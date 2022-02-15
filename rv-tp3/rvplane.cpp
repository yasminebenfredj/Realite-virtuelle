#include "rvplane.h"

RVPlane::RVPlane(float newLength, float newWidth)
    :RVBody()
{
    width = newWidth;
    length = newLength;
    globalColor = QColor(0, 255, 0);

    FSFileName = ":/shaders/FS_plan_texture.fsh";
}


void RVPlane::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    //Réglages OpenGL pour les textures
    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        texture->bind();
    }

    program.bind();
    vao.bind();

    //Définition des variables uniformes
    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("texture0", 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVPlane::initializeBuffer()
{
    float w = width/2;
    float l = length/2;
    //Definitions des 4 sommets du plan
    QVector3D A(-l, 0, w);
    QVector3D B(l, 0, w);
    QVector3D C(l, 0, -w);
    QVector3D D(-l, 0, -w);

    QVector2D SW(0, 0);
    QVector2D SE(1, 0);
    QVector2D NE(1, 1);
    QVector2D NW(0, 1);

    //Tableau des données : 4 sommets RVVertex
    RVVertex vertexData[] = {
        RVVertex(A, SW),
        RVVertex(B, SE),
        RVVertex(C, NE),
        RVVertex(D, NW)
    };


    //Initialisation du Vertex Buffer Object
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    vbo.create();
    //Lien du VBO avec le contexte de rendu OpenGL
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();

    numVertices = 4;
    numTriangles = 2;
    numIndices = 0;
}

float RVPlane::getLength() const
{
    return length;
}

void RVPlane::setLength(float newLength)
{
    length = newLength;
}

float RVPlane::getWidth() const
{
    return width;
}

void RVPlane::setWidth(float newWidth)
{
    width = newWidth;
}


