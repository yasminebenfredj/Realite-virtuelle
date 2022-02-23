#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createObjet()
{
    QVector3D position = QVector3D(ui->valeur_x->value(),
                                   ui->valeur_y->value(),
                                   ui->valeur_z->value());
    QQuaternion orientation = QQuaternion::fromEulerAngles(ui->valeur_roulis->value(),
                                                           ui->valeur_lacet->value(),
                                                           ui->valeur_tangage->value());
    int type = ui->valeur_type->currentIndex();
    srand (time(NULL));
    int irand = rand() % 100 + 1;
    QString name = ui->valeur_type->currentText()+QString::number(irand);
    ui->Object_selected_Box->addItem(name);
    ui->widgetRV->addObject(type, position, orientation, name);
}

void MainWindow::changeSelectedObject(int objectIndex)
{
    ui->widgetRV->setSelectedObject(objectIndex);
}

void MainWindow::removeObject()
{
    if(ui->widgetRV->getScene().count() > 1){
        int ind = ui->Object_selected_Box->currentIndex();
        ui->widgetRV->removeObject(ind);
        ui->Object_selected_Box->removeItem(ind);

        ui->widgetRV->setSelectedObject(ui->Object_selected_Box->currentIndex());
    }
}

void MainWindow::takePicture()
{
    QImage img(ui->widgetRV->getImage());
    ui->image->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::changeAmbientLight()
{
    RVLight* lumiere = ui->widgetRV->getScene().getLight();
    QColor col = QColorDialog::getColor(lumiere->getAmbient(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->button_ambiante->setStyleSheet(qss);
        lumiere->setAmbient(col);
    }
}

void MainWindow::changeDiffuseLight()
{
    RVLight* lumiere = ui->widgetRV->getScene().getLight();
    QColor col = QColorDialog::getColor(lumiere->getDiffuse(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->button_diffuse->setStyleSheet(qss);
        lumiere->setDiffuse(col);
    }
}

void MainWindow::changeSpectLight()
{
    RVLight* lumiere = ui->widgetRV->getScene().getLight();
    QColor col = QColorDialog::getColor(lumiere->getSpecular(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->button_spec->setStyleSheet(qss);
        lumiere->setSpecular(col);
    }
}

void MainWindow::tournerSoleil(bool turne)
{
    if(turne){
        double radius = ui->radius_spin->value();
        ui->widgetRV->setRadius(radius);
    }
    ui->widgetRV->setRotateSoleil(turne);
}
