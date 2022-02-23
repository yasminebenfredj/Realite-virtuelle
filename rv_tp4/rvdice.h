#ifndef RVDICE_H
#define RVDICE_H

#include "rvbody.h"

class RVDice : public RVBody
{
public:
    RVDice();

    // RVBody interface
public:
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeBuffer() override;
    void initializeVAO() override;
};

#endif // RVDICE_H
