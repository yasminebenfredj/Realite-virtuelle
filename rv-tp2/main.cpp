#include "rvwidget.h"

#include <QApplication>

#include "mainwindow.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow  w;
    w.setWindowTitle("Réalité Virtuelle: TP2 YASMINE BEN FREDJ");
    w.show();
    return a.exec();
}
