#ifndef ETATMORT_HPP
#define ETATMORT_HPP

#include "EtatCellule.hpp"

class EtatMort : public EtatCellule {
    public: 
        bool estObstacle() const override;
        bool estVivante() const override;
        EtatCellule* calculerProchainEtat(int nbVoisinsVivants) const override;

};

#endif