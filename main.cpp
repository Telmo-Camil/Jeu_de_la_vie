#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"
#include "../headers/EtatObstacle.hpp"

const int cellSize = 15;
const int MAX_ITERATIONS = 200;
Grille* grille = nullptr;

void initializeEnvironment() {
    mkdir("saves", 0777); 
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) return;
    int h, l;
    ifs >> h >> l;
    ifs.close();
    grille = new Grille(l, h);
    grille->setRegles(new RegleConwayClassique());
    grille->chargerDepuisFichier("input.txt");
}

int main() {
    initializeEnvironment();
    if (!grille) return -1;

    sf::RenderWindow window(sf::VideoMode(grille->getLargeur() * cellSize, grille->getHauteur() * cellSize), "Game of Life - POO");
    window.setFramerateLimit(10);

    int currentIteration = 0;
    bool simulationActive = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (simulationActive) {
            std::string filename = "saves/iteration_" + std::to_string(currentIteration) + ".txt";
            std::ofstream ofs(filename);
            if (ofs.is_open()) {
                grille->sauvegarderDansFichier(ofs);
                ofs.close();
            }

            bool changed = grille->mettreAJour();
            currentIteration++;

            if (!changed || currentIteration >= MAX_ITERATIONS) {
                std::cout << "Simulation terminee." << std::endl;
                simulationActive = false;
            }
        }

        window.clear(sf::Color::Black);
        sf::RectangleShape shape(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

        for (int x = 0; x < grille->getLargeur(); ++x) {
            for (int y = 0; y < grille->getHauteur(); ++y) {
                Cellule* cell = grille->getCellulePtr(x, y);

                // 1. Détection Obstacle (Bleu)
                if (dynamic_cast<EtatObstacle*>(cell->getEtat())) {
                    shape.setFillColor(sf::Color::Blue);
                } 
                // 2. Détection Vivant (Blanc ou Rouge si fini)
                else if (cell->estVivante()) {
                    shape.setFillColor(simulationActive ? sf::Color::White : sf::Color::Red);
                } 
                // 3. Mort (Rien à dessiner)
                else {
                    continue;
                }

                shape.setPosition(x * cellSize, y * cellSize);
                window.draw(shape);
            }
        }
        window.display();
    }

    delete grille;
    return 0;
}