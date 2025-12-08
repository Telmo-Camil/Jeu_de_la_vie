#include "TestSimulation.hpp"
#include "Grille.hpp"
#include "RegleConwayClassique.hpp"

// ...existing code...

bool TestSimulation::testerEtatApresIterations(
        const std::vector<std::vector<bool>>& etatInitial,
        const std::vector<std::vector<bool>>& etatAttendu,
        int iterations)
{
    int h = etatInitial.size();
    int l = etatInitial[0].size();

    // 1. Créer grille
    Grille grille(l, h);
    grille.setRegles(new RegleConwayClassique());
    // 2. Placer l'état initial
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < l; ++x)
            grille.setCellule(x, y, etatInitial[y][x]);

    // 3. Lancer les itérations
    for (int i = 0; i < iterations; ++i)
        grille.mettreAJour();

    // 4. Comparer avec l'état attendu
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < l; ++x)
            if (grille.getCellule(x, y) != etatAttendu[y][x])
                return false;

    return true;
}
