#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QFontMetrics>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QtDebug>
#include <QPalette>
#include <QTimer>
#include "utils.h"
#include "myitem.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public slots:
    void minSlot();
    void startSlot();
    void leftSlot();
    void rightSlot();
    void timerUpDateSlot();
private:
    int startX,startY;
    bool isPressed;
    int firstTotalTime;
    int secondTotalTime;
    int threeTotalTime;
    int index;
    QString totalResult;
    QPalette continuePA;
    QPalette pausePa;
    QWidget *mainWidget;
    QPushButton *closeButton ;
    QPushButton *minButton ;
    QLabel *totalTime;

    QGroupBox *options;
    QPushButton *start;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QListWidget *data;
    QTimer *timer;

    void initUI();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
