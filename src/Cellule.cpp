#include "Cellule.hpp"
#include "EtatCellule.hpp"
#include "EtatMort.hpp" 
#include "EtatVivant.hpp" 

Cellule::Cellule() : etatActuelle(new EtatMort()) {
}

Cellule::~Cellule() {
    delete etatActuelle;
}

void Cellule::setEtat(EtatCellule* nouvelEtat) {
    if (etatActuelle != nullptr) {
        delete etatActuelle;
    }
    etatActuelle = nouvelEtat;
}

bool Cellule::estVivante() {
    return (etatActuelle != nullptr) && etatActuelle->estVivante();
}

void Cellule::definirProchainEtat(int nbVoisinsVivants) {
    if (etatActuelle != nullptr) {
        EtatCellule* prochainEtat = etatActuelle->calculerProchainEtat(nbVoisinsVivants);
        setEtat(prochainEtat);
    }
}