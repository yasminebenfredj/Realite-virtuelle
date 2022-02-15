/*!
  \file rvsurface.cpp
  \brief Définition de la classe RVSurface.
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvsurface.h"

RVSurface::RVSurface()
    :RVBody()
{
    minS = 0;
    maxS = 1;
    minT = 0;
    maxT = 1;
    numSegS = 25;
    numSegT = 25;
}

void RVSurface::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (this->wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (culling)
        glEnable(GL_CULL_FACE);
    else
         glDisable(GL_CULL_FACE);


    if (texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        texture->bind();
    }

    program.bind();
    vao.bind();

    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);
    if (texture)
        program.setUniformValue("texture0", 0);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();

    if (texture) {
        texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVSurface::initializeBuffer()
{
    numVertices = (numSegS + 1) * (numSegT + 1);
    numTriangles = 2 * numSegS * numSegT;
    numIndices = 3 * numTriangles;

    RVVertex * vertexData = new RVVertex [numVertices];
    uint* indexData = new uint[numIndices];
    double t = minT;
    double s = minS;
    double deltaT = (maxT - minT)/numSegT;
    double deltaS = (maxS - minS)/numSegS;
    uint cptPoint = 0;
    uint cptIndex = 0;
    for (int i = 0; i <= numSegT; i++, t += deltaT) {
        s = minS;
        for (int j = 0; j <= numSegS; j++, s += deltaS, cptPoint++) {
            vertexData[cptPoint].position = pos(s,t);
            vertexData[cptPoint].texCoord = QVector2D(i/float(numSegS),j/float(numSegT));
            if ((i < numSegT) && (j < numSegS)) {
                indexData[cptIndex++] = cptPoint;
                indexData[cptIndex++] = cptPoint + uint(numSegS) + 1;
                indexData[cptIndex++] = cptPoint + uint(numSegS) + 2;
                indexData[cptIndex++] = cptPoint;
                indexData[cptIndex++] = cptPoint + uint(numSegS) + 2;
                indexData[cptIndex++] = cptPoint + 1;
            }
        }
    }

    //Initialisation et remplissage du Vertex Buffer Object
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.allocate(vertexData, numVertices*int(sizeof (RVVertex)));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.release();

    //Initialisation et remplissage de l'Index Buffer Object
    ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ibo.create();
    ibo.bind();
    ibo.allocate(indexData, numIndices*int(sizeof (uint)));
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.release();
}


