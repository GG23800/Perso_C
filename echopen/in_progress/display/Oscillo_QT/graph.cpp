#include "graph.h"

Graph::Graph()
{
    vx.reserve(16384);
    vy.reserve(16384);
    gain_vector.reserve(16384);
    xid.resize(11);
    buff=nullptr;
    offset=0.0;
    substrac_offset=false;
    freeze=false;
    set_gain=false;
}

Graph::~Graph()
{
    if (buff!=nullptr) {delete buff;}
}

void Graph::init(Settings *setw)
{
    Npoint=setw->Npoint;
    vx.resize(Npoint);
    vy.resize(Npoint);
    gain_vector.resize(Npoint);
    if (buff==nullptr) {buff=new int16_t [Npoint];}
    else
    {
        delete buff;
        buff=new int16_t [Npoint];
    }
    xmin=setw->R0;
    xmax=setw->Rf;
}

void Graph::set_xaxis()
{
    int i=0;
    vx[0]=xmin;
    double dr=(double)(xmax-xmin)/((double)(Npoint-1));
    for (i=1 ; i<Npoint ; i++) {vx[i]=vx[0]+i*dr;}
    set_xid();
}

void Graph::get_ylim()
{
    int i=0;
    ymin=vy[0];
    ymax=ymin;
    for (i=1 ; i<Npoint ; i++)
    {
        if (vy[i]>ymax) {ymax=vy[i];}
        else if (vy[i]<ymin) {ymin=vy[i];}
    }
}

void Graph::plot(TcpParameterWindow *tpw)
{
    int i=0;
    while (tpw->connected && !freeze)
    {
        if(receive_int16_TCP_client(&tpw->sock, buff, Npoint+1)==1)
        {
            tpw->connected=false;
            emit socket_closed();
        }
        else
        {
            line=(int)buff[0];
            ymin=(double)buff[1]/409.6;
            ymax=ymin;
            for(i=1 ; i<Npoint+1 ; i++)
            {
                vy[i-1]=(double)buff[i]/409.6;
                //vy[i-1]=1.0;
                if (substrac_offset) {vy[i-1]-=offset;}
                if (set_gain) {vy[i-1]*=gain_vector[i-1];}
                if (vy[i-1]>ymax) {ymax=vy[i-1];}
                else if (vy[i-1]<ymin) {ymin=vy[i-1];}
            }
            emit graph_done();
        }
    }
}

void Graph::set_xid()
{
    double deltaN=((double)Npoint)/10.0;
    int i=0;
    xid[0]=0;
    for (i=1 ; i<10 ; i++)
    {xid[i]=(int)(((double)i)*deltaN-1.0);}
    xid[10]=Npoint;
}

void Graph::set_gain_vector(QVector<double> ygain)
{
    int i=0, j=0;
    double y0;
    double delta;
    for (i=0 ; i<10 ; i++)
    {
        y0=ygain[i];
        delta=(ygain[i+1]-ygain[i])/((double)(xid[i+1]-xid[i]));
        for (j=xid[i] ; j<xid[i+1] ; j++)
        {
            gain_vector[j]=y0+((double)j-xid[i])*delta;
        }
    }
}
