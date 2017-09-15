#include "modeb.h"
#include "ui_modeb.h"
#include <QDebug>

ModeB::ModeB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeB),
    scene(nullptr), PixMap(nullptr), image(nullptr)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    PixMap=new QGraphicsPixmapItem;
    scene->addItem(PixMap);
    ui->graphicsView->setScene(scene);
    //init_image(512,512);
    //calculus_image(-5.0, 5.0, -5.0, 5.0);
    //lim_data();
    //print_data();
}

ModeB::~ModeB()
{
    //delete scene;
    //delete PixMap;
    //delete image;
    delete ui;
}

void ModeB::init_image(int nbx, int nby)
{
    nx=nbx;
    ny=nby;
    image=new QImage(nx,ny,QImage::Format_Grayscale8);
    dataB.resize(nx*ny);
}

void ModeB::resize_image(int nbx, int nby)
{
    if (image!=nullptr) {delete image;}
    init_image(nbx,nby);
}

void ModeB::calculus_image(double xmin, double xmax, double ymin, double ymax)
{
    int xind, yind;
    double x, y, r;

    if (xmax<xmin)
    {
        r=xmax;
        xmax=xmin;
        xmin=r;
    }
    if (ymax<ymin)
    {
        r=ymax;
        ymax=ymin;
        ymin=r;
    }

    for (xind=0 ; xind<nx ; xind++)
    {
        x=xmin+(xmax-xmin)/(nx-1)*xind;
        for (yind=0 ; yind<ny ; yind++)
        {
            y=ymin+(ymax-ymin)/(ny-1)*yind;
            r = 3*qSqrt(x*x+y*y)+1e-2;
            dataB[xind*ny+yind] = 2*x*(qCos(r+2)/r-qSin(r+2)/r);
        }
    }
}

void ModeB::lim_data()
{
    int i;

    mindata=dataB[0];
    maxdata=mindata;

    for (i=0 ; i<nx*ny ; i++)
    {
        if (dataB[i]<mindata) {mindata=dataB[i];}
        else if (dataB[i]>maxdata) {maxdata=dataB[i];}
    }
}

void ModeB::print_data()
{
    int xind, yind;
    int col;
    QPainter p(image);

    for (xind=0 ; xind<nx ; xind++)
    {
        for (yind=0 ; yind<ny ; yind++)
        {
            col=(int)((dataB[xind*ny+yind]-mindata)/(maxdata-mindata));
            p.setPen(QColor(col,col,col));
            p.drawPoint(xind,yind);
        }
    }
    PixMap->setPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->repaint();
}
