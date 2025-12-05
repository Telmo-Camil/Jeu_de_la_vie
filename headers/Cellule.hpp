#ifndef CELLULE_HPP
#define CELLULE_HPP

class EtatCellule;

class Cellule {
    private: 
        EtatCellule* etatActuelle;

    public: 
        Cellule();
        ~Cellule();
        void setEtat(EtatCellule* nouvelEtat);
        bool estVivante();
        void definirProchainEtat(int nbVoisinsVivants);

};


#endif