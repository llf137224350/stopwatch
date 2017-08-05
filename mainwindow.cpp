#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    index = 0;

    this->initUI();

    //关联信号和操
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(minButton,SIGNAL(clicked(bool)),this,SLOT(minSlot()));
    connect(start,SIGNAL(clicked(bool)),this,SLOT(startSlot()));

    connect(leftButton,SIGNAL(clicked(bool)),this,SLOT(leftSlot()));
    connect(rightButton,SIGNAL(clicked(bool)),this,SLOT(rightSlot()));

    timer = new QTimer(this);   //新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDateSlot()));//关联定时器计满信号和相应的槽函数


}

MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->startX = event->x();
    this->startY = event->y();
    this->isPressed = true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int moveX = event->x() -  this->startX;
    int moveY = event->y() -  this->startY;
    if(isPressed)
        this->move(this->x()+moveX,this->y()+moveY);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->startX = 0;
    this->startY = 0;
    this->isPressed = false;
}

void MainWindow::minSlot()
{

    this->showMinimized();
}

void MainWindow::startSlot()
{
    start->hide();
    leftButton->show();
    rightButton->show();
    firstTotalTime = 0;
    secondTotalTime = 0;
    threeTotalTime =0;
    timer->start(10);
}


void MainWindow::leftSlot()
{
    if(leftButton->objectName() == "pause"){
        leftButton->setObjectName(tr("continue"));
        rightButton->setObjectName(tr("reset"));
        leftButton->setText(tr("继续"));
        rightButton->setText(tr("重置"));
        leftButton->setPalette(continuePA);
        timer->stop();
    }else{
        leftButton->setObjectName(tr("pause"));
        rightButton->setObjectName(tr("remember_times"));
        leftButton->setText(tr("暂停"));
        rightButton->setText(tr("记次"));
        leftButton->setPalette(pausePa);
        timer->start(10);
    }
}

void MainWindow::rightSlot()
{
    if(rightButton->objectName() =="remember_times"){
        if(data->isHidden()){
            totalTime->move(totalTime->x(),totalTime->y() - 160);
            data->show();
        }
        index++;
        MyItem *myWidget = new MyItem;
        myWidget->setIndexAndValue(QString::number(index),totalResult);
        QListWidgetItem *items = new QListWidgetItem;
        items->setSizeHint(QSize(0, 35));
        data->insertItem(0,items);
        data->setItemWidget(items,myWidget);

    }else{//reset
        index = 0;
        totalTime->setText("00:00.00");
        QFontMetrics metric =  totalTime->fontMetrics();
        totalTime->move(this->width() / 2 - metric.width(totalTime->text()) / 2,this->height() / 2 - metric.height() / 2);
        data->clear();
        data->hide();
        leftButton->setObjectName(tr("pause"));
        leftButton->setText(tr("暂停"));
        leftButton->setPalette(pausePa);
        rightButton->setObjectName(tr("remember_times"));
        rightButton->setText(tr("记次"));
        leftButton->hide();
        rightButton->hide();

        start->show();
    }
}

void MainWindow::timerUpDateSlot()
{
    threeTotalTime++;
    if(threeTotalTime == 100){
        threeTotalTime = 0;
        secondTotalTime++;
        if(secondTotalTime == 60){
            secondTotalTime =0;
            firstTotalTime++;
        }
    }
    totalResult =(firstTotalTime < 10 ? "0"+QString::number(firstTotalTime) :QString::number(firstTotalTime))+":"
            +(secondTotalTime < 10 ? "0"+QString::number(secondTotalTime) :QString::number(secondTotalTime))+"."
            + (threeTotalTime < 10 ? "0"+QString::number(threeTotalTime) :QString::number(threeTotalTime));
    totalTime->setText(totalResult);
}
// init
void MainWindow::initUI()
{
    QDesktopWidget *widget = new QDesktopWidget;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    qApp->setStyleSheet(Utils::getQssFileContent(":/style.qss"));

    this->setMaximumSize(320,480);
    this->setMinimumSize(320,480);
    this->move(widget->width() / 2 - this->width() / 2, widget->height() / 2 - this->height() / 2);

    this->setWindowTitle(tr("秒表"));
    this->setWindowIcon(QIcon(":/app.ico"));
    //主界面
    mainWidget = new QWidget;
    QLabel *title = new   QLabel(mainWidget);

    title->setText(tr("秒表"));
    title->move(8,6);
    //关闭按钮
    closeButton = new QPushButton(mainWidget);
    closeButton->setGeometry(this->width() - 24,6,20,20);
    closeButton->setFlat(true);
    closeButton->setObjectName(tr("closeButton"));
    closeButton->setToolTip(tr("关闭"));
    minButton = new QPushButton(mainWidget);
    minButton->setGeometry(this->width() - 48,6,20,20);
    minButton->setFlat(true);
    minButton->setObjectName(tr("minButton"));
    minButton->setToolTip(tr("最小化"));
    //总时间
    totalTime = new QLabel(mainWidget);
    totalTime->setText("00:00.00");
    totalTime->setObjectName(tr("totalTime"));
    QFont font;
    font.setPixelSize(36);
    totalTime->setFont(font);
    //居中
    QFontMetrics metric =  totalTime->fontMetrics();
    totalTime->move(this->width() / 2 - metric.width(totalTime->text()) / 2,this->height() / 2 - metric.height() / 2);

    //list
    data = new QListWidget(mainWidget);
    data->setGeometry(1,this->height() * 0.32,this->width()-2,this->height() * 0.68- 40);
    data->setGridSize(QSize(data->width(),35));

    data->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    data->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    data->setFocusPolicy(Qt::NoFocus);
    data->hide();
    //options
    options = new QGroupBox(mainWidget);
    options->setGeometry(1,this->height() - 40-1,this->width()-2,40);
    start = new QPushButton(options);
    start->setText(tr("开始"));
    start->setObjectName(tr("start"));
    start->setGeometry(0,0,options->width(),options->height());

    continuePA.setColor(QPalette::ButtonText, QColor(38,199,1));
    pausePa.setColor(QPalette::ButtonText, QColor(233,40,58));

    leftButton = new QPushButton(options);
    leftButton->setText(tr("暂停"));
    leftButton->setObjectName(tr("pause"));
    leftButton->setGeometry(0,0,options->width() / 2,options->height());
    leftButton->setPalette(pausePa);
    leftButton->hide();

    rightButton = new QPushButton(options);
    rightButton->setText(tr("记次"));
    rightButton->setObjectName(tr("remember_times"));
    rightButton->setGeometry(options->width() / 2,0,options->width() / 2,options->height());
    rightButton->hide();

    this->setCentralWidget(mainWidget);
}

