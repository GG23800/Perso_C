#include "settings.h"
#include "ui_settings.h"
#include "./src_RP/TCP_API.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->comboBox_mode->addItem("int16_t", 0);
    ui->comboBox_mode->addItem("char", 1);
    ui->comboBox_mode->addItem("double", 2);
    ui->comboBox_mode->setCurrentIndex(1);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::init_settings(char set[])
{
    R0=int_converter(set[0]);
    ui->lineEdit_R0->setText(QString::number(R0));
    Rf=int_converter(set[1]);
    ui->lineEdit_Rf->setText(QString::number(Rf));
    dec=int_converter(set[2]);
    ui->lineEdit_dec->setText(QString::number(dec));
    Nline=int_converter(set[3]);
    ui->lineEdit_Nline->setText(QString::number(Nline));
    sector=int_converter(set[4]);
    ui->lineEdit_sector->setText(QString::number(sector));
    mode=int_converter(set[5]);
    ui->comboBox_mode->setCurrentIndex(mode);
    Npoint=(int)(2.0*(double)(Rf-R0)*125.0/1.48/((double)dec));
    if (Npoint>16384) {Npoint=16384;}
}

void Settings::disable_lineedit()
{
    ui->lineEdit_R0->setDisabled(true);
    ui->lineEdit_Rf->setDisabled(true);
    ui->lineEdit_dec->setDisabled(true);
    ui->lineEdit_Nline->setDisabled(true);
    ui->lineEdit_sector->setDisabled(true);
    ui->comboBox_mode->setDisabled(true);
    ui->pushButton_change->setDisabled(true);
}

void Settings::enable_lineedit()
{
    ui->lineEdit_R0->setEnabled(true);
    ui->lineEdit_Rf->setEnabled(true);
    ui->lineEdit_dec->setEnabled(true);
    ui->lineEdit_Nline->setEnabled(true);
    ui->lineEdit_sector->setEnabled(true);
    ui->comboBox_mode->setEnabled(true);
    ui->pushButton_change->setEnabled(true);
}

void Settings::get_setting(SOCKET sck)
{
    sock=sck;
    char tmp[6];
    receive_TCP_client(&sock, tmp, 6);
    init_settings(tmp);
    emit setting_done();
}

void Settings::get_ramp(SOCKET sck)
{
    sock_ramp=sck;
    char tmp[2];
    receive_TCP_client(&sock_ramp, tmp, 2);
    int temp;
    temp=int_converter(tmp[0]);
    gain0=((double)temp)/255.0;
    ui->lineEdit_gain0->setText(QString::number(gain0));
    temp=int_converter(tmp[1]);
    gainf=((double)temp)/255.0;
    ui->lineEdit_gainf->setText(QString::number(gainf));
}

void Settings::on_pushButton_edit_gain_clicked()
{
    ui->lineEdit_gain0->setEnabled(true);
    ui->lineEdit_gainf->setEnabled(true);
}

void Settings::on_pushButton_change_gain_clicked()
{
    double gain;
    char buff[2];
    int err;
    gain=ui->lineEdit_gain0->text().toDouble();
    buff[0]=(char)(gain*255.0);
    gain=ui->lineEdit_gainf->text().toDouble();
    buff[1]=(char)(gain*255.0);
    err=send_TCP_client(&sock_ramp, buff, 2);
    if (err==1) {qDebug("socket ramp closed");}
    ui->lineEdit_gain0->setEnabled(false);
    ui->lineEdit_gainf->setEnabled(false);
}
