#ifndef RVBODY_H
#define RVBODY_H

#include "rvcamera.h"

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>



class RVBody : protected QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw()= 0;
    virtual void initializeVAO();
    virtual void initializeBuffer()= 0;

    void initialize();
    void initializeShader();

    virtual QMatrix4x4 modelMatrix();

    int getNumVertices() const;
    int getNumTriangles() const;
    int getNumIndices() const;

    RVCamera *getCamera() const;
    void setCamera(RVCamera *newCamera);

    const QVector3D &getPosition() const;
    void setPosition(const QVector3D &newPosition);

    const QQuaternion &getOrientation() const;
    void setOrientation(const QQuaternion &newOrientation);
    void setOrientation(float yaw, float pitch, float roll);

    const QString &getVSFile() const;
    void setVSFile(const QString &newVSFile);

    const QString &getFSFile() const;
    void setFSFile(const QString &newFSFile);

    void translate(QVector3D position);
    void rotate(float angle, QVector3D axis);

    void setOpacity(int newOpacity);

    void reinitialiser();

    bool getWireframe() const;
    void setWireframe(bool newWireframe);

    bool getCulling() const;
    void setCulling(bool newCulling);


    float getScale() const;
    void setScale(float newScale);

    const QVector3D &getGlobalColor() const;
    void setGlobalColor(const QVector3D &newGlobalColor);

protected:
    QOpenGLBuffer vbo;     // vertex buffer qui stocke les sommets du maillage
    QOpenGLShaderProgram program;   // shader program
    QOpenGLVertexArrayObject vao; // vertex array object
    QOpenGLBuffer ibo;     //index buffer qui stocke les index à utiliser pour le rendu

    int numVertices;
    int numTriangles;
    int numIndices;

    QString VSFile;
    QString FSFile;

    RVCamera *camera;         // pointeur sur la caméra utilisée pour le rendu

    QVector3D position;           // position de l'objet dans la scène
    QQuaternion orientation;      // attitude de l'objet dans la scène

    int opacity = 100;
    bool wireframe;
    bool culling;

    float scale = 1;

    QVector3D globalColor = QVector3D(1, 1, 1);
};

#endif // RVBODY_H
