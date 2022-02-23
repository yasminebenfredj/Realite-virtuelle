#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    timer = new QTimer();
    angleY = 5;

    grabKeyboard();
}

RVWidget::~RVWidget()
{
}

void RVWidget::addObject(int type, QVector3D pos, QQuaternion orientation, QString name)
{
    this->makeCurrent();
    RVBody* newObject;
    switch (type)
    {
    case 0: // cube texturé
        newObject = new RVTexCube();
        newObject->setTexture(":/textures/3d-cube-textures/pierre.jpg");
        newObject->setScale(2);
        break;
    case 1: //dé
        newObject = new RVDice();
        newObject->setTexture(":/textures/3d-cube-textures/dice_texture.jpg");
        break;
    case 2: //planet
        newObject = new RVSphere(2.0);
        newObject->setTexture(":/textures/planet.jpg", true, true);
        //dynagit add * mic_cast<RVPlanet*>(newObject)->setNightTexture(":/textures/planet2.jpg", true, true);
        break;
    case 3: //torus
        newObject = new RVTorus(0.4,5);
        newObject->setFSFileName(":/shaders/FS_lit_checker.fsh");
        newObject->setTexture(":/textures/silver.jpg");
        break;
    case 4: //plane
        newObject = new RVPlane(10, 10);
        newObject->setTexture(":/textures/sol2.jpg");
        break;
    case 5: //cube coloré
        newObject = new RVCube();
        newObject->setScale(2);
        break;
    }
    newObject->setLight(scene.getLight());
    newObject->setPosition(pos);
    newObject->setOrientation(orientation);
    newObject->setCamera(scene.getCamera());

    // verification du nom :
    for (auto obj : scene) {
        if(obj->getObjectName() == name){
            srand (time(NULL));
            int irand = rand() % 1000 + 100;
            name += QString::number(irand);
        }
    }
    newObject->setObjectName(name);
    newObject->initialize();
    scene.append(newObject);
    QOpenGLWidget::update();
}


void RVWidget::update()
{
    if (animationOn) {
        scene.at(selectedObject)->rotate(angleY, QVector3D(0, 1, 0));
        QOpenGLWidget::update();
    }
    if(rotateSoleil){
        scene.getSoleil()->rotate(radius+angleY,QVector3D(0, 1, 0));
        QOpenGLWidget::update();
    }
}


