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
}

void RVScene::translate(QVector3D vec)
{
    foreach (RVBody* body, *this) {
        body->translate(vec);
    }
}

void RVScene::rotate(float angle, QVector3D axis)
{
    foreach (RVBody* body, *this) {
        body->rotate(angle, axis);
    }
}

void RVScene::draw()
{
    foreach (RVBody* body, *this) {
        body->draw();
    }
    if(skybox!=NULL)
        skybox->draw();
}

RVCamera *RVScene::getCamera() const
{
    return camera;
}

RVSkyBox *RVScene::getSkybox() const
{
    return skybox;
}

void RVScene::setSkybox(RVSkyBox *newSkybox)
{
    skybox = newSkybox;
}
