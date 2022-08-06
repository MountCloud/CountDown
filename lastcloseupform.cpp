#include "lastcloseupform.h"
#include "ui_lastcloseupform.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <Windows.h>

LastCloseUpForm::LastCloseUpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LastCloseUpForm)
{
    ui->setupUi(this);

    init();
}

LastCloseUpForm::~LastCloseUpForm()
{
    delete ui;
}

void LastCloseUpForm::init(){

    //窗口置顶
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    //test

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    ui->lcdNumber->installEventFilter(this);
    this->setStyleSheet("background-color:rgba(0,0,0,0)");
    this->ui->lcdNumber->setStyleSheet("background-color:rgba(0,0,0,0)");
}

void LastCloseUpForm::setTop(){
    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, this->pos().x(), this->pos().y(), this->width(), this->height(), SWP_SHOWWINDOW);
    SetWindowLong((HWND)this->winId(),GWL_EXSTYLE, WS_EX_TOOLWINDOW);
}

void LastCloseUpForm::setColor(QString color){
    QString colorStyle = "color: "+color+"";
    ui->lcdNumber->setStyleSheet(colorStyle);
}

void LastCloseUpForm::set(int num){
    //QString str = QString("%1").arg(num, 2, 10, QLatin1Char('0'));
    //ui->lcdNumber->display(str);
    //ui->lcdNumber->setDigitCount(QString("%1").arg(str).length());
    ui->lcdNumber->display(num);
    ui->lcdNumber->setDigitCount(QString("%1").arg(num).length());
}

int LastCloseUpForm::getSize(){
    return ui->lcdNumber->height();
}

void LastCloseUpForm::setSize(int size){
    QSize windowsize = this->size();
    ui->lcdNumber->setGeometry(0,(windowsize.height() -size)/2,windowsize.width(), size);
}

QSize LastCloseUpForm::getWinodwSize(){

    int number = QApplication::desktop()->screenNumber(this);
    //如果number是-1会出现崩溃，就是用默认0
    if(number<0){
        number=0;
    }
    //根据number获得当前窗口所在屏幕的大小
    QSize size = QGuiApplication::screens().at(number)->geometry().size();
    return size;
}
