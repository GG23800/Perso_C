#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "tcpparameterwindow.h"
#include "settings.h"
#include "graph.h"
#include "modeb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void tpw_show();
    void setw_show();
    void modeb_show();
    void set_connection();
    void init_graph();
    void update_plot();

signals:
    void plot(TcpParameterWindow *tpw);

private slots:
    void on_radio_linear_gain_clicked();
    void on_radio_custom_gain_clicked();
    void on_pushButton_clicked();
    void on_G1_sliderMoved(int position);
    void on_G2_sliderMoved(int position);
    void on_G3_sliderMoved(int position);
    void on_G4_sliderMoved(int position);
    void on_G5_sliderMoved(int position);
    void on_G6_sliderMoved(int position);
    void on_G7_sliderMoved(int position);
    void on_G8_sliderMoved(int position);
    void on_G9_sliderMoved(int position);
    void on_G10_sliderMoved(int position);
    void on_G11_sliderMoved(int position);
    void on_pushButton_offset_clicked();
    void on_pushButton_freeze_clicked();
    void on_checkBox_substract_offset_clicked();
    void on_checkBox_auto_clicked();
    void on_checkBox_fix_clicked();
    void on_verticalSlider_ymax_valueChanged(int value);
    void on_verticalSlider_ymin_valueChanged(int value);
    void on_lineEdit_ymax_returnPressed();
    void on_lineEdit_ymin_returnPressed();
    void on_checkBox_set_gain_clicked();

private:
    Ui::MainWindow *ui;
    TcpParameterWindow *tpw;
    Settings *setw;
    Graph *graph;
    ModeB *modeb;
    QThread *plot_thread;   
    QVector<double> xgain;
    QVector<double> ygain;
    bool auto_axis;
    bool set_gain;
    void create_plot(QCustomPlot *plot, double y0, double yf, double ymin, double ymax, QString ylabel);
    void hide_slider();
    void show_slider();
    void reset_gain_display(bool enab);
    void slider_gain_edit(QLineEdit *lineedit, int position);
    void edit_gain(int i, double value);
    void set_xgain(double xmin, double xmax);
    void get_ygain();
    void update_gain_plot();
};

#endif // MAINWINDOW_H
