#ifndef ETATVIVANT_HPP
#define ETATVIVANT_HPP

#include "EtatCellule.hpp"

class EtatVivant : public EtatCellule {
    public: 
        bool estVivante() const override;
        EtatCellule* calculerProchainEtat(int nbVoisinsVivants) const override;

};

#endif