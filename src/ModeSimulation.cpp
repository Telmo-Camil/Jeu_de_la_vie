#include "../headers/ModeSimulation.hpp"
#include <iostream>
#include <thread>
#include <chrono>

ModeSimulation* ModeSimulation::instance = nullptr;

ModeSimulation::ModeSimulation(int maxIt) : maxIterations(maxIt) {}

ModeSimulation& ModeSimulation::getInstance() {
    if (instance == nullptr) instance = new ModeSimulation();
    return *instance;
}

void ModeSimulation::lancer(Grille& grille, const std::string& nomFichierEntree) {
    std::cout << "--- Début de la simulation console ---" << std::endl;

    for (int i = 0; i < maxIterations; i++) {
        // Commande pour effacer le terminal (Linux/macOS)
        // Utilisez system("cls") pour Windows
        std::cout << "\033[2J\033[1;1H"; 

        std::cout << "========================================" << std::endl;
        std::cout << " ITERATION : " << (i + 1) << " / " << maxIterations << std::endl;
        std::cout << "========================================" << std::endl;
        
        grille.afficherConsole();

        std::cout << "========================================" << std::endl;

        bool aChange = grille.mettreAJour();
        
        if (!aChange) {
            std::cout << "LOG : Grille stable détectée à l'itération " << i + 1 << "." << std::endl;
            break;
        }

        // Vitesse de lecture console
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << "--- Simulation terminée ---" << std::endl;
}

void ModeSimulation::lancerGraphique(Grille& grille) {
    // La logique graphique est gérée dans main.cpp via SFML
}