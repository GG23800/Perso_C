/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QLabel *label_R0;
    QLineEdit *lineEdit_R0;
    QLabel *label_Rf;
    QLineEdit *lineEdit_Rf;
    QLabel *label_dec;
    QLineEdit *lineEdit_dec;
    QLabel *label_Nline;
    QLineEdit *lineEdit_Nline;
    QLineEdit *lineEdit_sector;
    QLabel *label_sector;
    QLabel *label_mode;
    QPushButton *pushButton_edit;
    QPushButton *pushButton_change;
    QComboBox *comboBox_mode;
    QLabel *label_image_settings;
    QLabel *label;
    QLabel *label_gain0;
    QLineEdit *lineEdit_gain0;
    QLineEdit *lineEdit_gainf;
    QLabel *label_gainf;
    QPushButton *pushButton_change_gain;
    QPushButton *pushButton_edit_gain;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QStringLiteral("Settings"));
        Settings->resize(829, 278);
        label_R0 = new QLabel(Settings);
        label_R0->setObjectName(QStringLiteral("label_R0"));
        label_R0->setGeometry(QRect(20, 44, 71, 16));
        lineEdit_R0 = new QLineEdit(Settings);
        lineEdit_R0->setObjectName(QStringLiteral("lineEdit_R0"));
        lineEdit_R0->setEnabled(false);
        lineEdit_R0->setGeometry(QRect(90, 40, 51, 22));
        lineEdit_R0->setMaxLength(3);
        label_Rf = new QLabel(Settings);
        label_Rf->setObjectName(QStringLiteral("label_Rf"));
        label_Rf->setGeometry(QRect(20, 74, 81, 16));
        lineEdit_Rf = new QLineEdit(Settings);
        lineEdit_Rf->setObjectName(QStringLiteral("lineEdit_Rf"));
        lineEdit_Rf->setEnabled(false);
        lineEdit_Rf->setGeometry(QRect(90, 70, 51, 22));
        lineEdit_Rf->setMaxLength(3);
        label_dec = new QLabel(Settings);
        label_dec->setObjectName(QStringLiteral("label_dec"));
        label_dec->setGeometry(QRect(20, 104, 91, 16));
        lineEdit_dec = new QLineEdit(Settings);
        lineEdit_dec->setObjectName(QStringLiteral("lineEdit_dec"));
        lineEdit_dec->setEnabled(false);
        lineEdit_dec->setGeometry(QRect(110, 100, 51, 22));
        lineEdit_dec->setMaxLength(2);
        label_Nline = new QLabel(Settings);
        label_Nline->setObjectName(QStringLiteral("label_Nline"));
        label_Nline->setGeometry(QRect(20, 134, 111, 16));
        lineEdit_Nline = new QLineEdit(Settings);
        lineEdit_Nline->setObjectName(QStringLiteral("lineEdit_Nline"));
        lineEdit_Nline->setEnabled(false);
        lineEdit_Nline->setGeometry(QRect(130, 130, 51, 22));
        lineEdit_Nline->setMaxLength(3);
        lineEdit_sector = new QLineEdit(Settings);
        lineEdit_sector->setObjectName(QStringLiteral("lineEdit_sector"));
        lineEdit_sector->setEnabled(false);
        lineEdit_sector->setGeometry(QRect(160, 160, 51, 22));
        lineEdit_sector->setMaxLength(3);
        label_sector = new QLabel(Settings);
        label_sector->setObjectName(QStringLiteral("label_sector"));
        label_sector->setGeometry(QRect(20, 164, 131, 16));
        label_mode = new QLabel(Settings);
        label_mode->setObjectName(QStringLiteral("label_mode"));
        label_mode->setGeometry(QRect(20, 194, 171, 16));
        pushButton_edit = new QPushButton(Settings);
        pushButton_edit->setObjectName(QStringLiteral("pushButton_edit"));
        pushButton_edit->setGeometry(QRect(60, 230, 80, 22));
        pushButton_change = new QPushButton(Settings);
        pushButton_change->setObjectName(QStringLiteral("pushButton_change"));
        pushButton_change->setGeometry(QRect(170, 230, 111, 22));
        comboBox_mode = new QComboBox(Settings);
        comboBox_mode->setObjectName(QStringLiteral("comboBox_mode"));
        comboBox_mode->setEnabled(false);
        comboBox_mode->setGeometry(QRect(190, 190, 101, 22));
        label_image_settings = new QLabel(Settings);
        label_image_settings->setObjectName(QStringLiteral("label_image_settings"));
        label_image_settings->setGeometry(QRect(70, 10, 101, 16));
        label = new QLabel(Settings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(420, 10, 131, 16));
        label_gain0 = new QLabel(Settings);
        label_gain0->setObjectName(QStringLiteral("label_gain0"));
        label_gain0->setGeometry(QRect(400, 44, 111, 16));
        lineEdit_gain0 = new QLineEdit(Settings);
        lineEdit_gain0->setObjectName(QStringLiteral("lineEdit_gain0"));
        lineEdit_gain0->setEnabled(false);
        lineEdit_gain0->setGeometry(QRect(510, 40, 51, 22));
        lineEdit_gain0->setMaxLength(4);
        lineEdit_gainf = new QLineEdit(Settings);
        lineEdit_gainf->setObjectName(QStringLiteral("lineEdit_gainf"));
        lineEdit_gainf->setEnabled(false);
        lineEdit_gainf->setGeometry(QRect(510, 70, 51, 22));
        lineEdit_gainf->setMaxLength(4);
        label_gainf = new QLabel(Settings);
        label_gainf->setObjectName(QStringLiteral("label_gainf"));
        label_gainf->setGeometry(QRect(400, 74, 101, 16));
        pushButton_change_gain = new QPushButton(Settings);
        pushButton_change_gain->setObjectName(QStringLiteral("pushButton_change_gain"));
        pushButton_change_gain->setGeometry(QRect(520, 110, 111, 22));
        pushButton_edit_gain = new QPushButton(Settings);
        pushButton_edit_gain->setObjectName(QStringLiteral("pushButton_edit_gain"));
        pushButton_edit_gain->setGeometry(QRect(410, 110, 80, 22));

        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Dialog", Q_NULLPTR));
        label_R0->setText(QApplication::translate("Settings", "R0 (mm) =", Q_NULLPTR));
        lineEdit_R0->setText(QApplication::translate("Settings", "0", Q_NULLPTR));
        label_Rf->setText(QApplication::translate("Settings", "Rf (mm) =", Q_NULLPTR));
        lineEdit_Rf->setText(QApplication::translate("Settings", "0", Q_NULLPTR));
        label_dec->setText(QApplication::translate("Settings", "Decimation =", Q_NULLPTR));
        lineEdit_dec->setText(QApplication::translate("Settings", "1", Q_NULLPTR));
        label_Nline->setText(QApplication::translate("Settings", "Number of line =", Q_NULLPTR));
        lineEdit_Nline->setText(QApplication::translate("Settings", "1", Q_NULLPTR));
        lineEdit_sector->setText(QApplication::translate("Settings", "0", Q_NULLPTR));
        label_sector->setText(QApplication::translate("Settings", "Angle of the sector =", Q_NULLPTR));
        label_mode->setText(QApplication::translate("Settings", "Type of data send via TCP:", Q_NULLPTR));
        pushButton_edit->setText(QApplication::translate("Settings", "Edit settings", Q_NULLPTR));
        pushButton_change->setText(QApplication::translate("Settings", "Change settings", Q_NULLPTR));
        label_image_settings->setText(QApplication::translate("Settings", "Image settings", Q_NULLPTR));
        label->setText(QApplication::translate("Settings", "Gain settings", Q_NULLPTR));
        label_gain0->setText(QApplication::translate("Settings", "Gain at R0 (V) =", Q_NULLPTR));
        lineEdit_gain0->setText(QApplication::translate("Settings", "0", Q_NULLPTR));
        lineEdit_gainf->setText(QApplication::translate("Settings", "0", Q_NULLPTR));
        label_gainf->setText(QApplication::translate("Settings", "Gain at Rf (V) =", Q_NULLPTR));
        pushButton_change_gain->setText(QApplication::translate("Settings", "Change settings", Q_NULLPTR));
        pushButton_edit_gain->setText(QApplication::translate("Settings", "Edit settings", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
