#include "rvcube.h"

RVCube::RVCube() : RVBody()
{
    VSFile = ":/shaders/VS_simple.vsh";
    FSFile = ":/shaders/FS_simple.fsh";
    initialize();
}

void RVCube::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); //glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    program.bind();
    vao.bind();

    QMatrix4x4  matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

    //Commande de rendu (indexé)
    program.setUniformValue("u_Opacity", ((float) opacity)/100);

    for (size_t i=0 ;i < 6 ;i++ ) {
        glDrawArrays(GL_TRIANGLE_FAN ,i*4, 4);
    }
    vao.release();
    program.release();
}

void RVCube::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(-0.5, -0.5, 0.5);
    QVector3D B(0.5, -0.5, 0.5);
    QVector3D C(0.5, 0.5, 0.5);
    QVector3D D(-0.5, 0.5, 0.5);
    QVector3D E(-0.5, -0.5, -0.5);
    QVector3D F(0.5, -0.5, -0.5);
    QVector3D G(0.5, 0.5, -0.5);
    QVector3D H(-0.5, 0.5,-0.5);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0); //rvb
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D jaune(1, 1, 0);
    QVector3D magenta(1, 0, 1);
    QVector3D cyan(0, 1, 1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A,B,C,D,
        D,H,E,A,
        H,G,F,E,
        B,A,E,F,
        C,B,F,G,
        D,H,G,C,

        rouge, rouge, rouge, rouge,
        vert, vert, vert, vert,
        cyan , cyan , cyan , cyan,
        jaune, jaune, jaune, jaune,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,

    };

    //Lien du VBO avec le contexte de rendu OpenGL
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();

    numVertices = 4*6;
    numTriangles = 4*6;
    numIndices = 4*6;
}

void RVCube::initializeVAO()
{
    //Création et initialisation du VAO
    program.bind();
    vao.bind();
    vbo.bind();
    //ibo.bind();

    //Définition des attributs
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*numVertices, 3);
    program.enableAttributeArray("rv_Color");

    //Libération
    vao.release();

    program.release();

}


