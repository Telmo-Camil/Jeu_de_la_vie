#include "EtatObstacle.hpp"
#include "EtatCellule.hpp"

bool EtatObstacle::estObstacle() const{
    return true;
}

bool EtatObstacle::estVivante() const {
    return false; 
}


EtatCellule* EtatObstacle::calculerProchainEtat(int nbVoisinsVivants) const {
   
    return new EtatObstacle(); 
}