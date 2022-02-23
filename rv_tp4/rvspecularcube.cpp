#include "rvspecularcube.h"

RVSpecularCube::RVSpecularCube()
{

    VSFileName = ":/shaders/VS_lit_texture_cube.vsh";
    FSFileName = ":/shaders/FS_lit_specular_cube.fsh";
}




void RVSpecularCube::setCubeTexture(QString leftImage,
                              QString rightImage,
                              QString frontImage,
                              QString backImage,
                              QString topImage,
                              QString bottomImage)
{
    texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    texture->create();

    QImage posX = QImage(leftImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negX = QImage(rightImage).convertToFormat(QImage::Format_RGBA8888);

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




void RVSpecularCube::draw()
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
        //Liaison de la texture
        texture->bind();
    }

    program.bind();
    vao.bind();

    //Définition de la variable uniforme
    program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    program.setUniformValue("u_ViewMatrix", camera->viewMatrix());
    program.setUniformValue("u_ProjectionMatrix", camera->projectionMatrix());
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    program.setUniformValue("skybox", 0);

    program.setUniformValue("eye_position", camera->getPosition());

    for (int i =0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE_CUBE_MAP);
    }
}
