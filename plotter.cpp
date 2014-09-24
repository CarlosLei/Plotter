#include "plotter.h"

#include <QToolButton>

Plotter::Plotter(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    rubberBandIsShown = false;

    //zoomInButton初始化
    zoomInButton = new QToolButton(this);
    zoomInButton->setIcon((QIcon(":/images/zoomIn.png")));
    zoomInButton->adjustSize();
    connect(zoomInButton,SIGNAL(clicked()),this,SLOT(zoomIn()));

    //zoomOutButton初始化
    zoomOutButton = new QToolButton(this);
    zoomOutButton->setIcon(QIcon(":/images/zoomOut.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton,SIGNAL(clicked()),this,SLOT(zoomOut()));

    setPlotSetting(PlotSettings());
}

Plotter::~Plotter()
{

}
