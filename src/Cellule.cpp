#include "Cellule.hpp"
#include "EtatCellule.hpp"
#include "EtatMort.hpp" 
#include "EtatVivant.hpp" 

Cellule::Cellule() : etatActuelle(new EtatMort()) {
}


void Cellule::setEtat(EtatCellule* nouvelEtat) {
    if (etatActuelle != nullptr) {
        delete etatActuelle;
    }
    etatActuelle = nouvelEtat;
}

bool Cellule::estVivante() {
    if (etatActuelle != nullptr) {
        return etatActuelle->estVivante();
    }
    return false;
}

void Cellule::definirProchainEtat(int nbVoisinsVivants) {
    if (etatActuelle != nullptr) {
        EtatCellule* prochainEtat = etatActuelle->calculerProchainEtat(nbVoisinsVivants);
        
      
        setEtat(prochainEtat);
    }
}

Cellule::~Cellule() {
    delete etatActuelle;
}
