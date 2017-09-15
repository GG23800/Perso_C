#ifndef MODEB_H
#define MODEB_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class ModeB;
}

class ModeB : public QDialog
{
    Q_OBJECT

public:
    explicit ModeB(QWidget *parent = 0);
    ~ModeB();

private:
    Ui::ModeB *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *PixMap;
    QImage *image;

    int nx, ny;
    QVector<double> dataB;
    double mindata, maxdata;

    void init_image(int nbx, int nby);
    void resize_image(int nbx, int nby);
    void calculus_image(double xmin, double xmax, double ymin, double ymax);
    void lim_data();
    void print_data();
};


#endif // MODEB_H
