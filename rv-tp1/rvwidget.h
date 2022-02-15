#ifndef RVWIDGET_H
#define RVWIDGET_H

#include "rvbody.h"

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QTimer>
#include <QMouseEvent>
#include <QPointF>

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT


public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget();

private:
    float angleY ;
    float angleX ;
    QPointF oldPos ;
    QTimer* timer = new QTimer();
    boolean isClicked = false;
    int pFov = 45;

    int speed = 5;
    QString direction = "Droite";
    RVBody* body ;
    RVCamera*  camera;



protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;


private slots:
    void update();

public slots:
    void startAnimation();
    void changeFov(int fov);
    void changeOpacity(int newOpacity);
    void changeSpeed(int newSpeed);
    void changeDirection(QString newDirection);
    void reinitialiser();
    void move();
};
#endif // RVWIDGET_H
