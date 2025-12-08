#ifndef ETATCELLULE_HPP
#define ETATCELLULE_HPP

class EtatCellule {
    public : 
        virtual ~EtatCellule() = default;

        virtual bool estObstacle() const = 0;
        virtual bool estVivante() const = 0;

        virtual EtatCellule* calculerProchainEtat(int nbVoisinsVivants) const = 0;
};

#endif