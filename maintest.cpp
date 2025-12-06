#include <iostream>
#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"

int main() {
    std::cout << "=== Test du Jeu de la Vie ===" << std::endl;
    
    // Charger grille initiale depuis input.txt
    Grille* g = new Grille(5, 5);
    RegleConwayClassique* regles = new RegleConwayClassique();
    g->setRegles(regles);
    
    if (!g->chargerDepuisFichier("input.txt")) {
        std::cerr << "Erreur : impossible de charger input.txt" << std::endl;
        delete g;
        delete regles;
        return 1;
    }
    
    std::cout << "Grille initiale :" << std::endl;
    g->afficherConsole();
    
    // Faire évoluer la grille (n itérations)
    int n = 1;
    for (int i = 0; i < n; ++i)
        g->mettreAJour();
    
    std::cout << "Grille après " << n << " itération(s) :" << std::endl;
    g->afficherConsole();
    
    // Charger la grille attendue depuis expected.txt
    Grille* gAttendue = new Grille(5, 5);
    RegleConwayClassique* regles2 = new RegleConwayClassique();
    gAttendue->setRegles(regles2);
    
    if (!gAttendue->chargerDepuisFichier("expected.txt")) {
        std::cerr << "Erreur : impossible de charger expected.txt" << std::endl;
        delete g;
        delete gAttendue;
        delete regles;
        delete regles2;
        return 1;
    }
    
    std::cout << "Grille attendue :" << std::endl;
    gAttendue->afficherConsole();
    
    // Vérifier
    if (*g == *gAttendue)
        std::cout << "\n✅ TEST OK" << std::endl;
    else
        std::cout << "\n❌ TEST FAIL" << std::endl;
    
    delete g;
    delete gAttendue;
    delete regles;
    delete regles2;
    
    return 0;
}
