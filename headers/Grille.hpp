#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>
#include <string>
#include <ostream>

#include "Cellule.hpp"
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "StrategieRegles.hpp"

class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule*>> cellules;
    StrategieRegles* regles;

public:
    Grille(int l, int h);
    ~Grille();

    bool chargerDepuisFichier(const std::string& chemin);

    int obtenirVoisinsVivants(int x, int y) const;
    void mettreAJour();
    void afficherConsole() const;
    void sauvegarderDansFichier(std::ostream &sortie) const;

    void setRegles(StrategieRegles* r);
    StrategieRegles* getRegles() const;

    int getLargeur() const;
    int getHauteur() const;

    bool getCellule(int x, int y) const;
    void setCellule(int x, int y, bool etat);
};

#endif
