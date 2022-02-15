#include "rvbody.h"

#include <QMessageBox>

RVBody::RVBody() : QOpenGLFunctions(),
    program(), vao(),
    position(), orientation()
{
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);


    vbo.create();
    //ibo.create();
    vao.create();
    program.create();

    numVertices = 0;
    numTriangles = 0;
    numIndices = 0;

    VSFile = "";
    FSFile = "";
}

RVBody::~RVBody()
{
    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    vao.destroy();
    //ibo.destroy();
    vbo.destroy();
}

void RVBody::initialize()
{
    initializeShader();
    initializeBuffer();
    initializeVAO();
}

void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();

    bool resultat;
    program.bind();

    //Vertex Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Vertex, VSFile);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Fragment, FSFile);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Link
    resultat = program.link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    program.release();
}

QMatrix4x4 RVBody::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(position);
    model.rotate(orientation);

    model.rotate(angleX,1, 0, 0 );
    model.rotate(angleY,0, 1, 0 );
    model.rotate(angleZ,0, 0, 1 );

    //orientation = QQuaternion(); //reinisialisation
    return model;
}

void RVBody::translate(QVector3D position)
{
    this->position += position;
}

void RVBody::rotate(float angle, QVector3D axis)
{

    if(axis == QVector3D(1,0,0)){
        angleX = angle;
    }else if (axis == QVector3D(0,1,0)){
        angleY = angle;
    }else{
        angleZ = angle;
    }
    //orientation = QQuaternion::fromAxisAndAngle( axis,angle);
}

void RVBody::setOrientation(float yaw, float pitch, float roll)
{
    orientation = QQuaternion::fromEulerAngles(pitch, yaw, roll);
}

///////////////////// GETTER AND SETTER

int RVBody::getNumVertices() const
{
    return numVertices;
}

int RVBody::getNumTriangles() const
{
    return numTriangles;
}

int RVBody::getNumIndices() const
{
    return numIndices;
}

RVCamera *RVBody::getCamera() const
{
    return camera;
}

void RVBody::setCamera(RVCamera *newCamera)
{
    camera = newCamera;
}

const QVector3D &RVBody::getPosition() const
{
    return position;
}

void RVBody::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

const QQuaternion &RVBody::getOrientation() const
{
    return orientation;
}

void RVBody::setOrientation(const QQuaternion &newOrientation)
{
    orientation = newOrientation;
}

const QString &RVBody::getVSFile() const
{
    return VSFile;
}

void RVBody::setVSFile(const QString &newVSFile)
{
    VSFile = newVSFile;
}

const QString &RVBody::getFSFile() const
{
    return FSFile;
}

void RVBody::setFSFile(const QString &newFSFile)
{
    FSFile = newFSFile;
}

void RVBody::setOpacity(int newOpacity)
{
    opacity = newOpacity;
}
