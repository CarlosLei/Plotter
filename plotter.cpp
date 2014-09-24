#include "plotter.h"

#include <QToolButton>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QMouseEvent>

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
void Plotter::paintEvent(QPaintEvent */*event*/)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,pixmap);

    if(rubberBandIsShown)//绘制橡皮根
    {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect.normalized()
                         .adjust(0,0,-1,-1););
    }
    if(hasFocus())//拥有焦点？？？
    {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect,option);
    }
}
void Plotter::resizeEvent(QResizeEvent */*event*/)
{
    //这里设置了两个按钮的位置
    int x = width() - (zoomInButton->width()
                       + zoomOutButton->width() + 10);
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5, 5);
    refreshPixmap();
}
void Plotter::mousePressEvent(QMouseEvent *event)
{
    QRect rect(Margin, Margin,
               width() - 2* Margin,height() - 2* Margin);
    if(event->button() == Qt::LeftButton)
    {
        if(rect.contains(event->pos()))
        {
            rubberBandIsShown = true;
            rubberBandRect.setTopLeft(event->pos());
            rubberBandRect.setBottomRight(event->pos());
            updateRubberBandRegion();
            setCursor(Qt::CrossCursor);
        }
    }
}







