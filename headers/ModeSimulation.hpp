#ifndef MODESIMULATION_HPP
#define MODESIMULATION_HPP

#include <string>
#include "Grille.hpp"

class ModeSimulation
{
private:
    static ModeSimulation* instance;  // Singleton
    int maxIterations;

    // Constructeur privé (Singleton)
    ModeSimulation(int maxIt = 50);

public:
    // Empêcher copie
    ModeSimulation(const ModeSimulation&) = delete;
    ModeSimulation& operator=(const ModeSimulation&) = delete;

    // Singleton - accès à l'instance unique
    static ModeSimulation& getInstance();

    // Simulation console
    void lancer(Grille& grille, const std::string& nomFichierEntree);

    // Simulation graphique (placeholder, selon ton projet)
    void lancerGraphique(Grille& grille);
};

#endif
