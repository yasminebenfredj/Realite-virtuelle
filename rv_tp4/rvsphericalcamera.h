#ifndef RVSPHERICALCAMERA_H
#define RVSPHERICALCAMERA_H

#include "rvcamera.h"

class RVSphericalCamera : public RVCamera
{
public:
    RVSphericalCamera();

    float getPhi() const;
    void setPhi(float newPhi);

    float getTheta() const;
    void setTheta(float newTheta);

    float getRho() const;
    void setRho(float newRho);

    void update();

private:
    float phi;
    float theta;
    float rho;

    void updatePosition();

};

#endif // RVSPHERICALCAMERA_H
