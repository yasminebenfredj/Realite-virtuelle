#ifndef RVBODY_H
#define RVBODY_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QColor>

#include "rvcamera.h"

class RVBody : public QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw() = 0;
    virtual QMatrix4x4 modelMatrix();

    void initialize();
    void initializeShader();
    virtual void initializeBuffer() = 0;
    virtual void initializeVAO();

    // pour bouger l'objet
    void rotate(float angle, QVector3D axis);
    void translate(QVector3D position);
    void setOrientation(float yaw, float pitch, float roll);

    // accesseurs et mutateurs .....
    RVCamera *getCamera() const;
    void setCamera(RVCamera *newCamera);

    const QVector3D &getPosition() const;
    void setPosition(const QVector3D &newPosition);

    const QQuaternion &getOrientation() const;
    void setOrientation(const QQuaternion &newOrientation);

    int getNumVertices() const;

    int getNumTriangles() const;

    int getNumIndices() const;

    const QString &getVSFileName() const;
    void setVSFileName(const QString &newVSFileName);

    const QString &getFSFileName() const;
    void setFSFileName(const QString &newFSFileName);

    float getOpacity() const;
    void setOpacity(float newOpacity);

    bool getWireframe() const;
    void setWireframe(bool newWireframe);

    bool getCulling() const;
    void setCulling(bool newCulling);

    float getScale() const;
    void setScale(float newScale);

    const QColor &getGlobalColor() const;
    void setGlobalColor(const QColor &newGlobalColor);

    void setTexture(QString textureFilename, bool hMirror = true, bool vMirror = true);

    const QString &getObjectName() const;
    void setObjectName(const QString &newObjectName);

protected:
    QString objectName;
    QString VSFileName;               //! : nom du fichier qui contient le vertex shader
    QString FSFileName;               //! : nom du fichier qui contient le fragment shader
    QOpenGLBuffer vbo;                //! : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer ibo;                //! : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject vao;     //! : vertex array object (obligatoire)
    QOpenGLShaderProgram program;     //! : shader program (obligatoire)

    QVector3D position;               //! : position de l'objet dans la scène
    QQuaternion orientation;          //! : attitude de l'objet dans la scène

    int numVertices;                  //! : nombre de sommets de l'objet (lecture seule)
    int numTriangles;                 //! : nombre de triangles de l'objet (lecture seule)
    int numIndices;                   //! : nombre d'index (0 si on n'utilise pas l'ibo)

    float opacity;                    //! : valeur de l'opacité (1 par défaut)
    bool wireframe;                   //! : pour activer le mode fil-de-fer (false par défaut)
    bool culling;                     //! : pour activer le culling (true par défaut)
    float scale;                      //! : facteur d'échelle (1.0 par défaut)
    QColor globalColor;               //! : couleur globale de l'objet (initialisée à blanc)

    RVCamera *camera;                 //! : pointeur sur la caméra utilisée pour le rendu.
    QOpenGLTexture* texture;          //! : pointeur sur la texture à utiliser

    struct RVVertex {
        QVector3D position;         //! position du sommet
        QVector2D texCoord;         //! coordonnées texture

        RVVertex(QVector3D pos = QVector3D(), QVector2D tex = QVector2D())
        {
            position = pos;
            texCoord = tex;
        }
    };
};

#endif // RVBODY_H
