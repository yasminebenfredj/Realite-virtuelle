#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void createObjet();
    void changeSelectedObject(int objectIndex);
    void removeObject();
    void takePicture() ;
    void changeAmbientLight();
    void changeDiffuseLight();
    void changeSpectLight();
    void tournerSoleil(bool turne);
};

#endif // MAINWINDOW_H
