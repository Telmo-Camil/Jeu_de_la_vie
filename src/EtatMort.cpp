#include "EtatMort.hpp"
#include "EtatVivant.hpp"
#include "EtatCellule.hpp"


bool EtatMort::estVivante() const {
    return false; 
}


EtatCellule* EtatMort::calculerProchainEtat(int nbVoisinsVivants) const {
    
    if (nbVoisinsVivants == 3) { 
        return new EtatVivant(); 
    } else {
        return new EtatMort(); 
    }
}