#include "rvcube.h"

RVCube::RVCube()
    :RVBody()
{
    VSFileName = ":/shaders/VS_lit_cube.vsh";
    FSFileName = ":/shaders/FS_lit_cube.fsh";
    //VSFileName = ":/shaders/VS_simple.vsh";
    //FSFileName = ":/shaders/FS_simple.fsh";
}


void RVCube::draw()
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

    program.bind();
    vao.bind();

    //Définition de la variable uniforme
    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);

    program.setUniformValue("light_ambient_color", light->getAmbient());
    program.setUniformValue("light_diffuse_color", light->getDiffuse());
    program.setUniformValue("light_specular_color", light->getSpecular());
    program.setUniformValue("light_specular_strength", specStrength);
    program.setUniformValue("light_position", light->getPosition());
    program.setUniformValue("eye_position", camera->getPosition());


    for (int i =0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    vao.release();
    program.release();
}

QMatrix4x4 RVCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVCube::initializeBuffer()
{
    //Definitions des 8 sommets du cube
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    //Définitions des 6 couleurs primaires
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D magenta(1, 0, 1);
    QVector3D jaune(1, 1, 0);

    //Definition des nomales
    QVector3D dessus(0, 1, 0);
    QVector3D dessous(0, -1, 0);

    QVector3D avant(0, 0, 1);
    QVector3D arriere(0, 0, -1);

    QVector3D gauche(0, -1, 0);
    QVector3D droite(0, 1, 0);
    //Tableau des données : 24 sommets puis 24 couleurs
    QVector3D vertexData[] = {
        A, B, C, D, //face avant
        H, G, F, E, //face arriere
        A, D, H, E, //face gauche
        B, F, G, C, //face droite
        D, C, G, H, //face dessus
        A, E, F, B, //face dessous

        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        jaune, jaune, jaune, jaune,

        avant, avant, avant, avant,
        arriere, arriere, arriere, arriere,
        gauche, gauche, gauche, gauche,
        droite, droite, droite, droite,
        dessus, dessus, dessus, dessus,
        dessous, dessous, dessous, dessous
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

    numVertices = 24;
    numTriangles = 12;
    numIndices = 0;
}

void RVCube::initializeVAO()
{
    //Initialisation du Vertex Array Object
    program.bind();
    vao.bind();
    vbo.bind();
    ibo.bind();

    //Définition des attributs
    program.setAttributeBuffer("rv_Position",
                               GL_FLOAT,
                               0,
                               3);
    program.enableAttributeArray("rv_Position");

    program.setAttributeBuffer("rv_Color",
                               GL_FLOAT,
                               sizeof(QVector3D)*numVertices,
                               3);
    program.enableAttributeArray("rv_Color");

    program.setAttributeBuffer("rv_Normal",
                               GL_FLOAT,
                               sizeof(QVector3D)*numVertices*2,
                               3);
    program.enableAttributeArray("rv_Normal");

    //Libération
    vao.release();
    program.release();
}
