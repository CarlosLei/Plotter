#include "plotter.h"
#include <QPushButton>
#include <QLabel>

Plotter::Plotter(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *okBtn = new QPushButton(this);
    okBtn->setText(tr("OK"));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(close()));
}

Plotter::~Plotter()
{

}
