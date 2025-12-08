
#include "EtatVivant.hpp"

#include "EtatMort.hpp"
#include "EtatCellule.hpp"

bool EtatVivant::estObstacle() const{
    return false;
}

bool EtatVivant::estVivante() const {
    return true; 
}


EtatCellule* EtatVivant::calculerProchainEtat(int nbVoisinsVivants) const {
    
    if (nbVoisinsVivants == 2 || nbVoisinsVivants == 3) {
       
        return new EtatVivant(); 
    } else {
        
        return new EtatMort(); 
    }
}