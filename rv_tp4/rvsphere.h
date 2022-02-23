#ifndef RVSPHERE_H
#define RVSPHERE_H

#include "rvsurface.h"

class RVSphere : public RVSurface
{
public:
    RVSphere(double radius = 1.0);

    double getRadius() const;
    void setRadius(double newRadius);

protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double radius;
};

#endif // RVSPHERE_H
