#include "tcpparameterwindow.h"
#include "ui_tcpparameterwindow.h"
//#include <stdio.h>

TcpParameterWindow::TcpParameterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpParameterWindow)
{
    ui->setupUi(this);
    this->connected=false;
    connectedset=false;
    ui->color_box_conn->setStyleSheet("QLineEdit { background-color: gray; }");
    ui->label_conn->setText("Not connected");
    //printf("creation of a new TcpParameterWindow\n");
}

TcpParameterWindow::~TcpParameterWindow()
{
    delete ui;
    //printf("destruction of a TcpParameterWindow\n");
}

void TcpParameterWindow::connection_state(int err)
{
    if (connected==true)
    {
        switch(err) {
        case 11:
            ui->label_conn->setText("Shutdown error");
            break;
        case 12:
            ui->label_conn->setText("Close error");
            break;
        default:
            emit on_connection(sock);
            ui->color_box_conn->setStyleSheet("QLineEdit { background-color: green; }");
            ui->label_conn->setText("Connected");
        }
    }
    else
    {
        ui->color_box_conn->setStyleSheet("QLineEdit { background-color: orange; }");
        switch (err) {
        case 1:
            ui->label_conn->setText("Error creating socket");
            break;
        case 2:
            ui->label_conn->setText("Connection error");
            break;
        default:
            emit on_deconnection();
            ui->color_box_conn->setStyleSheet("QLineEdit { background-color: red; }");
            ui->label_conn->setText("Not connected");
            break;
        }
    }
}

void TcpParameterWindow::on_ButtonDeconnexion_clicked()
{
    if (connected==true)
    {
        int err;
        err=close_TCP_client(&sock, connected);
        connection_state(err);
    }
    if (connectedset==true)
    {
        int err;
        err=close_TCP_client(&sock_ramp, connectedset);
        if (err==0) {connectedset=false;}
    }
}

void TcpParameterWindow::on_ButtonConnexion_clicked()
{
    if (connected==false)
    {
        int err;
        err=init_TCP_client(&sock, ui->lineEdit_ip->text().toStdString().c_str(), ui->lineEdit_port->text().toInt(), connected);
        connection_state(err);
    }
    if (connectedset==false)
    {
        int err;
        err=init_TCP_client(&sock_ramp, ui->lineEdit_ip->text().toStdString().c_str(), ui->lineEdit_port->text().toInt()+1, connectedset);
        if (err==0)
        {
            connectedset=true;
            emit on_ramp_connection(sock_ramp);
        }
    }
}
