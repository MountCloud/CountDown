#include "textshowform.h"
#include "ui_textshowform.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>
#include <Windows.h>

TextShowForm::TextShowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextShowForm)
{
    ui->setupUi(this);
    init();
}

TextShowForm::~TextShowForm()
{
    delete ui;
}

void TextShowForm::init(){
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    ui->labelContent->installEventFilter(this);


//    int number = QApplication::desktop()->screenNumber(this);
//    //如果number是-1会出现崩溃，就是用默认0
//    if(number<0){
//        number=0;
//    }
//    //根据number获得当前窗口所在屏幕的大小
//    QSize size = QGuiApplication::screens().at(number)->geometry().size();
//    //this->setFixedSize(size.width(),size.height());
//    this->setGeometry(0,0,size.width(),size.height());
}

void TextShowForm::setTop(){
    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, this->pos().x(), this->pos().y(), this->width(), this->height(), SWP_SHOWWINDOW);
    SetWindowLong((HWND)this->winId(),GWL_EXSTYLE, WS_EX_TOOLWINDOW);
}

void TextShowForm::setText(QString text){
    ui->labelContent->setText(text);
}

void TextShowForm::setTextColor(QString color){
    QString colorStyle = "color: "+color+";";
    ui->labelContent->setStyleSheet(colorStyle);
}

void TextShowForm::setTextFont(QFont font){
    ui->labelContent->setFont(font);
}

void TextShowForm::setTextSize(int size){
    QFont oldFont = ui->labelContent->font();
    oldFont.setPointSize(size);
    ui->labelContent->setFont(oldFont);
}

QFont TextShowForm::getTextFont(){
    return ui->labelContent->font();
}

QString TextShowForm::getText(){
    return ui->labelContent->text();
}

QSize TextShowForm::getWinodwSize(){

    int number = QApplication::desktop()->screenNumber(this);
    //如果number是-1会出现崩溃，就是用默认0
    if(number<0){
        number=0;
    }
    //根据number获得当前窗口所在屏幕的大小
    QSize size = QGuiApplication::screens().at(number)->geometry().size();
    return size;
}


void TextShowForm::setTextAlignment(Qt::Alignment alignment){
    ui->labelContent->setAlignment(alignment);
}
