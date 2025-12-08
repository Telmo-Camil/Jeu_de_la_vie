#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"

const int cellSize = 10;
const int MAX_ITERATIONS = 100; // Limite d'itérations
Grille* grille = nullptr;

void initializeEnvironment() {
    mkdir("saves", 0777); // Création du dossier saves
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

    sf::RenderWindow window(sf::VideoMode(grille->getLargeur() * cellSize, grille->getHauteur() * cellSize), "Game of Life");
    window.setFramerateLimit(10);

    int currentIteration = 0;
    bool simulationActive = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (simulationActive) {
            // 1. Sauvegarde de l'itération actuelle
            std::string filename = "saves/iteration_" + std::to_string(currentIteration) + ".txt";
            std::ofstream ofs(filename);
            if (ofs.is_open()) {
                grille->sauvegarderDansFichier(ofs);
                ofs.close();
            }

            // 2. Mise à jour et vérification des conditions d'arrêt
            bool changed = grille->mettreAJour();
            currentIteration++;

            if (!changed) {
                std::cout << "Simulation terminee : Grille stable a l'iteration " << currentIteration << std::endl;
                simulationActive = false;
            } else if (currentIteration >= MAX_ITERATIONS) {
                std::cout << "Simulation terminee : Limite de " << MAX_ITERATIONS << " atteint." << std::endl;
                simulationActive = false;
            }
        }

        // Rendu graphique (continue même si la simulation est stoppée pour voir le résultat)
        window.clear(sf::Color::Black);
        sf::RectangleShape shape(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        shape.setFillColor(simulationActive ? sf::Color::White : sf::Color::Red); // Rouge si fini

        for (int x = 0; x < grille->getLargeur(); ++x) {
            for (int y = 0; y < grille->getHauteur(); ++y) {
                if (grille->getCellule(x, y)) {
                    shape.setPosition(x * cellSize, y * cellSize);
                    window.draw(shape);
                }
            }
        }
        window.display();
    }

    delete grille;
    return 0;
}