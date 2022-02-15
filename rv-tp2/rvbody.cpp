#include "rvbody.h"

#include <QMessageBox>

RVBody::RVBody() : QOpenGLFunctions(),
    program(), vao(), position(), orientation()
{
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);


    vbo.create();
    ibo.create();
    vao.create();
    program.create();

    numVertices = 0;
    numTriangles = 0;
    numIndices = 0;
    wireframe = false;
    culling = false;

    scale = 1.0f;
    globalColor = QVector3D(1, 1, 1);

    VSFile = ":/shaders/VS_simpler.vsh";
    FSFile = ":/shaders/FS_simple.fsh";
}

RVBody::~RVBody()
{
    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    vao.destroy();
    ibo.destroy();
    vbo.destroy();
}

void RVBody::initializeVAO()
{
    //Initialisation du VAO
    //vao.create();
    vao.bind();
    vbo.bind();
    //ibo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    //Libération
    vao.release();
    program.release();
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
    model.scale(scale);
    return model;
}


void RVBody::translate(QVector3D position)
{
    this->position += position;
}

void RVBody::rotate(float angle, QVector3D axis)
{
    orientation = QQuaternion::fromAxisAndAngle( axis,angle)*orientation;
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

void RVBody::reinitialiser()
{
    orientation = QQuaternion(); //reinisialisation
}

bool RVBody::getWireframe() const
{
    return wireframe;
}

void RVBody::setWireframe(bool newWireframe)
{
    wireframe = newWireframe;
}

bool RVBody::getCulling() const
{
    return culling;
}

void RVBody::setCulling(bool newCulling)
{
    culling = newCulling;
}

float RVBody::getScale() const
{
    return scale;
}

void RVBody::setScale(float newScale)
{
    scale = newScale;
}

const QVector3D &RVBody::getGlobalColor() const
{
    return globalColor;
}

void RVBody::setGlobalColor(const QVector3D &newGlobalColor)
{
    globalColor = newGlobalColor;
}
