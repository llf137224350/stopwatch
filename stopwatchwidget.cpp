#include "stopwatchwidget.h"


StopwatchWidget::StopwatchWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);

    QDesktopWidget *widget = new QDesktopWidget;
    this->setMaximumSize(320,480);
    this->setMinimumSize(320,480);
    this->move(widget->width() / 2 - this->width() / 2, widget->height() / 2 - this->height() / 2);
    this->setWindowTitle("秒表");
    layout = new QStackedLayout;
    toolbar = new TabBar();
    layout->addWidget(homePage);
    layout->addWidget(dictPage);
    layout->setCurrentIndex(1);
    this->setLayout(layout);
}

StopwatchWidget::~StopwatchWidget()
{

}
void StopwatchWidget::mousePressEvent(QMouseEvent *event)
{
    this->startX = event->x();
    this->startY = event->y();
    this->isPressed = true;
}

void StopwatchWidget::mouseMoveEvent(QMouseEvent *event)
{
    int moveX = event->x() -  this->startX;
    int moveY = event->y() -  this->startY;
    if(isPressed)
        this->move(this->x()+moveX,this->y()+moveY);
}

void StopwatchWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->startX = 0;
    this->startY = 0;
    this->isPressed = false;
}
