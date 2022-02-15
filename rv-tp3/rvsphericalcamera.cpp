#include "rvsphericalcamera.h"
#include <cmath>

RVSphericalCamera::RVSphericalCamera()
{
    phi = M_PI/4;
    theta = 0;
    rho = 20;
}

float RVSphericalCamera::getPhi() const
{
    return phi;
}

void RVSphericalCamera::setPhi(float newPhi)
{
    if(newPhi > -M_PI/2 && newPhi < M_PI/2)
        phi = newPhi;
    this->updatePosition();
}

float RVSphericalCamera::getTheta() const
{
    return theta;
}

void RVSphericalCamera::setTheta(float newTheta)
{
    theta = newTheta;
    this->updatePosition();
}

float RVSphericalCamera::getRho() const
{
    return rho;
}

void RVSphericalCamera::setRho(float newRho)
{
    if(newRho > 0)
        rho = newRho;
    this->updatePosition();
}

void RVSphericalCamera::update()
{
    this->updatePosition();
}

void RVSphericalCamera::updatePosition()
{
    float x = this->target.x() + rho * qCos(phi) * qCos(theta);
    float y = this->target.y() + rho * qSin(phi);
    float z = this->target.z() + rho * qCos(phi) * qSin(theta) ;
    this->position = QVector3D(x, y, z);
}
