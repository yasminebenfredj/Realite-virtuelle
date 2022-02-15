#include "rvplane.h"

RVPlane::RVPlane() :  RVBody()
{
    initialize();
    longX = 10; //longueur
    longZ = 10; //largeur
    FSFile = ":/shaders/FS_plan.fsh";
    globalColor = QVector3D(0.2, 0.8, 0.2);
}

void RVPlane::draw()
{
    glFrontFace(GL_CCW); //glFrontFace(GL_CW);
    if(wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if(culling){
        glEnable(GL_CULL_FACE);
        //glCullFace(GL_FRONT);
    }else{
        glDisable(GL_CULL_FACE);
    }


    program.bind();
    vao.bind();

    QMatrix4x4  matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();

    program.setUniformValue("u_Opacity", ((float) opacity)/100);
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_color", globalColor);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    vao.release();
    program.release();
}

QMatrix4x4 RVPlane::modelMatrix()
{
    QMatrix4x4 model;
    return RVBody::modelMatrix() * model;
}

void RVPlane::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(-longX/2, 0, -longZ/2);
    QVector3D B(-longX/2, 0, longZ/2);
    QVector3D C(longX/2, 0, longZ/2);
    QVector3D D(longX/2, 0, -longZ/2);
    QVector3D vertexData[] = {
        A,B,C,D
    };
    //Lien du VBO avec le contexte de rendu OpenGL
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();

    numVertices = 4;
    numIndices = 4;

}


int RVPlane::getLongX() const
{
    return longX;
}

int RVPlane::getLongZ() const
{
    return longZ;
}
