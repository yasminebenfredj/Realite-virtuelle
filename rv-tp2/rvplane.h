#ifndef RVPLANE_H
#define RVPLANE_H

#include "rvbody.h"

class RVPlane  : public RVBody
{
public:
    RVPlane();
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    int getLongZ() const;
    int getLongX() const;

protected:
    void initializeBuffer() override;
    int longX = 20; //longueur
    int longZ = 20; //largeur
};

#endif // RVPLANE_H
