QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rvbody.cpp \
    rvcamera.cpp \
    rvcube.cpp \
    rvdice.cpp \
    rvlight.cpp \
    rvplane.cpp \
    rvplanet.cpp \
    rvscene.cpp \
    rvskybox.cpp \
    rvspecularcube.cpp \
    rvsphere.cpp \
    rvsphericalcamera.cpp \
    rvsurface.cpp \
    rvtexcube.cpp \
    rvtorus.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvbody.h \
    rvcamera.h \
    rvcube.h \
    rvdice.h \
    rvlight.h \
    rvplane.h \
    rvplanet.h \
    rvscene.h \
    rvskybox.h \
    rvspecularcube.h \
    rvsphere.h \
    rvsphericalcamera.h \
    rvsurface.h \
    rvtexcube.h \
    rvtorus.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Instruction de compilation complémentaire pour Windows
windows:LIBS += -lopengl32

DISTFILES += \
    ../Fichiers nécessaires au TP3-20220204/dice_texture.jpg \
    3d-cube-textures/container.jpg \
    3d-cube-textures/dice_texture.jpg \
    3d-cube-textures/flam.jpg \
    3d-cube-textures/pierre.jpg \
    FS_simple.fsh \
    FS_skybox_texture.fsh \
    Forest/negx.jpg \
    Forest/negy.jpg \
    Forest/negz.jpg \
    Forest/posx.jpg \
    Forest/posy.jpg \
    Forest/posz.jpg \
    Tantolunden4/negx.jpg \
    Tantolunden4/negy.jpg \
    Tantolunden4/negz.jpg \
    Tantolunden4/posx.jpg \
    Tantolunden4/posy.jpg \
    Tantolunden4/posz.jpg \
    VS_simple.vsh \
    VS_skybox_texture.vsh \
    gold.jfif \
    planet.jpg \
    planet2.jpg \
    polytech_logo.jpg \
    silver.jpg \
    sol2.jpg

RESOURCES += \
    RVResources.qrc

FORMS += \
    mainwindow.ui
