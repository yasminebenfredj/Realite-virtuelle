#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList>
#include "rvbody.h"
#include "rvcamera.h"
#include "rvskybox.h"
#include "rvlight.h"
#include "rvsphere.h"

class RVScene : public QList<RVBody*>
{
    public:
        RVScene();

        void setCamera(RVCamera *newCamera);
        void setSoleil(RVSphere *soleil);
        void setStateSoleil(bool state);
        void translate(QVector3D vec);
        void rotate(float angle, QVector3D axis);
        void draw();

        RVCamera *getCamera() const;
        RVSphere *getSoleil() const;
        RVSkyBox *getSkybox() const;
        RVLight *getLight() const;
        void setSkybox(RVSkyBox *newSkybox);

        void setLight(RVLight *newLight);

        RVBody *getSpecCube() const;
        void setSpecCube(RVBody *newSpecCube);

protected:
        RVCamera *camera;
        RVSkyBox *skybox;
        RVSphere *soleil;
        RVLight *light;
        RVBody *specCube;
        bool stateSoleil = false;

};

#endif // RVSCENE_H
