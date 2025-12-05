#ifndef STRATEGIEREGLES_HPP
#define STRATEGIEREGLES_HPP

class StrategieRegles
{
public:
    virtual ~StrategieRegles() = default;

    virtual bool nouvelleCelluleDoitNaitre(int nbVoisinsVivants) const = 0;

    virtual bool celluleVivanteDoitResterVivante(int nbVoisinsVivants) const = 0;
};

#endif