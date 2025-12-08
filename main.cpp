#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>

#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"
#include "../headers/EtatObstacle.hpp"
#include "../headers/ModeSimulation.hpp"

const int cellSize = 15;
const int MAX_ITERATIONS = 200;
Grille* grid = nullptr;

void initializeEnvironment() {
    mkdir("saves", 0777); 
    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) return;
    int h, l;
    ifs >> h >> l;
    ifs.close();
    grid = new Grille(l, h);
    grid->setRegles(new RegleConwayClassique());
    grid->chargerDepuisFichier("input.txt");
}

void runGraphicMode() {
    sf::RenderWindow window(sf::VideoMode(grid->getLargeur() * cellSize, grid->getHauteur() * cellSize), "Game of Life - SFML");
    
    // Correction pour l'erreur de sync : on désactive explicitement la vsync avant de limiter les fps
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(10); 

    int currentIteration = 0;
    bool simulationActive = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (simulationActive) {
            // Sauvegarde iteration
            std::ofstream ofs("saves/iteration_" + std::to_string(currentIteration) + ".txt");
            if (ofs) grid->sauvegarderDansFichier(ofs);

            bool changed = grid->mettreAJour();
            currentIteration++;

            if (!changed || currentIteration >= MAX_ITERATIONS) {
                simulationActive = false;
                std::cout << "Graphique : Simulation stoppee (Stable ou Limite)." << std::endl;
            }
        }

        window.clear(sf::Color::Black);
        sf::RectangleShape shape(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

        for (int x = 0; x < grid->getLargeur(); ++x) {
            for (int y = 0; y < grid->getHauteur(); ++y) {
                Cellule* cell = grid->getCellulePtr(x, y);

                if (dynamic_cast<EtatObstacle*>(cell->getEtat())) {
                    shape.setFillColor(sf::Color::Blue);
                } else if (cell->estVivante()) {
                    shape.setFillColor(simulationActive ? sf::Color::White : sf::Color::Red);
                } else {
                    continue;
                }

                shape.setPosition(x * cellSize, y * cellSize);
                window.draw(shape);
            }
        }
        window.display();
    }
}

int main() {
    int choice;
    std::cout << "=== MENU JEU DE LA VIE ===" << std::endl;
    std::cout << "1. Mode Console" << std::endl;
    std::cout << "2. Mode Graphique" << std::endl;
    std::cout << "Votre choix : ";
    std::cin >> choice;

    initializeEnvironment();
    if (!grid) return -1;

    if (choice == 1) {
        ModeSimulation::getInstance().lancer(*grid, "input.txt");
    } else if (choice == 2) {
        runGraphicMode();
    } else {
        std::cout << "Erreur : Choix invalide." << std::endl;
    }

    delete grid;
    return 0;
}