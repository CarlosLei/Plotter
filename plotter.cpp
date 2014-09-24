#include "plotter.h"

#include <QToolButton>
#include <QStylePainter>

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
void Plotter::setPlotSetting(const PlotSettings &settings)
{
    //初始化Plotsettings
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();
    refreshPixmap();
}
void Plotter::zoomOut()
{
    //缩小
    if(curZoom > 0)
    {
        --curZoom;
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);
        zoomInButton->show();
        refreshPixmap();
    }
}
void Plotter::zoomIn()
{
    //放大
    if(curZoom < zoomStack.count() - 1)
    {
        ++curZoom;
        zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
        zoomOutButton->setEnabled(true);
        zoomOutButton->show();
        refreshPixmap();
    }
}
void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
    //设置用于给定的曲线ID中的数据
    curveMap[id] = data;
    refreshPixmap();
}
void Plotter::clearCurve(int id)
{
    //移除一条给定的曲线
    curveMap.remove(id);
    refreshPixmap();
}
QSize Plotter::minimumSizeHint() const
{
    return QSize(6*Margin, 4*Margin);
}
QSize Plotter::sizeHint() const
{
    return QSize(12*Margin, 8*Margin);
}
//-------------------------------------------








