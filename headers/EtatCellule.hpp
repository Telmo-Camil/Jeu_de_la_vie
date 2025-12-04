#ifndef ETATCELLULE_HPP
#define ETATCELLULE_HPP

#include "Cellule.hpp"

class EtatCellule {
    public : 
        virtual bool estVivante() const = 0;
        virtual EtatCellule* calculerProchainEtat(int nbVoisinsVivants) const = 0;
};

#endif