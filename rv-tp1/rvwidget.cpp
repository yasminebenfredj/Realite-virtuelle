#include "rvcube.h"
#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    angleY = 0.0f;
    angleX = 0.0f;
}

RVWidget::~RVWidget()
{
}

void RVWidget::move()
{
    if (direction == "Haut")
    {
        angleX  = angleX - speed;
    }else if (direction == "Bas")
    {
        angleX  = angleX + speed;
    }else if (direction == "Droite")
    {
        angleY  = angleY + speed;
    }else if (direction == "Gauche")
    {
        angleY  = angleY - speed;
    }
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
    this->update();
}

void RVWidget::changeOpacity(int newOpacity)
{
    body->setOpacity(newOpacity);
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
    this->update();
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    //Réglage des états OpenGL
    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glFrontFace(GL_CCW); //glFrontFace(GL_CW);
    //glEnable(GL_CULL_FACE); //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera = new RVCamera();
    body = new RVCube();
    body->setCamera(camera);
    body->setPosition(QVector3D(0 ,0 ,-3.5));
    body->initialize();

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    //connect(timer, SIGNAL(clicked()), this, SLOT(startAnimation()));
    //connect(timer, SIGNAL(valueChanged(int)), this, SLOT(changeFov(int)));

}

void RVWidget::resizeGL(int w, int h)
{
    float aspetcRatio  = ((float)w)/h;
    camera->setAspect(aspetcRatio);
    glViewport(0, 0, w, h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    body->rotate(angleX,QVector3D(1,0,0));
    body->rotate(angleY,QVector3D(0,1,0));
    body->draw();
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
    oldPos = event->position();
    this->update();
}

