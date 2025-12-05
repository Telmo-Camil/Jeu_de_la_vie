#ifndef STRATEGIEREGLES_H
#define STRATEGIEREGLES_H

class StrategieRegles
{
public:
    virtual ~StrategieRegles() = default;

    virtual bool nouvelleCelluleDoitNaitre(int nbVoisinsVivants) const = 0;

    virtual bool celluleVivanteDoitResterVivante(int nbVoisinsVivants) const = 0;
};

#endif