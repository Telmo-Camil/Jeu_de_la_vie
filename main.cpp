#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 60;

struct Cell {
    bool alive;
    bool nextState;
};

std::vector<std::vector<Cell>> grid(gridWidth, std::vector<Cell>(gridHeight, {false, false}));

int countLiveNeighbors(int x, int y) {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            
            int nx = (x + dx + gridWidth) % gridWidth;
            int ny = (y + dy + gridHeight) % gridHeight;
            
            if (grid[nx][ny].alive) count++;
        }
    }
    return count;
}

void updateGrid() {
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            int neighbors = countLiveNeighbors(x, y);
            
            if (grid[x][y].alive) {
                grid[x][y].nextState = (neighbors == 2 || neighbors == 3);
            } else {
                grid[x][y].nextState = (neighbors == 3);
            }
        }
    }
    
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y].alive = grid[x][y].nextState;
        }
    }
}

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y].alive = (std::rand() % 3 == 0);
            grid[x][y].nextState = false;
        }
    }
}

void renderGrid(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);

    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    cell.setFillColor(sf::Color::White);

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y].alive) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");
    window.setFramerateLimit(15);
    
    initializeGrid();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        updateGrid();
        renderGrid(window);
    }

    return 0;
}