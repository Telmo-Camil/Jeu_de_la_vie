#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream> // Ajout pour lire le fichier
#include <iostream>

#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"

const int cellSize = 15; // Ajustez la taille des cellules pour la visibilité
Grille* grille = nullptr;

void initializeGrid() {
    if (grille != nullptr) delete grille;

    std::ifstream ifs("input.txt");
    if (!ifs.is_open()) {
        std::cerr << "ERREUR : Impossible d'ouvrir input.txt pour initialisation" << std::endl;
        return;
    }

    int h, l;
    ifs >> h >> l; // Lire les dimensions depuis le début du fichier
    ifs.close();

    // Créer la grille avec les dimensions lues
    grille = new Grille(l, h);
    
    // Attacher les règles
    grille->setRegles(new RegleConwayClassique());
    
    // Charger les états des cellules depuis le fichier
    if (!grille->chargerDepuisFichier("input.txt")) {
        std::cerr << "ERREUR : Échec du chargement des données depuis input.txt" << std::endl;
    }
}

int main() {
    initializeGrid(); // Initialiser d'abord pour avoir les dimensions correctes

    if (grille == nullptr) return -1;

    // Créer la fenêtre en fonction de la taille réelle de la grille chargée
    sf::RenderWindow window(sf::VideoMode(grille->getLargeur() * cellSize, 
                                          grille->getHauteur() * cellSize), 
                            "Jeu de la Vie - Chargé depuis input.txt");
    
    window.setFramerateLimit(5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        grille->mettreAJour();

        window.clear(sf::Color::Black);
        sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
        cellShape.setFillColor(sf::Color::White);

        for (int x = 0; x < grille->getLargeur(); ++x) {
            for (int y = 0; y < grille->getHauteur(); ++y) {
                if (grille->getCellule(x, y)) {
                    cellShape.setPosition(x * cellSize, y * cellSize);
                    window.draw(cellShape);
                }
            }
        }
        window.display();
    }

    delete grille;
    return 0;
}