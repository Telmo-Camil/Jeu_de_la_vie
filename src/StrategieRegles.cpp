

#include "StrategieRegles.hpp"

class ReglesConwayClassique : public StrategieRegles
{
public:
    ReglesConwayClassique(){};

    ~ReglesConwayClassique(){
        
    };

    bool nouvelleCelluleDoitNaitre(int nbVoisinsVivants) const
    {

        return nbVoisinsVivants == 3;
    }
    bool celluleVivanteDoitResterVivante(int nbVoisinsVivants) const
    {

        return nbVoisinsVivants == 2 || nbVoisinsVivants == 3;
    }
};

