#include "rvcube.h"
#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    angleY = 0.0f;
    angleX = 0.0f;
    grabKeyboard();
}

RVWidget::~RVWidget()
{
}

void RVWidget::move()
{
    if (direction == "Haut")
    {
        angleX  = angleX - speed;
        body->rotate(-speed,QVector3D(1,0,0));

    }else if (direction == "Bas")
    {
        angleX  = angleX + speed;
        body->rotate(speed,QVector3D(1,0,0));

    }else if (direction == "Droite")
    {
        angleY  = angleY + speed;
        body->rotate(speed,QVector3D(0,1,0));

    }else if (direction == "Gauche")
    {
        angleY  = angleY - speed;
        body->rotate(-speed,QVector3D(0,1,0));

    }
    this->update();
}

void RVWidget::changeWireframe(bool wireframeState)
{
    body->setWireframe(wireframeState);
    this->update();
}

void RVWidget::changeCulling(bool cullingState)
{
    body->setCulling(cullingState);
    this->update();
}

void RVWidget::changeScale(int newScale)
{
    plan->setScale(newScale);
    this->update();
}

void RVWidget::changeSaturation(int newSaturation)
{
    float g = ((float)newSaturation)/255;
    body->setGlobalColor(QVector3D(g, g, g));
    this->update();

}

void RVWidget::changeProjection(bool newProj)
{
    camera->setIsOrthogonal(newProj);
    this->update();
}



void RVWidget::update()
{
    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    if(!isClicked){
        timer->start(10); // rotation
        isClicked = true;
    }else{
        timer->stop(); // pas de rotation
        isClicked = false;
    }
}

void RVWidget::changeFov(int fov)
{
    camera->setFov(fov);
    camera2->setFov(camera->getFov()-10);
    camera3->setFov(camera->getFov()-10);
    camera4->setFov(camera->getFov()-10);
    this->update();
}

void RVWidget::changeOpacity(int newOpacity)
{
    plan->setOpacity(newOpacity);
    this->update();
}

void RVWidget::changeSpeed(int newSpeed)
{
    speed = newSpeed;
    this->update();
}

void RVWidget::changeDirection(QString newDirection)
{
    direction = newDirection;
    this->update();
}

void RVWidget::reinitialiser()
{
    angleY = 0.0f;
    angleX = 0.0f;
    body->reinitialiser();
    this->update();
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //Réglage des états OpenGL
    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera = new RVCamera(); //bas gauche
    camera->setPosition(QVector3D(0,7,10));
    camera->setTarget(QVector3D(0,0,0));

    camera2 = new RVCamera(); //haut gauche
    camera2->setIsOrthogonal(true);
    camera2->setPosition(QVector3D (0, 0, 10));
    camera2->setTarget(QVector3D(0,0,0));

    camera3 = new RVCamera(); //haut droite
    camera3->setIsOrthogonal(true);
    camera3->setPosition(QVector3D (0,10,-0.001));
    camera3->setTarget(QVector3D(0,0,0));

    camera4 = new RVCamera(); //bas droite
    camera4->setIsOrthogonal(true);
    camera4->setPosition(QVector3D (10,0,0));
    camera4->setTarget(QVector3D(0,0,0));

    camera2->setFov(camera->getFov()-10);
    camera3->setFov(camera->getFov()-10);
    camera4->setFov(camera->getFov()-10);

    body = new RVCube();
    body->initialize();
    body->setCamera(camera);
    body->setPosition(QVector3D(0 ,0 ,0));

    plan = new RVPlane();
    plan->initialize();
    plan->setCamera(camera);
    plan->setPosition(QVector3D(0 ,0 ,0));
    plan->setScale(2);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

}

void RVWidget::resizeGL(int w, int h)
{
    float aspetcRatio  = ((float)w)/h;
    camera->setAspect(aspetcRatio);
    camera2->setAspect(aspetcRatio);
    camera3->setAspect(aspetcRatio);
    camera4->setAspect(aspetcRatio);
    this->h = h;
    this->w = w;
    //glViewport(0, 0, w, h);
}

void RVWidget::changeVue(int vue)
{
    indexVue = vue;
    this->update();
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (indexVue == 1){
        // bas gauche
        body->setCamera(camera);
        plan->setCamera(camera);
        glViewport(0, 0, this->w, this->h);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();
    }else
    if (indexVue == 2){
        // haut gauche
        body->setCamera(camera2);
        plan->setCamera(camera2);
        glViewport(0, 0, this->w, this->h);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();
    }else
    if (indexVue == 3){
        //haut droite
        body->setCamera(camera3);
        plan->setCamera(camera3);
        glViewport(0, 0, this->w, this->h);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();
    }else
    if (indexVue == 4){
        // bas droite
        body->setCamera(camera4);
        plan->setCamera(camera4);
        glViewport(0, 0, this->w, this->h);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();
    }else
    if (indexVue == 0){
        // bas gauche
        body->setCamera(camera);
        plan->setCamera(camera);
        glViewport(0, 0, this->w/2, this->h/2);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();

        //haut droite
        body->setCamera(camera3);
        plan->setCamera(camera3);
        glViewport(this->w/2, this->h/2, this->w/2, this->h/2);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();

        // haut gauche
        body->setCamera(camera2);
        plan->setCamera(camera2);
        glViewport(0, this->h/2, this->w/2, this->h/2);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();

        // bas droite
        body->setCamera(camera4);
        plan->setCamera(camera4);
        glViewport(this->w/2, 0 , this->w/2, this->h/2);
        for(int i = -plan->getLongX()/2+1 ; i < plan->getLongX()/2 ;i++){
            for(int j = -plan->getLongZ()/2+1 ; j < plan->getLongZ()/2 ;j++){
                body->setPosition(QVector3D(i*2,0,j*2));
                body->draw();
            }
        }
        plan->draw();
    }
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->position();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = (event->position().x() - oldPos.x()) /width();
    float dy = (event->position().y() - oldPos.y()) /height();
    angleX  = angleX  +  dy*180;
    angleY  = angleY  +  dx*180;

    body->rotate(dy*180,QVector3D(1,0,0));
    body->rotate(dx*180,QVector3D(0,1,0));

    oldPos = event->position();
    this->update();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left )//16777234) //left
    {
        QVector3D pos = camera->getPosition();
        pos.setX(pos.x() - 1);
        camera->setPosition(pos);
    }
    else if (event->key() == Qt::Key_Right ) //16777236)//right
    {
        QVector3D pos = camera->getPosition();
        pos.setX(pos.x() + 1);
        camera->setPosition(pos);
    }
    else if (event->key() == Qt::Key_Down) //16777237) //down
    {
        QVector3D pos = camera->getPosition();
        pos.setY(pos.y() - 1);
        camera->setPosition(pos);
    }
    else if (event->key() == Qt::Key_Up )//16777235) //up
    {
        QVector3D pos = camera->getPosition();
        pos.setY(pos.y() + 1);
        camera->setPosition(pos);

}
    this->update();
}

