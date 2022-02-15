#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList>
#include "rvbody.h"
#include "rvcamera.h"
#include "rvskybox.h"

class RVScene : public QList<RVBody*>
{
    public:
        RVScene();

        void setCamera(RVCamera *newCamera);
        void translate(QVector3D vec);
        void rotate(float angle, QVector3D axis);
        void draw();

        RVCamera *getCamera() const;

        RVSkyBox *getSkybox() const;
        void setSkybox(RVSkyBox *newSkybox);

protected:
        RVCamera *camera;
        RVSkyBox *skybox;

};

#endif // RVSCENE_H
