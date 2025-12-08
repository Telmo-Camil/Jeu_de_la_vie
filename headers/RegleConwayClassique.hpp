#ifndef REGLECONWAYCLASSIQUE_HPP
#define REGLECONWAYCLASSIQUE_HPP

#include "StrategieRegles.hpp"

class RegleConwayClassique : public StrategieRegles
{
public:
    RegleConwayClassique(){};

    ~RegleConwayClassique(){};

    bool nouvelleCelluleDoitNaitre(int nbVoisinsVivants) const
    {
        return nbVoisinsVivants == 3;
    }
    
    bool celluleVivanteDoitResterVivante(int nbVoisinsVivants) const
    {
        return nbVoisinsVivants == 2 || nbVoisinsVivants == 3;
    }
};

#endif
