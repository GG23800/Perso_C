/********************************************************************************
** Form generated from reading UI file 'tcpparameterwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPPARAMETERWINDOW_H
#define UI_TCPPARAMETERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TcpParameterWindow
{
public:
    QPushButton *ButtonDeconnexion;
    QPushButton *ButtonConnexion;
    QLabel *label_ip;
    QLabel *label_port;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QLineEdit *color_box_conn;
    QLabel *label_conn;

    void setupUi(QDialog *TcpParameterWindow)
    {
        if (TcpParameterWindow->objectName().isEmpty())
            TcpParameterWindow->setObjectName(QStringLiteral("TcpParameterWindow"));
        TcpParameterWindow->resize(251, 184);
        ButtonDeconnexion = new QPushButton(TcpParameterWindow);
        ButtonDeconnexion->setObjectName(QStringLiteral("ButtonDeconnexion"));
        ButtonDeconnexion->setGeometry(QRect(130, 100, 80, 22));
        ButtonConnexion = new QPushButton(TcpParameterWindow);
        ButtonConnexion->setObjectName(QStringLiteral("ButtonConnexion"));
        ButtonConnexion->setGeometry(QRect(20, 100, 80, 22));
        label_ip = new QLabel(TcpParameterWindow);
        label_ip->setObjectName(QStringLiteral("label_ip"));
        label_ip->setGeometry(QRect(47, 24, 59, 14));
        label_port = new QLabel(TcpParameterWindow);
        label_port->setObjectName(QStringLiteral("label_port"));
        label_port->setGeometry(QRect(31, 54, 59, 14));
        lineEdit_ip = new QLineEdit(TcpParameterWindow);
        lineEdit_ip->setObjectName(QStringLiteral("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(70, 20, 113, 22));
        lineEdit_port = new QLineEdit(TcpParameterWindow);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(70, 50, 113, 22));
        color_box_conn = new QLineEdit(TcpParameterWindow);
        color_box_conn->setObjectName(QStringLiteral("color_box_conn"));
        color_box_conn->setGeometry(QRect(20, 140, 21, 22));
        label_conn = new QLabel(TcpParameterWindow);
        label_conn->setObjectName(QStringLiteral("label_conn"));
        label_conn->setGeometry(QRect(50, 144, 111, 16));

        retranslateUi(TcpParameterWindow);

        QMetaObject::connectSlotsByName(TcpParameterWindow);
    } // setupUi

    void retranslateUi(QDialog *TcpParameterWindow)
    {
        TcpParameterWindow->setWindowTitle(QApplication::translate("TcpParameterWindow", "Dialog", Q_NULLPTR));
        ButtonDeconnexion->setText(QApplication::translate("TcpParameterWindow", "Deconnexion", Q_NULLPTR));
        ButtonConnexion->setText(QApplication::translate("TcpParameterWindow", "Connexion", Q_NULLPTR));
        label_ip->setText(QApplication::translate("TcpParameterWindow", "IP:", Q_NULLPTR));
        label_port->setText(QApplication::translate("TcpParameterWindow", "Port:", Q_NULLPTR));
        lineEdit_ip->setText(QApplication::translate("TcpParameterWindow", "192.168.128.3", Q_NULLPTR));
        lineEdit_port->setText(QApplication::translate("TcpParameterWindow", "7538", Q_NULLPTR));
        label_conn->setText(QApplication::translate("TcpParameterWindow", "Connexion state", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpParameterWindow: public Ui_TcpParameterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPPARAMETERWINDOW_H
