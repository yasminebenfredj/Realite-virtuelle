#include "rvcamera.h"

RVCamera::RVCamera()
{
    position = QVector3D(0, 0, 0);
    target = QVector3D(0, 0, -0.5);
    up = QVector3D(0, 1, 0);

    fov = 45;
    aspect = 1.33f;
    zMax = 100.0f;
    zMin = 1.0f;
    isOrthogonal = false;
}

RVCamera::~RVCamera()
{

}

QMatrix4x4 RVCamera::viewMatrix()
{
    QMatrix4x4 view;

    view.lookAt(position, target, up);
    return view;
}

QMatrix4x4 RVCamera::projectionMatrix()
{
    QMatrix4x4 proj;
    if(isOrthogonal)
    {
        proj.ortho((-fov/2) * aspect, (fov/2) * aspect , -fov/2,  fov/2, zMin,  zMax);
    }else{
        proj.perspective(fov, aspect, zMin, zMax);
    }
    return  proj;
}

float RVCamera::getFov() const
{
    return fov;
}

void RVCamera::setFov(float newFov)
{
    fov = newFov;
}

QVector3D RVCamera::getUp() const
{
    return up;
}

void RVCamera::setUp(const QVector3D &newUp)
{
    up = newUp;
}

QVector3D RVCamera::getTarget() const
{
    return target;
}

void RVCamera::setTarget(const QVector3D &newTarget)
{
    target = newTarget;
}

QVector3D RVCamera::getPosition() const
{
    return position;
}

void RVCamera::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

float RVCamera::getAspect() const
{
    return aspect;
}

void RVCamera::setAspect(float newAspect)
{
    aspect = newAspect;
}

float RVCamera::getZMin() const
{
    return zMin;
}

void RVCamera::setZMin(float newZMin)
{
    zMin = newZMin;
}

float RVCamera::getZMax() const
{
    return zMax;
}

void RVCamera::setZMax(float newZMax)
{
    zMax = newZMax;
}

bool RVCamera::getIsOrthogonal() const
{
    return isOrthogonal;
}

void RVCamera::setIsOrthogonal(bool newIsOrthogonal)
{
    isOrthogonal = newIsOrthogonal;
}


