#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLFramebufferObject>

#include "rvbody.h"
#include "rvcamera.h"
#include "rvcube.h"
#include "rvplane.h"
#include "rvsphere.h"
#include "rvplanet.h"
#include "rvtorus.h"
#include "rvtexcube.h"
#include "rvdice.h"
#include "rvscene.h"
#include "rvsphericalcamera.h"
#include "rvskybox.h"
#include "rvlight.h"
#include "rvspecularcube.h"

class RVWidget : public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT


public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget();

    void addObject(int type, QVector3D pos, QQuaternion orientation, QString name);

    // Attributs pour le rendu
    const RVScene &getScene() const;

    const int &getSelectedObject() const;
    void setSelectedObject(const int &newSelectedObject);
    void removeObject(int ind);
    QImage  getImage();


    double getRadius() const;
    void setRadius(double newRadius);

    double getRotateSoleil() const;
    void setRotateSoleil(double newRotateSoleil);

private:

    QTimer* timer;
    float angleY;
    bool animationOn = false;
    float angleX;
    QPointF oldPos;
    RVScene scene;
    int selectedObject =0;

protected :
    double radius = 0;
    double rotateSoleil = false ;

protected slots:
    void update();

public slots:
    void startAnimation();
    void changeFov(int);
    void changeOpacity(int);
    void changeSize(int value);
    void changeSaturation(int value);
    void changeCulling();
    void changeWireframe();
    void changeSkyBox(int ind);
    void changeCoefSpec(int val);
    void changeLightPosX(double);
    void changeLightPosY(double);
    void changeLightPosZ(double);
    void afficherSoleil(bool state);
    void changePosXObject(double x);
    void changePosYObject(double y);
    void changePosZObject(double z);


    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
};
#endif // RVWIDGET_H
