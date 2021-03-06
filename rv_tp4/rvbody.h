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

#include "rvlight.h"
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

    RVLight *getLight() const;
    void setLight(RVLight *newLight);

    float getSpecStrength() const;
    void setSpecStrength(float newSpecStrength);

protected:
    QString objectName;
    QString VSFileName;               //! : nom du fichier qui contient le vertex shader
    QString FSFileName;               //! : nom du fichier qui contient le fragment shader
    QOpenGLBuffer vbo;                //! : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer ibo;                //! : index buffer (optionnel) qui stocke les index ?? utiliser pour le rendu
    QOpenGLVertexArrayObject vao;     //! : vertex array object (obligatoire)
    QOpenGLShaderProgram program;     //! : shader program (obligatoire)

    QVector3D position;               //! : position de l'objet dans la sc??ne
    QQuaternion orientation;          //! : attitude de l'objet dans la sc??ne

    int numVertices;                  //! : nombre de sommets de l'objet (lecture seule)
    int numTriangles;                 //! : nombre de triangles de l'objet (lecture seule)
    int numIndices;                   //! : nombre d'index (0 si on n'utilise pas l'ibo)

    float opacity;                    //! : valeur de l'opacit?? (1 par d??faut)
    bool wireframe;                   //! : pour activer le mode fil-de-fer (false par d??faut)
    bool culling;                     //! : pour activer le culling (true par d??faut)
    float scale;                      //! : facteur d'??chelle (1.0 par d??faut)
    QColor globalColor;               //! : couleur globale de l'objet (initialis??e ?? blanc)

    RVCamera *camera;                 //! : pointeur sur la cam??ra utilis??e pour le rendu.
    QOpenGLTexture* texture;          //! : pointeur sur la texture ?? utiliser
    RVLight* light;

    float specStrength = 20.0f ;

    struct RVVertex {
    QVector3D position;         //! position du sommet
    QVector2D texCoord;         //! coordonn??es texture
    QVector3D normal;           //! vecteur normal

    RVVertex(QVector3D pos = QVector3D(),
             QVector2D tex = QVector2D(),
             QVector3D normalVector = QVector3D())
    {
        position = pos;
        texCoord = tex;
        normal = normalVector;
    }
    };
};

#endif // RVBODY_H
