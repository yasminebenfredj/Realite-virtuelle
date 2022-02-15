/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "rvwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    RVWidget *widgetRV;
    QVBoxLayout *verticalLayout;
    QPushButton *animationButton;
    QComboBox *directionBox;
    QFrame *line_3;
    QLabel *label;
    QDial *fov;
    QFrame *line_2;
    QLabel *labelOpacity;
    QSlider *opacitySlider;
    QFrame *line;
    QLabel *labelRotation;
    QSlider *speedSlider;
    QFrame *line_4;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setDocumentMode(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetRV = new RVWidget(centralwidget);
        widgetRV->setObjectName(QString::fromUtf8("widgetRV"));
        widgetRV->setMinimumSize(QSize(400, 300));
        widgetRV->setCursor(QCursor(Qt::CrossCursor));

        horizontalLayout->addWidget(widgetRV);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        animationButton = new QPushButton(centralwidget);
        animationButton->setObjectName(QString::fromUtf8("animationButton"));
        animationButton->setEnabled(true);
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        animationButton->setFont(font);
        animationButton->setCursor(QCursor(Qt::PointingHandCursor));
        animationButton->setCheckable(true);
        animationButton->setChecked(false);
        animationButton->setAutoRepeat(false);
        animationButton->setAutoExclusive(false);

        verticalLayout->addWidget(animationButton);

        directionBox = new QComboBox(centralwidget);
        directionBox->addItem(QString());
        directionBox->addItem(QString());
        directionBox->addItem(QString());
        directionBox->addItem(QString());
        directionBox->setObjectName(QString::fromUtf8("directionBox"));
        directionBox->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(directionBox->sizePolicy().hasHeightForWidth());
        directionBox->setSizePolicy(sizePolicy1);
        directionBox->setCursor(QCursor(Qt::PointingHandCursor));
        directionBox->setAcceptDrops(false);
        directionBox->setAutoFillBackground(false);
        directionBox->setEditable(false);
        directionBox->setIconSize(QSize(26, 26));

        verticalLayout->addWidget(directionBox);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI Historic")});
        font1.setPointSize(10);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        fov = new QDial(centralwidget);
        fov->setObjectName(QString::fromUtf8("fov"));
        fov->setMinimumSize(QSize(0, 80));
        fov->setCursor(QCursor(Qt::ClosedHandCursor));
        fov->setMouseTracking(false);
        fov->setTabletTracking(false);
        fov->setAcceptDrops(false);
        fov->setAutoFillBackground(true);
        fov->setMinimum(10);
        fov->setMaximum(120);
        fov->setSingleStep(1);
        fov->setSliderPosition(45);
        fov->setInvertedAppearance(false);
        fov->setInvertedControls(false);
        fov->setWrapping(false);
        fov->setNotchTarget(3.700000000000000);
        fov->setNotchesVisible(true);

        verticalLayout->addWidget(fov);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        labelOpacity = new QLabel(centralwidget);
        labelOpacity->setObjectName(QString::fromUtf8("labelOpacity"));
        QFont font2;
        labelOpacity->setFont(font2);
        labelOpacity->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelOpacity);

        opacitySlider = new QSlider(centralwidget);
        opacitySlider->setObjectName(QString::fromUtf8("opacitySlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(opacitySlider->sizePolicy().hasHeightForWidth());
        opacitySlider->setSizePolicy(sizePolicy2);
        opacitySlider->setCursor(QCursor(Qt::PointingHandCursor));
        opacitySlider->setAcceptDrops(false);
        opacitySlider->setAutoFillBackground(true);
        opacitySlider->setMaximum(100);
        opacitySlider->setSliderPosition(100);
        opacitySlider->setOrientation(Qt::Horizontal);
        opacitySlider->setInvertedAppearance(false);
        opacitySlider->setInvertedControls(false);

        verticalLayout->addWidget(opacitySlider);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        labelRotation = new QLabel(centralwidget);
        labelRotation->setObjectName(QString::fromUtf8("labelRotation"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        labelRotation->setPalette(palette);
        QFont font3;
        font3.setBold(false);
        labelRotation->setFont(font3);
        labelRotation->setTabletTracking(false);
        labelRotation->setTextFormat(Qt::PlainText);
        labelRotation->setScaledContents(false);
        labelRotation->setAlignment(Qt::AlignCenter);
        labelRotation->setWordWrap(false);
        labelRotation->setMargin(2);
        labelRotation->setIndent(0);

        verticalLayout->addWidget(labelRotation);

        speedSlider = new QSlider(centralwidget);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setEnabled(true);
        sizePolicy2.setHeightForWidth(speedSlider->sizePolicy().hasHeightForWidth());
        speedSlider->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setStrikeOut(false);
        speedSlider->setFont(font4);
        speedSlider->setCursor(QCursor(Qt::PointingHandCursor));
        speedSlider->setAutoFillBackground(true);
        speedSlider->setMinimum(1);
        speedSlider->setMaximum(20);
        speedSlider->setPageStep(1);
        speedSlider->setSliderPosition(3);
        speedSlider->setOrientation(Qt::Horizontal);
        speedSlider->setInvertedAppearance(false);
        speedSlider->setInvertedControls(false);

        verticalLayout->addWidget(speedSlider);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 28));
        QFont font5;
        font5.setPointSize(10);
        pushButton->setFont(font5);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(128, 188, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(animationButton, &QPushButton::clicked, widgetRV, qOverload<>(&RVWidget::startAnimation));
        QObject::connect(fov, SIGNAL(valueChanged(int)), widgetRV, SLOT(changeFov(int)));
        QObject::connect(opacitySlider, SIGNAL(valueChanged(int)), widgetRV, SLOT(changeOpacity(int)));
        QObject::connect(speedSlider, SIGNAL(valueChanged(int)), widgetRV, SLOT(changeSpeed(int)));
        QObject::connect(directionBox, SIGNAL(textActivated(QString)), widgetRV, SLOT(changeDirection(QString)));
        QObject::connect(pushButton, &QPushButton::clicked, widgetRV, qOverload<>(&RVWidget::reinitialiser));

        directionBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(accessibility)
        animationButton->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        animationButton->setText(QCoreApplication::translate("MainWindow", "Animation", nullptr));
        directionBox->setItemText(0, QCoreApplication::translate("MainWindow", "Haut", nullptr));
        directionBox->setItemText(1, QCoreApplication::translate("MainWindow", "Bas", nullptr));
        directionBox->setItemText(2, QCoreApplication::translate("MainWindow", "Gauche", nullptr));
        directionBox->setItemText(3, QCoreApplication::translate("MainWindow", "Droite", nullptr));

#if QT_CONFIG(whatsthis)
        directionBox->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Direction</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        directionBox->setAccessibleName(QCoreApplication::translate("MainWindow", "Direction de l'animation", nullptr));
#endif // QT_CONFIG(accessibility)
        label->setText(QCoreApplication::translate("MainWindow", "Ouverture focale", nullptr));
        labelOpacity->setText(QCoreApplication::translate("MainWindow", "Transparence", nullptr));
        labelRotation->setText(QCoreApplication::translate("MainWindow", "Vitesse de rotation", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser le cube", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
