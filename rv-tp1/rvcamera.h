#ifndef RVCAMERA_H
#define RVCAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class RVCamera
{
public:
    RVCamera();
    virtual ~RVCamera();

    QMatrix4x4 viewMatrix();
    QMatrix4x4 projectionMatrix();

    QVector3D getUp() const;
    void setUp(const QVector3D &newUp);

    QVector3D getTarget() const;
    void setTarget(const QVector3D &newTarget);

    QVector3D getPosition() const;
    void setPosition(const QVector3D &newPosition);

    float getFov() const;
    void setFov(float newFov);

    float getAspect() const;
    void setAspect(float newAspect);

    float getZMin() const;
    void setZMin(float newZMin);

    float getZMax() const;
    void setZMax(float newZMax);

protected:
    QVector3D position;
    QVector3D target;
    QVector3D up;

    float fov;
    float aspect;
    float zMin;
    float zMax;

};

#endif // RVCAMERA_H
