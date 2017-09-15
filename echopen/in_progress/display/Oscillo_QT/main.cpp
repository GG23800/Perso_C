#include "mainwindow.h"
#include "tcpparameterwindow.h"
#include <QApplication>

float r0=10.0;
float rf=100.0;
int decimation=8;
int Nline=64;
double sector=80.0;
int mode_RP=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
