#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../headers/EtatCellule.hpp" 
#include "../headers/EtatVivant.hpp"
#include "../headers/EtatMort.hpp"
#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

Grille* grille = nullptr;

void initializeGrid() {
    if (grille != nullptr) delete grille;
    grille = new Grille(gridWidth, gridHeight);
    
    // Initialiser les règles
    RegleConwayClassique* regles = new RegleConwayClassique();
    grille->setRegles(regles);
    
    // Remplir aléatoirement
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            bool vivante = (std::rand() % 3 == 0);  // 1/3 vivantes
            grille->setCellule(x, y, vivante);
        }
    }
}

void renderGrid(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    cell.setFillColor(sf::Color::White);

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grille != nullptr && grille->getCellule(x, y)) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life (SFML)");
    window.setFramerateLimit(10);  // 10 itérations par seconde
    
    initializeGrid(); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mettre à jour la grille à chaque itération
        if (grille != nullptr) {
            grille->mettreAJour();
        }

        renderGrid(window);
    }

    // Libérer la mémoire
    if (grille != nullptr) {
        delete grille;
    }

    return 0;
}