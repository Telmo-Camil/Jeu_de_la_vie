#include "ModeSimulation.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

ModeSimulation* ModeSimulation::instance = nullptr;

// Constructeur privé
ModeSimulation::ModeSimulation(int maxIt)
    : maxIterations(maxIt)
{
}

ModeSimulation& ModeSimulation::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ModeSimulation();
    }
    return *instance;
}

void ModeSimulation::lancer(Grille& grille, const std::string& nomFichierEntree)
{
    std::cout << "Chargement du fichier : " << nomFichierEntree << std::endl;

    if (!grille.chargerDepuisFichier(nomFichierEntree))
    {
        std::cerr << "ERREUR : Impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    std::cout << "Début de la simulation..." << std::endl;

    for (int i = 0; i < maxIterations; i++)
    {
        std::cout << "Iteration " << i + 1 << "/" << maxIterations << std::endl;

        grille.afficherConsole();
        grille.mettreAJour();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "Simulation terminée." << std::endl;
}

void ModeSimulation::lancerGraphique(Grille& grille)
{
    std::cout << "Mode graphique non implémenté, mais appelé correctement !" << std::endl;

    // Si tu utilises SFML, SDL, Qt ou autre → mettre le code ici
    // Exemple placeholder :
    for (int i = 0; i < maxIterations; i++)
    {
        grille.mettreAJour();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