void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // light
    RVLight* light = new RVLight();

    // camera
    RVCamera* camera;
    camera = new RVSphericalCamera();
    camera->setFov(45.0f);
    camera->setPosition(QVector3D(0, 8, 8));
    camera->setPosition(QVector3D(0, 8, 8));
    camera->setZMin(1);
    camera->setZMax(500);

    // sky
    RVSkyBox* skybox;
    skybox = new RVSkyBox();
    skybox->setCamera(camera);
    skybox->setPosition(QVector3D(0, 0, 0));
    skybox->setScale(100);
    skybox->setCubeTexture(":/textures/Forest/negx.jpg",
                           ":/textures/Forest/posx.jpg",
                           ":/textures/Forest/posy.jpg",
                           ":/textures/Forest/negy.jpg",
                           ":/textures/Forest/posz.jpg",
                           ":/textures/Forest/negz.jpg"
                           );
    skybox->initialize();
    scene.setSkybox(skybox);

    // Dé
    RVBody* body;
    body = new RVDice();
    body->setCamera(camera);
    body->setPosition(QVector3D(15, 4, 0));
    body->initialize();
    body->setScale(3);
    body->setObjectName("Dé1");
    body->setTexture(":/textures/3d-cube-textures/dice_texture.jpg");

    scene.append(body);
    camera->setTarget(body->getPosition());

    // plane
    RVBody* plane;
    plane = new RVPlane(40, 40);
    plane->setCamera(camera);
    plane->setPosition(QVector3D(0, -10, 0));
    plane->setTexture(":/textures/wood.png");
    plane->setObjectName("Plane1");
    plane->initialize();
    scene.append(plane);

    // terre
    RVBody* world;
    world = new RVSphere(2.0);
    world->setCamera(camera);
    world->setPosition(QVector3D(0, 7, 0));
    world->setScale(2);
    world->setObjectName("Terre1");
    world->setTexture(":/textures/2k_earth_daymap.jpg", true, true);
    //dynamic_cast<RVPlanet*>(world)->setNightTexture(":/textures/2k_earth_nightmap.jpg", true, true);
    world->initialize();
    scene.append(world);

    // torus
    RVBody* torus;
    torus = new RVTorus(0.5,7);
    torus->setCamera(camera);
    torus->setPosition(QVector3D(0, 7, 0));
    //torus->setFSFileName(":/shaders/FS_simple_texture.fsh");
    torus->setFSFileName(":/shaders/FS_lit_checker.fsh");
    torus->setTexture(":/textures/gold2.jpg");
    torus->setObjectName("Torus1");
    torus->initialize();
    scene.append(torus);


    RVBody* specCube;
    specCube = new RVSpecularCube();
    specCube->setCamera(camera);
    specCube->setPosition(QVector3D(10, 5, 10));
    specCube->initialize();
    specCube->setScale(5);
    specCube->setObjectName("CubeSpect");
    dynamic_cast<RVSpecularCube*>(specCube)->setCubeTexture(":/textures/Forest/posx.jpg",
                             ":/textures/Forest/negx.jpg",
                             ":/textures/Forest/posy.jpg",
                             ":/textures/Forest/negy.jpg",
                             ":/textures/Forest/posz.jpg",
                             ":/textures/Forest/negz.jpg"
                             );
    scene.setSpecCube(specCube);

    RVSphere* soleil ;
    soleil = new RVSphere(2);
    soleil->setPosition(light->getPosition());
    soleil->setObjectName("Soleil");
    soleil->setTexture(":/textures/2k_sun.jpg", true, true);
    soleil->initialize();
    scene.setSoleil(soleil);



    dynamic_cast<RVSphericalCamera*>(camera)->update();
    scene.setCamera(camera);

    scene.setLight(light);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = ((float)w)/h;
    scene.getCamera()->setAspect(aspect);
    glViewport(0, 0, w, h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene.getCamera()->setTarget(scene.at(selectedObject)->getPosition());
    scene.draw();
}



//////////////////////////////// Slots ///////////////////////////////
///
///
/////
/// \brief RVWidget::afficherSoleil
/// \param state
///
void RVWidget::afficherSoleil(bool state)
{
    scene.setStateSoleil(state);
    QOpenGLWidget::update();
}


/////////
/// \brief RVWidget::changeCoefSpec
/// \param val
///
void RVWidget::changeCoefSpec(int val)
{
    scene.at(selectedObject)->setSpecStrength(val);
    QOpenGLWidget::update();
}

/////
/// \brief RVWidget::changeLightPosX
/// \param x
///
void RVWidget::changeLightPosX(double x)
{
    scene.getLight()->setPosition(QVector3D(x,
                       scene.getLight()->getPosition().y(),
                       scene.getLight()->getPosition().z()));
    scene.getSoleil()->setPosition(QVector3D(x,
                                             scene.getLight()->getPosition().y(),
                                             scene.getLight()->getPosition().z()));
    QOpenGLWidget::update();
}

/////
/// \brief RVWidget::changeLightPosY
/// \param y
///
void RVWidget::changeLightPosY(double y)
{
    scene.getLight()->setPosition(QVector3D(scene.getLight()->getPosition().x(),
                       y, scene.getLight()->getPosition().z()));
    scene.getSoleil()->setPosition(QVector3D(scene.getLight()->getPosition().x(),
                                             y, scene.getLight()->getPosition().z()));
    QOpenGLWidget::update();
}

