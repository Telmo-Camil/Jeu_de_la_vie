#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../headers/Grille.hpp"
#include "../headers/RegleConwayClassique.hpp"
#include "../headers/Cellule.hpp"


bool comparerGrilleAvecFichier(const Grille& grille, const std::string& cheminExpected) {
    std::ifstream expectedFile(cheminExpected);
    if (!expectedFile.is_open()) {
        std::cerr << "ERREUR : Impossible d'ouvrir " << cheminExpected << std::endl;
        return false;
    }

    int expH, expL;
    expectedFile >> expH >> expL;

    // Vérification des dimensions
    if (expH != grille.getHauteur() || expL != grille.getLargeur()) {
        std::cout << "FAIL : Les dimensions ne correspondent pas." << std::endl;
        return false;
    }

    // Comparaison cellule par cellule
    for (int y = 0; y < expH; ++y) {
        for (int x = 0; x < expL; ++x) {
            int valeurAttendue;
            expectedFile >> valeurAttendue;
            
            bool etatAttendu = (valeurAttendue == 1);
            bool etatActuel = grille.getCellule(x, y);

            if (etatActuel != etatAttendu) {
                std::cout << "ERREUR : Difference detectee en (" << x << "," << y << ") "
                          << "| Attendu: " << valeurAttendue 
                          << ", Obtenu: " << (etatActuel ? 1 : 0) << std::endl;
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::cout << "=== LANCEMENT DU TEST DE VALIDATION : INPUT VS EXPECTED ===" << std::endl;

    std::ifstream check("input.txt");
    if (!check.is_open()) {
        std::cerr << "ERREUR : input.txt est requis pour ce test." << std::endl;
        return 1;
    }
    int h, l;
    check >> h >> l;
    check.close();

    Grille grilleTest(l, h);
    grilleTest.setRegles(new RegleConwayClassique());
    
    if (!grilleTest.chargerDepuisFichier("input.txt")) {
        std::cerr << "ERREUR : Echec du chargement de input.txt" << std::endl;
        return 1;
    }

    // 2. Simulation d'UNE generation
    std::cout << "Simulation d'une itération en cours..." << std::endl;
    grilleTest.mettreAJour();

    // 3. Validation par comparaison
    if (comparerGrilleAvecFichier(grilleTest, "expected.txt")) {
        std::cout << "✅ RESULTAT : TEST REUSSI. La grille correspond a expected.txt" << std::endl;
    } else {
        std::cout << "❌ RESULTAT : TEST ECHOUE. La grille differe de expected.txt" << std::endl;
    }

    return 0;
}