#include "EtatObstacle.hpp"
#include "EtatCellule.hpp"


bool EtatObstacle::estVivante() const {
    return false; 
}


EtatCellule* EtatObstacle::calculerProchainEtat(int nbVoisinsVivants) const {
   
    return new EtatObstacle(); 
}