//////
/// \brief RVWidget::changeLightPosZ
/// \param z
///
void RVWidget::changeLightPosZ(double z)
{
    scene.getLight()->setPosition(QVector3D(scene.getLight()->getPosition().x(),
                       scene.getLight()->getPosition().y(), z));
    scene.getSoleil()->setPosition(QVector3D(scene.getLight()->getPosition().x(),
                                             scene.getLight()->getPosition().y(), z));
    QOpenGLWidget::update();
}

////////
/// \brief RVWidget::changeCulling
///
void RVWidget::changeCulling()
{
    bool culling = !scene.at(selectedObject)->getCulling();
    scene.at(selectedObject)->setCulling(culling);
    QOpenGLWidget::update();
}

///////////////////
/// \brief RVWidget::changeWireframe
///
void RVWidget::changeWireframe()
{
    bool wireframe = !scene.at(selectedObject)->getWireframe();
    scene.at(selectedObject)->setWireframe(wireframe);
    QOpenGLWidget::update();
}

/////////////
/// \brief RVWidget::changeSaturation
/// \param value
///
void RVWidget::changeSaturation(int value)
{
    int gris = (int)(2.55f * value);
    scene.at(selectedObject)->setGlobalColor(QColor(gris, gris, gris));
    QOpenGLWidget::update();
}

//////////
/// \brief RVWidget::changeSkyBox
/// \param ind
///
void RVWidget::changeSkyBox(int ind)
{
    switch (ind)
    {
    case 0:
        dynamic_cast<RVSpecularCube*>(scene.getSpecCube())->setCubeTexture(":/textures/Forest/posx.jpg",
                                   ":/textures/Forest/negx.jpg",
                                   ":/textures/Forest/posy.jpg",
                                   ":/textures/Forest/negy.jpg",
                                   ":/textures/Forest/posz.jpg",
                                   ":/textures/Forest/negz.jpg"
                                   );
        dynamic_cast<RVSkyBox*>(scene.getSkybox())->setCubeTexture(":/textures/Forest/negx.jpg",
                                   ":/textures/Forest/posx.jpg",
                                   ":/textures/Forest/posy.jpg",
                                   ":/textures/Forest/negy.jpg",
                                   ":/textures/Forest/posz.jpg",
                                   ":/textures/Forest/negz.jpg"
                                   );
        break;
    case 1:
        dynamic_cast<RVSpecularCube*>(scene.getSpecCube())->setCubeTexture(":/textures/Park3/posx.jpg",
                                                                           ":/textures/Park3/negx.jpg",
                                                                           ":/textures/Park3/posy.jpg",
                                                                           ":/textures/Park3/negy.jpg",
                                                                           ":/textures/Park3/posz.jpg",
                                                                           ":/textures/Park3/negz.jpg"
                                                                           );
        dynamic_cast<RVSkyBox*>(scene.getSkybox())->setCubeTexture(":/textures/Park3/negx.jpg",
                                   ":/textures/Park3/posx.jpg",
                                   ":/textures/Park3/posy.jpg",
                                   ":/textures/Park3/negy.jpg",
                                   ":/textures/Park3/posz.jpg",
                                   ":/textures/Park3/negz.jpg"
                                   );
        break;
    case 2:
        dynamic_cast<RVSpecularCube*>(scene.getSpecCube())->setCubeTexture(":/textures/SwedishRoyalCastle/posx.jpg",
                                                                           ":/textures/SwedishRoyalCastle/negx.jpg",
                                                                           ":/textures/SwedishRoyalCastle/posy.jpg",
                                                                           ":/textures/SwedishRoyalCastle/negy.jpg",
                                                                           ":/textures/SwedishRoyalCastle/posz.jpg",
                                                                           ":/textures/SwedishRoyalCastle/negz.jpg"
                                                                           );
        dynamic_cast<RVSkyBox*>(scene.getSkybox())->setCubeTexture(":/textures/SwedishRoyalCastle/negx.jpg",
                                   ":/textures/SwedishRoyalCastle/posx.jpg",
                                   ":/textures/SwedishRoyalCastle/posy.jpg",
                                   ":/textures/SwedishRoyalCastle/negy.jpg",
                                   ":/textures/SwedishRoyalCastle/posz.jpg",
                                   ":/textures/SwedishRoyalCastle/negz.jpg"
                                   );
        break;
                /*
    case 3:
        dynamic_cast<RVSpecularCube*>(scene.getSpecCube())->setCubeTexture(":/textures/HornstullsStrand/posx.jpg",
                                                                           ":/textures/HornstullsStrand/negx.jpg",
                                                                           ":/textures/HornstullsStrand/posy.jpg",
                                                                           ":/textures/HornstullsStrand/negy.jpg",
                                                                           ":/textures/HornstullsStrand/posz.jpg",
                                                                           ":/textures/HornstullsStrand/negz.jpg"
                                                                           );
        dynamic_cast<RVSkyBox*>(scene.getSkybox())->setCubeTexture(":/textures/HornstullsStrand/negx.jpg",
                                   ":/textures/HornstullsStrand/posx.jpg",
                                   ":/textures/HornstullsStrand/posy.jpg",
                                   ":/textures/HornstullsStrand/negy.jpg",
                                   ":/textures/HornstullsStrand/posz.jpg",
                                   ":/textures/HornstullsStrand/negz.jpg"
                                   );
        break;

    case 4:
        dynamic_cast<RVSpecularCube*>(scene.getSpecCube())->setCubeTexture(":/textures/Tantolunden4/posx.jpg",
                                                                           ":/textures/Tantolunden4/negx.jpg",
                                                                           ":/textures/Tantolunden4/posy.jpg",
                                                                           ":/textures/Tantolunden4/negy.jpg",
                                                                           ":/textures/Tantolunden4/posz.jpg",
                                                                           ":/textures/Tantolunden4/negz.jpg"
                                                                           );
        dynamic_cast<RVSkyBox*>(scene.getSkybox())->setCubeTexture(":/textures/Tantolunden4/negx.jpg",
                                   ":/textures/Tantolunden4/posx.jpg",
                                   ":/textures/Tantolunden4/posy.jpg",
                                   ":/textures/Tantolunden4/negy.jpg",
                                   ":/textures/Tantolunden4/posz.jpg",
                                   ":/textures/Tantolunden4/negz.jpg"
                                   );
        break;
        */
    }
    QOpenGLWidget::update();
}

