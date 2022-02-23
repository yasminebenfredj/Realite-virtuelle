#include "rvscene.h"

RVScene::RVScene()
{

}

void RVScene::setCamera(RVCamera *newCamera)
{
    foreach (RVBody* body, *this) {
        camera = newCamera;
        body->setCamera(camera);
    }
    if(skybox!=NULL)
        skybox->setCamera(camera);

    soleil->setCamera(camera);
    if(specCube!=NULL)
        specCube->setCamera(camera);
}



void RVScene::translate(QVector3D vec)
{
    foreach (RVBody* body, *this) {
        body->translate(vec);
    }
    if(specCube!=NULL)
        specCube->translate(vec);
}

void RVScene::rotate(float angle, QVector3D axis)
{
    foreach (RVBody* body, *this) {
        body->rotate(angle, axis);
    }
    if(specCube!=NULL)
        specCube->rotate(angle, axis);
}

void RVScene::draw()
{
    foreach (RVBody* body, *this) {
        body->draw();
    }
    if(skybox!=NULL)
        skybox->draw();
    if(specCube!=NULL)
        specCube->draw();
    if(stateSoleil)
        soleil->draw();
}

RVCamera *RVScene::getCamera() const
{
    return camera;
}

RVSkyBox *RVScene::getSkybox() const
{
    return skybox;
}

RVLight *RVScene::getLight() const
{
    return light;
}

void RVScene::setSkybox(RVSkyBox *newSkybox)
{
    skybox = newSkybox;
}

void RVScene::setLight(RVLight *newLight)
{
    light = newLight;
    foreach (RVBody* body, *this) {
        body->setLight(light);
    }
    if(skybox!=NULL)
        skybox->setLight(light);
    if(specCube!=NULL)
        specCube->setLight(light);

    soleil->setLight(light);
}

RVBody *RVScene::getSpecCube() const
{
    return specCube;
}

void RVScene::setSpecCube(RVBody *newSpecCube)
{
    specCube = newSpecCube;
}

RVSphere *RVScene::getSoleil() const
{
    return soleil;
}

void RVScene::setStateSoleil(bool state)
{
    stateSoleil = state;
}


void RVScene::setSoleil(RVSphere *soleil)
{
    this->soleil = soleil;
}
