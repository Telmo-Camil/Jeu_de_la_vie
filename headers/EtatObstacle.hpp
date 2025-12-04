#ifndef ETATOBSTACLE_HPP
#define ETATOBSTACLE_HPP

#include "EtatCellule.hpp"

class EtatObstacle : public EtatCellule {
    public: 
        bool estVivante() const override;
        EtatCellule* calculerProchainEtat(int nbVoisinsVivants) const override;

};

#endif