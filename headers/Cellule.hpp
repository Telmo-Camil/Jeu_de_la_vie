#ifndef CELLULE_HPP
#define CELLULE_HPP

#include "EtatCellule.hpp"

class Cellule {
    private: 
        EtatCellule* etatActuelle;

    public: 
        Cellule();
        void setEtat(EtatCellule* nouvelEtat);
        bool estVivante();
        void definirProchainEtat(int nbVoisinsVivants);

};


#endif