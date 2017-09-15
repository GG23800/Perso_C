#ifndef TCPPARAMETERWINDOW_H
#define TCPPARAMETERWINDOW_H

#include <QDialog>
#include "./src_RP/TCP_API.h"

namespace Ui {
class TcpParameterWindow;
}

class TcpParameterWindow : public QDialog
{
    Q_OBJECT

public:
    SOCKET sock;
    explicit TcpParameterWindow(QWidget *parent = 0);
    ~TcpParameterWindow();
    bool connected;
    void connection_state(int err);

private slots:
    void on_ButtonDeconnexion_clicked();
    void on_ButtonConnexion_clicked();

signals:
    void on_connection(SOCKET sock);
    void on_deconnection();
    void on_ramp_connection(SOCKET sock);

private:
    Ui::TcpParameterWindow *ui;
    bool connectedset;
    SOCKET sock_ramp;
};


#endif // TCPPARAMETERWINDOW_H
