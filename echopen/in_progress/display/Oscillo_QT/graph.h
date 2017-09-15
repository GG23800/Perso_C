#ifndef GRAPH_H
#define GRAPH_H

#include "tcpparameterwindow.h"
#include "settings.h"
#include "./src_RP/TCP_API.h"

class Graph : public QObject
{
    Q_OBJECT

public:
    Graph();
    ~Graph();
    int Npoint;
    double ymin;
    double ymax;
    double xmin;
    double xmax;
    int line;
    double offset; //value of the offset
    bool substrac_offset;
    bool freeze;
    bool set_gain;
    void init(Settings *setw);
    void set_xaxis();
    void get_ylim();
    QVector<double> vx;
    QVector<double> vy;
    void set_xid();
    void set_gain_vector(QVector<double> ygain);

private slots:
    void plot(TcpParameterWindow *tpw);

signals:
    void graph_done();
    void socket_closed();

private:
    int16_t *buff;
    QVector<int> xid;
    QVector<double> gain_vector;
};

#endif // GRAPH_H
