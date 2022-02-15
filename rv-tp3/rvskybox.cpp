#include "rvskybox.h"

RVSkyBox::RVSkyBox()
{
    VSFileName = ":/shaders/VS_skybox_texture.vsh";
    FSFileName = ":/shaders/FS_skybox_texture.fsh";

}

void RVSkyBox::initializeBuffer()
{
    //Definitions des 8 sommets du skyBox
    QVector3D A(-1, -1, 1);
    QVector3D B(1, -1, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(-1, 1, 1);
    QVector3D E(-1, -1, -1);
    QVector3D F(1, -1, -1);
    QVector3D G(1, 1, -1);
    QVector3D H(-1, 1, -1);

    QVector3D vertexData[] = {
        D, C, B, A, //face avant
        E, F, G, H, //face arriere
        E, H, D, A, //face gauche
        C, G, F, B, //face droite
        H, G, C, D, //face dessus
        B, F, E, A, //face dessous
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

void RVSkyBox::initializeVAO()
{
    //Initialisation du Vertex Array Object
    program.bind();
    vao.bind();
    vbo.bind();
    ibo.bind();

    //Définition des attributs
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    //Libération
    vao.release();
    program.release();
}

void RVSkyBox::draw()
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
        glEnable(GL_TEXTURE_CUBE_MAP);
        glEnable(GL_TEXTURE4);
        texture->bind();
    }

    program.bind();
    vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    //program.setUniformValue("u_Opacity", opacity);
    //program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("texture4", 0);

    for (int i =0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE4);
        glDisable(GL_TEXTURE_CUBE_MAP);
    }
}

void RVSkyBox::setCubeTexture(QString leftImage,
                              QString rightImage,
                              QString frontImage,
                              QString backImage,
                              QString topImage,
                              QString bottomImage)
{
    texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    texture->create();

    QImage posX = QImage(rightImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negX = QImage(leftImage).convertToFormat(QImage::Format_RGBA8888);

    QImage posY = QImage(frontImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negY = QImage(backImage).convertToFormat(QImage::Format_RGBA8888);

    QImage posZ = QImage(topImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negZ = QImage(bottomImage).convertToFormat(QImage::Format_RGBA8888);
    texture->setSize(posX.width(), posX.height(), posX.depth());

    texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    texture->allocateStorage();

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           posX.constBits(),
                           Q_NULLPTR);
    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           negX.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           posY.constBits(),
                           Q_NULLPTR);
    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           negY.constBits(),
                           Q_NULLPTR);

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           posZ.constBits(),
                           Q_NULLPTR);
    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
                           QOpenGLTexture::RGBA,
                           QOpenGLTexture::UInt8,
                           negZ.constBits(),
                           Q_NULLPTR);

    texture->generateMipMaps();

    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}
