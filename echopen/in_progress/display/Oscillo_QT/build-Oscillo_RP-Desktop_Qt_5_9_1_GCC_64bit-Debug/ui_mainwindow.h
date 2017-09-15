/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTCP_parameters;
    QAction *actionSettings_of_the_image;
    QWidget *centralWidget;
    QLineEdit *ColorBox;
    QLabel *Label_connection;
    QCustomPlot *customPlot;
    QCustomPlot *gain_plot;
    QSlider *G1;
    QSlider *G2;
    QSlider *G3;
    QSlider *G4;
    QSlider *G5;
    QSlider *G6;
    QSlider *G7;
    QSlider *G8;
    QSlider *G9;
    QSlider *G10;
    QSlider *G11;
    QRadioButton *radio_linear_gain;
    QRadioButton *radio_custom_gain;
    QLineEdit *GT1;
    QLineEdit *GT2;
    QLineEdit *GT3;
    QLineEdit *GT4;
    QLineEdit *GT5;
    QLineEdit *GT6;
    QLineEdit *GT7;
    QLineEdit *GT8;
    QLineEdit *GT9;
    QLineEdit *GT10;
    QLineEdit *GT11;
    QPushButton *pushButton;
    QCheckBox *checkBox_set_gain;
    QCheckBox *checkBox_substract_offset;
    QLabel *label_offset;
    QLineEdit *lineEdit_offset;
    QPushButton *pushButton_offset;
    QPushButton *pushButton_freeze;
    QCheckBox *checkBox_auto;
    QCheckBox *checkBox_fix;
    QLabel *label_ymax;
    QLineEdit *lineEdit_ymax;
    QSlider *verticalSlider_ymax;
    QSlider *verticalSlider_ymin;
    QLabel *label_ymin;
    QLineEdit *lineEdit_ymin;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(927, 643);
        actionTCP_parameters = new QAction(MainWindow);
        actionTCP_parameters->setObjectName(QStringLiteral("actionTCP_parameters"));
        actionSettings_of_the_image = new QAction(MainWindow);
        actionSettings_of_the_image->setObjectName(QStringLiteral("actionSettings_of_the_image"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ColorBox = new QLineEdit(centralWidget);
        ColorBox->setObjectName(QStringLiteral("ColorBox"));
        ColorBox->setEnabled(false);
        ColorBox->setGeometry(QRect(10, 10, 21, 21));
        Label_connection = new QLabel(centralWidget);
        Label_connection->setObjectName(QStringLiteral("Label_connection"));
        Label_connection->setGeometry(QRect(40, 10, 111, 16));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(50, 80, 581, 221));
        gain_plot = new QCustomPlot(centralWidget);
        gain_plot->setObjectName(QStringLiteral("gain_plot"));
        gain_plot->setGeometry(QRect(50, 330, 581, 121));
        G1 = new QSlider(centralWidget);
        G1->setObjectName(QStringLiteral("G1"));
        G1->setGeometry(QRect(100, 460, 16, 61));
        G1->setOrientation(Qt::Vertical);
        G2 = new QSlider(centralWidget);
        G2->setObjectName(QStringLiteral("G2"));
        G2->setGeometry(QRect(151, 460, 16, 61));
        G2->setOrientation(Qt::Vertical);
        G3 = new QSlider(centralWidget);
        G3->setObjectName(QStringLiteral("G3"));
        G3->setGeometry(QRect(202, 460, 16, 61));
        G3->setOrientation(Qt::Vertical);
        G4 = new QSlider(centralWidget);
        G4->setObjectName(QStringLiteral("G4"));
        G4->setGeometry(QRect(253, 460, 16, 61));
        G4->setOrientation(Qt::Vertical);
        G5 = new QSlider(centralWidget);
        G5->setObjectName(QStringLiteral("G5"));
        G5->setGeometry(QRect(304, 460, 16, 61));
        G5->setOrientation(Qt::Vertical);
        G6 = new QSlider(centralWidget);
        G6->setObjectName(QStringLiteral("G6"));
        G6->setGeometry(QRect(355, 460, 16, 61));
        G6->setOrientation(Qt::Vertical);
        G7 = new QSlider(centralWidget);
        G7->setObjectName(QStringLiteral("G7"));
        G7->setGeometry(QRect(406, 460, 16, 61));
        G7->setOrientation(Qt::Vertical);
        G8 = new QSlider(centralWidget);
        G8->setObjectName(QStringLiteral("G8"));
        G8->setGeometry(QRect(457, 460, 16, 61));
        G8->setOrientation(Qt::Vertical);
        G9 = new QSlider(centralWidget);
        G9->setObjectName(QStringLiteral("G9"));
        G9->setGeometry(QRect(508, 460, 16, 61));
        G9->setOrientation(Qt::Vertical);
        G10 = new QSlider(centralWidget);
        G10->setObjectName(QStringLiteral("G10"));
        G10->setGeometry(QRect(559, 460, 16, 61));
        G10->setOrientation(Qt::Vertical);
        G11 = new QSlider(centralWidget);
        G11->setObjectName(QStringLiteral("G11"));
        G11->setGeometry(QRect(610, 460, 16, 61));
        G11->setOrientation(Qt::Vertical);
        radio_linear_gain = new QRadioButton(centralWidget);
        radio_linear_gain->setObjectName(QStringLiteral("radio_linear_gain"));
        radio_linear_gain->setGeometry(QRect(680, 480, 100, 20));
        radio_linear_gain->setChecked(true);
        radio_custom_gain = new QRadioButton(centralWidget);
        radio_custom_gain->setObjectName(QStringLiteral("radio_custom_gain"));
        radio_custom_gain->setGeometry(QRect(820, 480, 100, 20));
        radio_custom_gain->setChecked(false);
        GT1 = new QLineEdit(centralWidget);
        GT1->setObjectName(QStringLiteral("GT1"));
        GT1->setGeometry(QRect(88, 530, 41, 22));
        GT2 = new QLineEdit(centralWidget);
        GT2->setObjectName(QStringLiteral("GT2"));
        GT2->setGeometry(QRect(139, 530, 41, 22));
        GT3 = new QLineEdit(centralWidget);
        GT3->setObjectName(QStringLiteral("GT3"));
        GT3->setGeometry(QRect(190, 530, 41, 22));
        GT4 = new QLineEdit(centralWidget);
        GT4->setObjectName(QStringLiteral("GT4"));
        GT4->setGeometry(QRect(241, 530, 41, 22));
        GT5 = new QLineEdit(centralWidget);
        GT5->setObjectName(QStringLiteral("GT5"));
        GT5->setGeometry(QRect(292, 530, 41, 22));
        GT6 = new QLineEdit(centralWidget);
        GT6->setObjectName(QStringLiteral("GT6"));
        GT6->setGeometry(QRect(343, 530, 41, 22));
        GT7 = new QLineEdit(centralWidget);
        GT7->setObjectName(QStringLiteral("GT7"));
        GT7->setGeometry(QRect(394, 530, 41, 22));
        GT8 = new QLineEdit(centralWidget);
        GT8->setObjectName(QStringLiteral("GT8"));
        GT8->setGeometry(QRect(445, 530, 41, 22));
        GT9 = new QLineEdit(centralWidget);
        GT9->setObjectName(QStringLiteral("GT9"));
        GT9->setGeometry(QRect(497, 530, 41, 22));
        GT10 = new QLineEdit(centralWidget);
        GT10->setObjectName(QStringLiteral("GT10"));
        GT10->setGeometry(QRect(547, 530, 41, 22));
        GT11 = new QLineEdit(centralWidget);
        GT11->setObjectName(QStringLiteral("GT11"));
        GT11->setGeometry(QRect(598, 530, 41, 22));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(730, 520, 131, 22));
        checkBox_set_gain = new QCheckBox(centralWidget);
        checkBox_set_gain->setObjectName(QStringLiteral("checkBox_set_gain"));
        checkBox_set_gain->setGeometry(QRect(10, 480, 85, 20));
        checkBox_substract_offset = new QCheckBox(centralWidget);
        checkBox_substract_offset->setObjectName(QStringLiteral("checkBox_substract_offset"));
        checkBox_substract_offset->setGeometry(QRect(710, 330, 121, 20));
        label_offset = new QLabel(centralWidget);
        label_offset->setObjectName(QStringLiteral("label_offset"));
        label_offset->setGeometry(QRect(710, 360, 41, 16));
        lineEdit_offset = new QLineEdit(centralWidget);
        lineEdit_offset->setObjectName(QStringLiteral("lineEdit_offset"));
        lineEdit_offset->setEnabled(false);
        lineEdit_offset->setGeometry(QRect(760, 357, 71, 22));
        pushButton_offset = new QPushButton(centralWidget);
        pushButton_offset->setObjectName(QStringLiteral("pushButton_offset"));
        pushButton_offset->setGeometry(QRect(710, 390, 121, 22));
        pushButton_freeze = new QPushButton(centralWidget);
        pushButton_freeze->setObjectName(QStringLiteral("pushButton_freeze"));
        pushButton_freeze->setGeometry(QRect(170, 10, 131, 41));
        checkBox_auto = new QCheckBox(centralWidget);
        checkBox_auto->setObjectName(QStringLiteral("checkBox_auto"));
        checkBox_auto->setGeometry(QRect(710, 80, 85, 20));
        checkBox_fix = new QCheckBox(centralWidget);
        checkBox_fix->setObjectName(QStringLiteral("checkBox_fix"));
        checkBox_fix->setGeometry(QRect(710, 100, 85, 20));
        checkBox_fix->setChecked(true);
        label_ymax = new QLabel(centralWidget);
        label_ymax->setObjectName(QStringLiteral("label_ymax"));
        label_ymax->setGeometry(QRect(680, 140, 59, 14));
        lineEdit_ymax = new QLineEdit(centralWidget);
        lineEdit_ymax->setObjectName(QStringLiteral("lineEdit_ymax"));
        lineEdit_ymax->setGeometry(QRect(739, 136, 61, 22));
        lineEdit_ymax->setMaxLength(6);
        verticalSlider_ymax = new QSlider(centralWidget);
        verticalSlider_ymax->setObjectName(QStringLiteral("verticalSlider_ymax"));
        verticalSlider_ymax->setGeometry(QRect(810, 120, 20, 51));
        verticalSlider_ymax->setOrientation(Qt::Vertical);
        verticalSlider_ymin = new QSlider(centralWidget);
        verticalSlider_ymin->setObjectName(QStringLiteral("verticalSlider_ymin"));
        verticalSlider_ymin->setGeometry(QRect(811, 184, 20, 51));
        verticalSlider_ymin->setOrientation(Qt::Vertical);
        verticalSlider_ymin->setInvertedAppearance(true);
        verticalSlider_ymin->setInvertedControls(true);
        label_ymin = new QLabel(centralWidget);
        label_ymin->setObjectName(QStringLiteral("label_ymin"));
        label_ymin->setGeometry(QRect(681, 204, 59, 14));
        lineEdit_ymin = new QLineEdit(centralWidget);
        lineEdit_ymin->setObjectName(QStringLiteral("lineEdit_ymin"));
        lineEdit_ymin->setGeometry(QRect(740, 200, 61, 22));
        lineEdit_ymin->setMaxLength(6);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 927, 19));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionTCP_parameters);
        menuMenu->addAction(actionSettings_of_the_image);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionTCP_parameters->setText(QApplication::translate("MainWindow", "TCP parameters", Q_NULLPTR));
        actionSettings_of_the_image->setText(QApplication::translate("MainWindow", "Settings of the image", Q_NULLPTR));
        Label_connection->setText(QApplication::translate("MainWindow", "Connection", Q_NULLPTR));
        radio_linear_gain->setText(QApplication::translate("MainWindow", "Linear gain", Q_NULLPTR));
        radio_custom_gain->setText(QApplication::translate("MainWindow", "Custom gain", Q_NULLPTR));
        GT1->setText(QString());
        GT2->setText(QString());
        GT3->setText(QString());
        GT4->setText(QString());
        GT5->setText(QString());
        GT6->setText(QString());
        GT7->setText(QString());
        GT8->setText(QString());
        GT9->setText(QString());
        GT10->setText(QString());
        GT11->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "Reset gain settings", Q_NULLPTR));
        checkBox_set_gain->setText(QApplication::translate("MainWindow", "Set gain", Q_NULLPTR));
        checkBox_substract_offset->setText(QApplication::translate("MainWindow", "Substract offset", Q_NULLPTR));
        label_offset->setText(QApplication::translate("MainWindow", "Offset:", Q_NULLPTR));
        lineEdit_offset->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        pushButton_offset->setText(QApplication::translate("MainWindow", "Offset calculus", Q_NULLPTR));
        pushButton_freeze->setText(QApplication::translate("MainWindow", "Freeze", Q_NULLPTR));
        checkBox_auto->setText(QApplication::translate("MainWindow", "Auto axis", Q_NULLPTR));
        checkBox_fix->setText(QApplication::translate("MainWindow", "Fix axis", Q_NULLPTR));
        label_ymax->setText(QApplication::translate("MainWindow", "y max =", Q_NULLPTR));
        lineEdit_ymax->setText(QApplication::translate("MainWindow", "1.0", Q_NULLPTR));
        label_ymin->setText(QApplication::translate("MainWindow", "y min =", Q_NULLPTR));
        lineEdit_ymin->setText(QApplication::translate("MainWindow", "-1.0", Q_NULLPTR));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
