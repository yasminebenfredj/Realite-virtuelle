#ifndef RVSPECULARCUBE_H
#define RVSPECULARCUBE_H

#include "rvtexcube.h"

class RVSpecularCube : public RVTexCube
{
public:
    RVSpecularCube();

    void draw() override;
    void setCubeTexture(QString leftImage, QString rightImage,
                            QString frontImage, QString backImage,
                            QString topImage, QString bottomImage);

};

#endif // RVSPECULARCUBE_H
