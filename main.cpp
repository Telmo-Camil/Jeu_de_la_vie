#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../headers/EtatCellule.hpp" 
#include "../headers/EtatVivant.hpp"
#include "../headers/EtatMort.hpp"

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

std::vector<std::vector<EtatCellule*>> grid(gridWidth, std::vector<EtatCellule*>(gridHeight, nullptr));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            
            if (grid[x][y] != nullptr) {
                 delete grid[x][y];
            }

            if (std::rand() % 2 == 1) {
                grid[x][y] = new EtatVivant();
            } else {
                grid[x][y] = new EtatMort();
            }
        }
    }
}

void renderGrid(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    cell.setFillColor(sf::Color::White);

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            
            if (grid[x][y] != nullptr && grid[x][y]->estVivante()) {
                
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life (SFML)");
    window.setFramerateLimit(30);
    
    initializeGrid(); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        renderGrid(window);
    }

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] != nullptr) {
                delete grid[x][y];
            }
        }
    }

    return 0;
}