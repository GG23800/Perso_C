#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tpw(nullptr), setw(nullptr), modeb(nullptr), graph()
{
    ui->setupUi(this);
    tpw=new TcpParameterWindow(this);
    setw=new Settings(this);
    modeb=new ModeB(this);
    graph=new Graph();
    xgain.resize(11);
    ygain.resize(11);
    auto_axis=false;
    set_gain=false;
    ui->verticalSlider_ymax->setMinimum(0);
    ui->verticalSlider_ymax->setMaximum(100);
    ui->verticalSlider_ymax->setValue((int)(100.0/2.5));
    ui->verticalSlider_ymin->setMinimum(0);
    ui->verticalSlider_ymin->setMaximum(100);
    ui->verticalSlider_ymin->setValue((int)(100.0/2.5));

    connect(ui->actionTCP_parameters, SIGNAL(triggered()), this, SLOT(tpw_show())); //show the interface tcpparameterwindow when clicking in the menu
    connect(ui->actionSettings_of_the_image, SIGNAL(triggered()), this, SLOT(setw_show())); //show the interface tcpparameterwindow when clicking in the menu
    connect(ui->actionMode_B, SIGNAL(triggered()), this, SLOT(modeb_show())); //show the interface tcpparameterwindow when clicking in the menu
    connect(tpw, SIGNAL(on_connection(SOCKET)), this, SLOT(set_connection())); //put the colorbox on green on connection
    connect(tpw, SIGNAL(on_deconnection()), this, SLOT(set_connection())); //put the colorbox on red on connection
    connect(tpw, SIGNAL(on_connection(SOCKET)), setw, SLOT(get_setting(SOCKET))); //send the socket to setw and get the image settings at connection
    connect(tpw, SIGNAL(on_ramp_connection(SOCKET)), setw, SLOT(get_ramp(SOCKET))); //send the socket to setw and get the ramp settings at connection
    connect(setw, SIGNAL(setting_done()), this, SLOT(init_graph()));

    ui->ColorBox->setStyleSheet("QLineEdit { background-color: gray; }");
    ui->Label_connection->setText("Not connected");
    ui->radio_linear_gain->setChecked(true);
    hide_slider();

    create_plot(ui->customPlot, 0.0, 0.0, -1.0, 1.0, "y (UI)");
    create_plot(ui->gain_plot, 1.0, 1.0, 0.0, 10.0, "gain");
    reset_gain_display(false);
    set_xgain(0, 1);
    get_ygain();
    update_gain_plot();

    //Thread for plotting
    QThread *plot_thread = new QThread;

    graph->moveToThread(plot_thread);
    connect(this, SIGNAL (plot(TcpParameterWindow *)), graph, SLOT (plot(TcpParameterWindow *)));
    connect(graph,SIGNAL(graph_done()), this, SLOT(update_plot()));
    //connect(graph, SIGNAL (socket_closed()), plot_thread, SLOT (quit()));
    //connect(graph, SIGNAL (socket_closed()), graph, SLOT (deleteLater()));
    connect(plot_thread, SIGNAL (finished()), plot_thread, SLOT (deleteLater()));
    connect(graph, SIGNAL(socket_closed()), this, SLOT(set_connection()));
    plot_thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create_plot(QCustomPlot *plot, double y0, double yf, double ymin, double ymax, QString ylabel)
{
    // generate some data:
    QVector<double> x(2), y(2); // initialize with entries 0..100
    for (int i=0; i<2; ++i)
    {
      x[i] = (double)i; // simple graphe x=0 for initialisation
      y[i] = 0.0;
    }
    y[0]=y0;
    y[1]=yf;
    // create graph and assign data to it:
    plot->addGraph();
    plot->graph(0)->setData(x, y, true); //set true if sure x is sorting ascending
    // give the axes some labels:
    plot->xAxis->setLabel("x (mm)");
    plot->yAxis->setLabel(ylabel);
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(0, 1);
    plot->yAxis->setRange(ymin, ymax);
    /*QCPTextElement *title = new QCPTextElement(ui->customPlot);
    title->setText("No data");
    plot->plotLayout()->addElement(0, 0, title); // place the title in the empty cell we've just created*/
    plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    plot->replot();
}

void MainWindow::init_graph()
{
    //set reception graph
    graph->init(setw);
    graph->set_xaxis();
    ui->customPlot->xAxis->setRange(graph->xmin, graph->xmax);

    //set gain graph
    set_xgain(graph->xmin, graph->xmax);
    update_gain_plot();

    //signal for plotting
    emit plot(tpw);
}

void MainWindow::update_plot()
{
    if (tpw->connected)
    {
        if (auto_axis) {ui->customPlot->yAxis->setRange(graph->ymin, graph->ymax);}
        ui->customPlot->graph(0)->setData(graph->vx, graph->vy, true);
        ui->customPlot->replot();
    }
}

void MainWindow::tpw_show()
{
    tpw->show();
}

void MainWindow::setw_show()
{
    setw->show();
}

void MainWindow::modeb_show()
{
    modeb->show();
}

void MainWindow::set_connection()
{
    if (tpw->connected==true)
    {
        ui->ColorBox->setStyleSheet("QLineEdit { background-color: green; }");
        ui->Label_connection->setText("Connected");
    }
    else
    {
        ui->ColorBox->setStyleSheet("QLineEdit { background-color: red; }");
        ui->Label_connection->setText("Not connected");
    }
}

void MainWindow::set_xgain(double xmin, double xmax)
{
    int i=0;
    double deltax=(xmax-xmin)/10.0;
    xgain[0]=xmin;
    for (i=1 ; i<11 ; i++){ xgain[i]=xgain[i-1]+deltax; }
    xgain[10]=xmax;
    ui->gain_plot->xAxis->setRange(xmin, xmax);
}

void MainWindow::get_ygain()
{
    ygain[0]=ui->GT1->text().toDouble();
    ygain[1]=ui->GT2->text().toDouble();
    ygain[2]=ui->GT3->text().toDouble();
    ygain[3]=ui->GT4->text().toDouble();
    ygain[4]=ui->GT5->text().toDouble();
    ygain[5]=ui->GT6->text().toDouble();
    ygain[6]=ui->GT7->text().toDouble();
    ygain[7]=ui->GT8->text().toDouble();
    ygain[8]=ui->GT9->text().toDouble();
    ygain[9]=ui->GT10->text().toDouble();
    ygain[10]=ui->GT11->text().toDouble();
}

void MainWindow::update_gain_plot()
{
    get_ygain();
    ui->gain_plot->graph(0)->setData(xgain, ygain, true);
    ui->gain_plot->replot();
}

void MainWindow::on_radio_linear_gain_clicked()
{
    if (ui->radio_linear_gain->isChecked())
    {
        hide_slider();
    }
}

void MainWindow::on_radio_custom_gain_clicked()
{
    if (ui->radio_custom_gain->isChecked())
    {
        show_slider();
    }
}

void MainWindow::on_pushButton_clicked()
{
    reset_gain_display(false);
}

void MainWindow::hide_slider()
{
    ui->G2->hide();
    ui->G3->hide();
    ui->G4->hide();
    ui->G5->hide();
    ui->G6->hide();
    ui->G7->hide();
    ui->G8->hide();
    ui->G9->hide();
    ui->G10->hide();
    ui->GT2->hide();
    ui->GT3->hide();
    ui->GT4->hide();
    ui->GT5->hide();
    ui->GT6->hide();
    ui->GT7->hide();
    ui->GT8->hide();
    ui->GT9->hide();
    ui->GT10->hide();
}

void MainWindow::show_slider()
{
    ui->G2->show();
    ui->G3->show();
    ui->G4->show();
    ui->G5->show();
    ui->G6->show();
    ui->G7->show();
    ui->G8->show();
    ui->G9->show();
    ui->G10->show();
    ui->GT2->show();
    ui->GT3->show();
    ui->GT4->show();
    ui->GT5->show();
    ui->GT6->show();
    ui->GT7->show();
    ui->GT8->show();
    ui->GT9->show();
    ui->GT10->show();
}

void MainWindow::reset_gain_display(bool enab)
{
    //define max length and enability of gain line edits
    ui->GT1->setMaxLength(3);
    ui->GT1->setEnabled(enab);
    ui->GT1->setText("1.0");
    ui->GT2->setMaxLength(3);
    ui->GT2->setEnabled(enab);
    ui->GT2->setText("1.0");
    ui->GT3->setMaxLength(3);
    ui->GT3->setEnabled(enab);
    ui->GT3->setText("1.0");
    ui->GT4->setMaxLength(3);
    ui->GT4->setEnabled(enab);
    ui->GT4->setText("1.0");
    ui->GT5->setMaxLength(3);
    ui->GT5->setEnabled(enab);
    ui->GT5->setText("1.0");
    ui->GT6->setMaxLength(3);
    ui->GT6->setEnabled(enab);
    ui->GT6->setText("1.0");
    ui->GT7->setMaxLength(3);
    ui->GT7->setEnabled(enab);
    ui->GT7->setText("1.0");
    ui->GT8->setMaxLength(3);
    ui->GT8->setEnabled(enab);
    ui->GT8->setText("1.0");
    ui->GT9->setMaxLength(3);
    ui->GT9->setEnabled(enab);
    ui->GT9->setText("1.0");
    ui->GT10->setMaxLength(3);
    ui->GT10->setEnabled(enab);
    ui->GT10->setText("1.0");
    ui->GT11->setMaxLength(3);
    ui->GT11->setEnabled(enab);
    ui->GT11->setText("1.0");

    //set slider
    ui->G1->setMinimum(0);
    ui->G1->setMaximum(100);
    ui->G1->setValue(10);
    ui->G2->setMinimum(0);
    ui->G2->setMaximum(100);
    ui->G2->setValue(10);
    ui->G3->setMinimum(0);
    ui->G3->setMaximum(100);
    ui->G3->setValue(10);
    ui->G4->setMinimum(0);
    ui->G4->setMaximum(100);
    ui->G4->setValue(10);
    ui->G5->setMinimum(0);
    ui->G5->setMaximum(100);
    ui->G5->setValue(10);
    ui->G6->setMinimum(0);
    ui->G6->setMaximum(100);
    ui->G6->setValue(10);
    ui->G7->setMinimum(0);
    ui->G7->setMaximum(100);
    ui->G7->setValue(10);
    ui->G8->setMinimum(0);
    ui->G8->setMaximum(100);
    ui->G8->setValue(10);
    ui->G9->setMinimum(0);
    ui->G9->setMaximum(100);
    ui->G9->setValue(10);
    ui->G10->setMinimum(0);
    ui->G10->setMaximum(100);
    ui->G10->setValue(10);
    ui->G11->setMinimum(0);
    ui->G11->setMaximum(100);
    ui->G11->setValue(10);

    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::slider_gain_edit(QLineEdit *lineedit, int position)
{
    double value = (double)(position)/10.0;
    lineedit->setText(QString::number(value));
}

void MainWindow::edit_gain(int i, double value)
{
    int position;
    QSlider *slider;
    QLineEdit *lineedit;
    switch (i) {
    case 1:
        slider=ui->G1;
        lineedit=ui->GT1;
        break;
    case 2:
        slider=ui->G2;
        lineedit=ui->GT2;
        break;
    case 3:
        slider=ui->G3;
        lineedit=ui->GT3;
        break;
    case 4:
        slider=ui->G4;
        lineedit=ui->GT4;
        break;
    case 5:
        slider=ui->G5;
        lineedit=ui->GT5;
        break;
    case 6:
        slider=ui->G6;
        lineedit=ui->GT6;
        break;
    case 7:
        slider=ui->G7;
        lineedit=ui->GT7;
        break;
    case 8:
        slider=ui->G8;
        lineedit=ui->GT8;
        break;
    case 9:
        slider=ui->G9;
        lineedit=ui->GT9;
        break;
    case 10:
        slider=ui->G10;
        lineedit=ui->GT10;
        break;
    case 11:
        slider=ui->G11;
        lineedit=ui->GT11;
        break;
    }
    position=(int)(value*10);
    slider->setValue(position);
    lineedit->setText(QString::number(value));
}

void MainWindow::on_G1_sliderMoved(int position)
{
    slider_gain_edit(ui->GT1, position);
    if (ui->radio_linear_gain->isChecked())
    {
        int i;
        double gain_min, gain_max, delta_gain, temp_gain;
        gain_min = (double)(position)/10.0;
        gain_max = ui->GT11->text().toDouble();
        delta_gain=(gain_max-gain_min)/10.0;
        temp_gain = gain_min+delta_gain;
        for (i=2 ; i<11 ; i++)
        {
            edit_gain(i, temp_gain);
            temp_gain+=delta_gain;
        }
    }
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G2_sliderMoved(int position)
{
    slider_gain_edit(ui->GT2, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G3_sliderMoved(int position)
{
    slider_gain_edit(ui->GT3, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G4_sliderMoved(int position)
{
    slider_gain_edit(ui->GT4, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G5_sliderMoved(int position)
{
    slider_gain_edit(ui->GT5, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G6_sliderMoved(int position)
{
    slider_gain_edit(ui->GT6, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G7_sliderMoved(int position)
{
    slider_gain_edit(ui->GT7, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G8_sliderMoved(int position)
{
    slider_gain_edit(ui->GT8, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G9_sliderMoved(int position)
{
    slider_gain_edit(ui->GT9, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G10_sliderMoved(int position)
{
    slider_gain_edit(ui->GT10, position);
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_G11_sliderMoved(int position)
{
    slider_gain_edit(ui->GT11, position);
    if (ui->radio_linear_gain->isChecked())
    {
        int i;
        double gain_min, gain_max, delta_gain, temp_gain;
        gain_min = ui->GT1->text().toDouble();
        gain_max = (double)(position)/10.0;
        delta_gain=(gain_max-gain_min)/10.0;
        temp_gain = gain_min+delta_gain;
        for (i=2 ; i<11 ; i++)
        {
            edit_gain(i, temp_gain);
            temp_gain+=delta_gain;
        }
    }
    update_gain_plot();
    if (set_gain)
    {
        get_ygain();
        graph->set_gain_vector(ygain);
    }
}

void MainWindow::on_pushButton_offset_clicked()
{
    if (tpw->connected)
    {
        double mean=0.0;
        int i=0;
        for (i=0 ; i<setw->Npoint ; i++)
        {
            mean+=graph->vy[i];
        }
        graph->offset=mean/((double)setw->Npoint);
        ui->lineEdit_offset->setText(QString::number(graph->offset));
    }
}

void MainWindow::on_pushButton_freeze_clicked()
{
    graph->freeze=!graph->freeze;
    if (graph->freeze) {ui->pushButton_freeze->setText("Unfreeze");}
    else
    {
        ui->pushButton_freeze->setText("Freeze");
        emit plot(tpw);
    }
}

void MainWindow::on_checkBox_substract_offset_clicked()
{
    if(ui->checkBox_substract_offset->isChecked()) {graph->substrac_offset=true;}
    else {graph->substrac_offset=false;}
}

void MainWindow::on_checkBox_auto_clicked()
{
    if(ui->checkBox_auto->isChecked())
    {
        auto_axis=true;
        ui->checkBox_fix->setChecked(false);
    }
    else
    {
        auto_axis=false;
        ui->checkBox_fix->setChecked(true);
    }
}

void MainWindow::on_checkBox_fix_clicked()
{
    if(ui->checkBox_fix->isChecked())
    {
        ui->checkBox_auto->setChecked(false);
        auto_axis=false;
    }
    else
    {
        ui->checkBox_fix->setChecked(true);
        auto_axis=true;
    }
}

void MainWindow::on_verticalSlider_ymax_valueChanged(int value)
{
    if (auto_axis)
    {
        auto_axis=false;
        ui->checkBox_auto->setChecked(false);
        ui->checkBox_fix->setChecked(true);
    }
    double ymax=(double)(value)*2.5/100.0;
    double ymin=ui->lineEdit_ymin->text().toDouble();
    ui->lineEdit_ymax->setText(QString::number(ymax));
    ui->customPlot->yAxis->setRange(ymin, ymax);
    ui->customPlot->replot();
}

void MainWindow::on_verticalSlider_ymin_valueChanged(int value)
{
    if (auto_axis)
    {
        auto_axis=false;
        ui->checkBox_auto->setChecked(false);
        ui->checkBox_fix->setChecked(true);
    }
    double ymin=-(double)(value)*2.5/100.0;
    double ymax=ui->lineEdit_ymax->text().toDouble();
    ui->lineEdit_ymin->setText(QString::number(ymin));
    ui->customPlot->yAxis->setRange(ymin, ymax);
    ui->customPlot->replot();
}

void MainWindow::on_lineEdit_ymax_returnPressed()
{
    if (auto_axis)
    {
        auto_axis=false;
        ui->checkBox_auto->setChecked(false);
        ui->checkBox_fix->setChecked(true);
    }
    QString string_ymax=ui->lineEdit_ymax->text();
    double ymax=string_ymax.toDouble();
    double ymin=ui->lineEdit_ymin->text().toDouble();
    int value=(int)(ymax*100.0/2.5);
    if (value<0) {value=0;}
    if (value>100) {value=100;}
    ui->verticalSlider_ymax->setValue(value);
    ui->customPlot->yAxis->setRange(ymin, ymax);
    ui->customPlot->replot();
}

void MainWindow::on_lineEdit_ymin_returnPressed()
{
    if (auto_axis)
    {
        auto_axis=false;
        ui->checkBox_auto->setChecked(false);
        ui->checkBox_fix->setChecked(true);
    }
    QString string_ymin=ui->lineEdit_ymin->text();
    double ymin=string_ymin.toDouble();
    double ymax=ui->lineEdit_ymax->text().toDouble();
    int value=(int)(-ymin*100.0/2.5);
    if (value<0) {value=0;}
    if (value>100) {value=100;}
    ui->verticalSlider_ymin->setValue(value);
    ui->customPlot->yAxis->setRange(ymin, ymax);
    ui->customPlot->replot();
}

void MainWindow::on_checkBox_set_gain_clicked()
{
    if(ui->checkBox_set_gain->isChecked())
    {
        if(!tpw->connected) {ui->checkBox_set_gain->setChecked(false);}
        else
        {
            set_gain=true;
            graph->set_gain=true;
            get_ygain();
            graph->set_gain_vector(ygain);
        }
    }
    else
    {
        set_gain=false;
        graph->set_gain=false;
    }
}