////////
/// \brief RVWidget::changeFov
/// \param fov
///
void RVWidget::changeFov(int fov)
{
    scene.getCamera()->setFov(fov);
    QOpenGLWidget::update();
}

////
/// \brief RVWidget::startAnimation
///
void RVWidget::startAnimation()
{
    animationOn = !animationOn;
}

//////////
/// \brief RVWidget::changeOpacity
/// \param val
///
void RVWidget::changeOpacity(int val)
{
    //body->setOpacity(val * 0.01f);
    scene.at(selectedObject)->setOpacity(val * 0.01f);
    QOpenGLWidget::update();
}

//////
/// \brief RVWidget::changeSize
/// \param value
///
void RVWidget::changeSize(int value)
{
    scene.at(selectedObject)->setScale(value*0.1f);
    QOpenGLWidget::update();
}

///////
/// \brief RVWidget::removeObject
/// \param ind
///
void RVWidget::removeObject(int ind)
{
    if(scene.count()>1)
        scene.removeAt(ind);
    QOpenGLWidget::update();
}



///
/// \brief RVWidget::changePosXObject
/// \param x
///
void RVWidget::changePosXObject(double x)
{
    QVector3D pos = QVector3D(x,
                              scene.at(selectedObject)->getPosition().y(),
                              scene.at(selectedObject)->getPosition().z());
    scene.at(selectedObject)->setPosition(pos);
}

///
/// \brief RVWidget::changePosYObject
/// \param y
///
void RVWidget::changePosYObject(double y)
{
    QVector3D pos = QVector3D(scene.at(selectedObject)->getPosition().x(),
        y, scene.at(selectedObject)->getPosition().z());
scene.at(selectedObject)->setPosition(pos);
}

///
/// \brief RVWidget::changePosZObject
/// \param z
///
void RVWidget::changePosZObject(double z)
{
    QVector3D pos = QVector3D(scene.at(selectedObject)->getPosition().x(),
        scene.at(selectedObject)->getPosition().y(), z);
scene.at(selectedObject)->setPosition(pos);
}





//////////////////////////////// Events //////////////////////////////////
///
////
/// \brief RVWidget::mousePressEvent
/// \param event
///
void RVWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->position();
}

/////
/// \brief RVWidget::mouseMoveEvent
/// \param event
///
void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = (event->position().x() - oldPos.x()) / width();
    float dy = (event->position().y() - oldPos.y()) / height();
    if (event->buttons() & Qt::LeftButton) {
        //float xAngle = 180 * dy;
        //float yAngle = 180 * dx;
        //scene.at(0)->rotate(yAngle, QVector3D(0, 1, 0));
        //scene.at(0)->rotate(xAngle, QVector3D(1, 0, 0));
        float phi = dynamic_cast<RVSphericalCamera*>(scene.getCamera())->getPhi();
        float theta = dynamic_cast<RVSphericalCamera*>(scene.getCamera())->getTheta();
        dynamic_cast<RVSphericalCamera*>(scene.getCamera())->setPhi(phi + dy );
        dynamic_cast<RVSphericalCamera*>(scene.getCamera())->setTheta(theta + dx);

        QOpenGLWidget::update();
    }
    oldPos = event->pos();
}

////
/// \brief RVWidget::keyPressEvent
/// \param event
///
void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = scene.getCamera()->getPosition();
    float delta = 0.2f;
    switch (event->key())
    {
    case Qt::Key_Left:
        camPos.setX(camPos.x() - delta);
        break;
    case Qt::Key_Right:
        camPos.setX(camPos.x() + delta);
        break;
    case Qt::Key_Up:
        camPos.setY(camPos.y() + delta);
        break;
    case Qt::Key_Down:
        camPos.setY(camPos.y() - delta);
        break;
    }
    scene.getCamera()->setPosition(camPos);
    QOpenGLWidget::update();
}

////
/// \brief RVWidget::wheelEvent
/// \param event
///
void RVWidget::wheelEvent(QWheelEvent *event)
{

    float camRho = dynamic_cast<RVSphericalCamera*>(scene.getCamera())->getRho();
    float numStep = (event->angleDelta().y() / 8) / 15;
    camRho += numStep;
    dynamic_cast<RVSphericalCamera*>(scene.getCamera())->setRho(camRho);
    QOpenGLWidget::update();
}






/////////////////////////////////////// Getter and Setter/////////////////
/// \brief RVWidget::getScene
/// \return
///
const RVScene &RVWidget::getScene() const
{
    return scene;
}

//////
/// \brief RVWidget::getSelectedObject
/// \return
///
const int &RVWidget::getSelectedObject() const
{
    return selectedObject;
}

///////
/// \brief RVWidget::setSelectedObject
/// \param newSelectedObject
///
void RVWidget::setSelectedObject(const int &newSelectedObject)
{
    selectedObject = newSelectedObject;
}


//////
/// \brief RVWidget::getImage
/// \return
///
QImage RVWidget::getImage()
{

    makeCurrent();
    QOpenGLFramebufferObject * fbo = new QOpenGLFramebufferObject(this->width(), this->height());
    fbo->setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fbo->bind();
    glViewport(0, 0, this->width(), this->height());
    paintGL();
    QImage img(fbo->toImage(true));
    fbo->release();
    return QImage(img.constBits(), img.width(), img.height(), QImage::Format_ARGB32);
}

double RVWidget::getRadius() const
{
    return radius;
}

void RVWidget::setRadius(double newRadius)
{
    radius = newRadius;
}

double RVWidget::getRotateSoleil() const
{
    return rotateSoleil;
}

void RVWidget::setRotateSoleil(double newRotateSoleil)
{
    rotateSoleil = newRotateSoleil;
}

