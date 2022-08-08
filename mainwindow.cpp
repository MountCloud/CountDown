#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QDateTime>
#include <QDesktopWidget>
#include <QScreen>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>
#include <QTimer>

#define qcn

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event){
    QApplication::instance()->exit(0);
}


void MainWindow::init(){
    this->setWindowTitle("CountDown v1.2.1 by MountCloud");
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setFixedSize(this->width(),this->height());
    //init form
    countDownShowForm = new TextShowForm();
    lastCloseUpForm = new LastCloseUpForm();
    lasetTextShowForm = new TextShowForm();

    countDownShowForm->show();
    countDownShowForm->setTop();
    countDownShowForm->hide();

    lastCloseUpForm->show();
    lastCloseUpForm->setTop();
    lastCloseUpForm->hide();

    lasetTextShowForm->show();
    lasetTextShowForm->setTop();
    lasetTextShowForm->hide();

    statusLable = new QLabel();
    statusLable->setText(QString(""));
    this->statusBar()->addWidget(statusLable);

    reloadFlowerView();

    //init event
    connect(ui->actionHomPage, &QAction::triggered, this, &MainWindow::slots_menuHomePage);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::slots_about);

    connect(ui->pushButtonContDownColor, &QPushButton::clicked, this, &MainWindow::slots_countDownSelectColor);
    connect(ui->pushButtonCountDownMid, &QPushButton::clicked, this, &MainWindow::slots_countDownSetMid);
    connect(ui->pushButtonCountDownSet, &QPushButton::clicked, this, &MainWindow::slots_countDownTextConfig);
    connect(ui->pushButtonCountDownYulan, &QPushButton::clicked, this, &MainWindow::slots_countDownPreview);
    connect(ui->pushButtonCountDownTextLeft, &QPushButton::clicked, this, &MainWindow::slots_countDownTextLeft);
    connect(ui->pushButtonCountDownTextMid, &QPushButton::clicked, this, &MainWindow::slots_countDownTextMid);


    connect(ui->pushButtonLastYulan, &QPushButton::clicked, this, &MainWindow::slots_lastPreview);
    connect(ui->pushButtonLastSelectColor, &QPushButton::clicked, this, &MainWindow::slots_lastSelectColor);
    connect(ui->pushButtonLastSet, &QPushButton::clicked, this, &MainWindow::slots_lastTimeSet);

    connect(ui->pushButtonLastTextSet, &QPushButton::clicked, this, &MainWindow::slots_setLastTextConfig);
    connect(ui->pushButtonLastTextYulan, &QPushButton::clicked, this, &MainWindow::slots_lastTextPreview);
    connect(ui->pushButtonLastMid, &QPushButton::clicked, this, &MainWindow::slots_lastSetMid);


    //pushButtonLastTextSelectColor
    connect(ui->pushButtonLastTextSelectColor, &QPushButton::clicked, this, &MainWindow::slots_lastTextSelectColor);
    connect(ui->pushButtonLastTextMid, &QPushButton::clicked, this, &MainWindow::slots_lastTextSetMid);

    connect(ui->pushButtonLastTextContentLeft, &QPushButton::clicked, this, &MainWindow::slots_lastTextTextLeft);
    connect(ui->pushButtonLastTextContentMid, &QPushButton::clicked, this, &MainWindow::slots_lastTextTextMid);

    connect(ui->pushButtonFlowerSet, &QPushButton::clicked, this, &MainWindow::slots_flowerSet);
    connect(ui->pushButtonFlowerSetAndShow, &QPushButton::clicked, this, &MainWindow::slots_flowerSetAndSHow);

    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::slots_start);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::slots_stop);
    connect(ui->pushButtonHideAll, &QPushButton::clicked, this, &MainWindow::slots_hideAll);


    //init value
    ui->spinBoxCountDown->setValue(countDownShowForm->getTextFont().pointSize());
    ui->spinBoxCountDownW->setValue(countDownShowForm->size().width());
    ui->spinBoxCountDownH->setValue(countDownShowForm->size().height());
    ui->spinBoxCountDownX->setValue(countDownShowForm->pos().x());
    ui->spinBoxCountDownY->setValue(countDownShowForm->pos().y());

    ui->spinBoxLastSize->setValue(lastCloseUpForm->getSize());
    ui->spinBoxLastW->setValue(lastCloseUpForm->size().width());
    ui->spinBoxLastH->setValue(lastCloseUpForm->size().height());
    ui->spinBoxLastX->setValue(lastCloseUpForm->pos().x());
    ui->spinBoxLastY->setValue(lastCloseUpForm->pos().y());


    ui->spinBoxLastText->setValue(lasetTextShowForm->getTextFont().pointSize());
    ui->lineEditLastTextContent->setText(lasetTextShowForm->getText());
    ui->spinBoxLastTextW->setValue(lasetTextShowForm->size().width());
    ui->spinBoxLastTextH->setValue(lasetTextShowForm->size().height());
    ui->spinBoxLastTextX->setValue(lasetTextShowForm->pos().x());
    ui->spinBoxLastTextY->setValue(lasetTextShowForm->pos().y());

    ui->dateTimeEditEndTime->setDateTime(QDateTime::currentDateTime());

    countDownTimer = new QTimer(this);
    connect(countDownTimer,&QTimer::timeout,this,&MainWindow::slots_countDown);
}

void MainWindow::slots_countDownSetMid(){
    QSize windowSize = this->countDownShowForm->getWinodwSize();
    QSize formSize = this->countDownShowForm->size();

    int x = (windowSize.width() - formSize.width()) / 2;
    int y = (windowSize.height() - formSize.height()) / 2;

    this->countDownShowForm->setGeometry(QRect(x,y,formSize.width(),formSize.height()));
    ui->spinBoxCountDownX->setValue(x);
    ui->spinBoxCountDownY->setValue(y);
}

void MainWindow::slots_countDownSelectColor(){
    QColorDialog colorDlg;
    QString colorStr = ui->lineEditCountDownColor->text();
    colorStr = colorStr.mid(1);
    QColor color = colorDlg.getColor(QColor(colorStr.toUInt(NULL,16)));

    //QRgb(uint) >> QColor;
    colorStr = QString("#%1%2%3")
            .arg(color.red(),2,16,QLatin1Char('0'))
            .arg(color.green(),2,16,QLatin1Char('0'))
            .arg(color.blue(),2,16,QLatin1Char('0'));

    if(colorStr != "000"){
        ui->lineEditCountDownColor->setText(colorStr);
    }
}

void MainWindow::slots_countDownTextConfig(){
    int ltw = ui->spinBoxCountDownW->value();
    int lth = ui->spinBoxCountDownH->value();
    int ltx = ui->spinBoxCountDownX->value();
    int lty = ui->spinBoxCountDownY->value();
    this->countDownShowForm->setGeometry(QRect(ltx,lty,ltw,lth));

    QFont font = ui->fontComboBoxCountDown->currentFont();
    int fontSize= ui->spinBoxCountDown->value();
    QString color = ui->lineEditCountDownColor->text();
    font.setPointSize(fontSize);

    this->countDownShowForm->setTextFont(font);
    this->countDownShowForm->setTextColor(color);
}

void MainWindow::slots_countDownPreview(){
    if(this->countDownShowForm->isHidden()){
        this->countDownShowForm->show();
        //this->countDownShowForm->setTop();
        QString str = ui->lineEditCountDownContent->text();
        setCountDown(str,QString::number(1),QString::number(2),QString::number(3),QString::number(4));
    }else{
        this->countDownShowForm->hide();
    }
}


void MainWindow::slots_countDownTextLeft(){
    countDownShowForm->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}
void MainWindow::slots_countDownTextMid(){
    countDownShowForm->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

//---------------------------------------------------------------------
void MainWindow::slots_lastSelectColor(){
    QColorDialog colorDlg;
    QString colorStr = ui->lineEditLastColor->text();
    colorStr = colorStr.mid(1);
    QColor color = colorDlg.getColor(QColor(colorStr.toUInt(NULL,16)));

    //QRgb(uint) >> QColor;
    colorStr = QString("#%1%2%3")
            .arg(color.red(),2,16,QLatin1Char('0'))
            .arg(color.green(),2,16,QLatin1Char('0'))
            .arg(color.blue(),2,16,QLatin1Char('0'));
    if(colorStr != "000"){
        ui->lineEditLastColor->setText(colorStr);
    }
}

void MainWindow::slots_lastTimeSet(){
    int ltw = ui->spinBoxLastW->value();
    int lth = ui->spinBoxLastH->value();
    int ltx = ui->spinBoxLastX->value();
    int lty = ui->spinBoxLastY->value();
    this->lastCloseUpForm->setGeometry(QRect(ltx,lty,ltw,lth));

    QString colorStr = ui->lineEditLastColor->text();
    this->lastCloseUpForm->setColor(colorStr);

    int timeSize = ui->spinBoxLastSize->value();
    this->lastCloseUpForm->setSize(timeSize);
}

void MainWindow::slots_lastPreview(){
    if(lastCloseUpForm->isHidden()){
        lastCloseUpForm->show();
        //lastCloseUpForm->setTop();
        stateyulan = true;
    }else{
        lastCloseUpForm->hide();
        stateyulan = false;
    }

}

void MainWindow::slots_lastSetMid(){
    QSize windowSize = this->lastCloseUpForm->getWinodwSize();
    QSize formSize = this->lastCloseUpForm->size();

    int x = (windowSize.width() - formSize.width()) / 2;
    int y = (windowSize.height() - formSize.height()) / 2;

    this->lastCloseUpForm->setGeometry(QRect(x,y,formSize.width(),formSize.height()));
    //this->lastCloseUpForm->setTop();
    ui->spinBoxLastX->setValue(x);
    ui->spinBoxLastY->setValue(y);
}


void MainWindow::slots_countDown(){

    int nowTimeSec = QDateTime::currentDateTime().toTime_t();
    if(lastExecTime == nowTimeSec){
        return;
    }
    lastExecTime = nowTimeSec;

    int differ = countDownEndTime - nowTimeSec;
    qDebug(QString::number(differ).toStdString().c_str());

    if(showCountDownText){
        if(differ>0){
            QString str = ui->lineEditCountDownContent->text();
            int day = differ / 86400 % 365;
            int hour = differ / 3600 % 24;
            int minute = differ /60 % 60;
            int second = differ % 60;
            setCountDown(str,QString::number(day),QString::number(hour),QString::number(minute),QString::number(second));
        }else{
            QString str = ui->lineEditCountDownContent->text();
            setCountDown(str,QString::number(0),QString::number(0),QString::number(0),QString::number(0));
        }
    }


    if(showLastCountDownText){
        if(differ > 0 && differ <= showLastCountDownSec){
            lastCloseUpForm->set(differ);
            if(lastCloseUpForm->isHidden()){
                lastCloseUpForm->show();
                //lastCloseUpForm->setTop();
            }
        }
        if(differ<=0){
            lastCloseUpForm->set(0);
        }
    }

    if(showEndText){
        if(differ <= 0){
            if(this->lasetTextShowForm->isHidden()){
                lastCloseUpForm->hide();
                this->lasetTextShowForm->show();
                //this->lasetTextShowForm->setTop();
            }
        }
    }

    //flower
    if(showFlowers&&scatterFlowers!=NULL){
        if(differ <= flowerEndTimeSec){
            if(!scatterFlowers->getFlowerIsStart()&&!flowerShowed){
                flowerDisplayTime = nowTimeSec;
                flowerShowed = true;
                scatterFlowers->show();
                //scatterFlowers->setTop();
                scatterFlowers->startScatterFlowers();
            }
            if(scatterFlowers->getFlowerIsStart()){
                int flowerDiiffer = nowTimeSec - flowerDisplayTime;
                if(flowerDiiffer > flowerShowTimeSec){
                    scatterFlowers->stopScatterFlowers();
                    scatterFlowers->hide();
                }
            }
        }
    }
}


void MainWindow::setCountDown(QString str,QString day,QString hour,QString minute,QString second){
    QString newStr = str
            .replace("$day",day)
            .replace("$hour",hour)
            .replace("$minute",minute)
            .replace("$second",second);
    qDebug(newStr.toStdString().c_str());
    this->countDownShowForm->setText(newStr);
}

void MainWindow::reloadFlowerView(){
    if(scatterFlowers!=NULL){
        delete scatterFlowers;
        scatterFlowers = NULL;
    }

    int number = QApplication::desktop()->screenNumber(this);
    //如果number是-1会出现崩溃，就是用默认0
    if(number<0){
        number=0;
    }
    //根据number获得当前窗口所在屏幕的大小
    QSize size = QGuiApplication::screens().at(number)->geometry().size();

    flowerEndTimeSec = ui->spinBoxFlowersEndTime->value();
    flowerShowTimeSec = ui->spinBoxFlowersTime->value();

    int playCount = ui->spinBoxFlowerPlayCount->value();
    int kMaxGraphicsCount = ui->spinBoxFlowerCount->value();   //最大数量60
    scatterFlowers = new ScatterFlowers(kMaxGraphicsCount,playCount,size.width(),size.height());

    scatterFlowers->show();
    scatterFlowers->setTop();
    scatterFlowers->hide();

    scatterFlowers->resize(size.width(), size.height());
    scatterFlowers->move(0, 0);
    scatterFlowers->show();
    scatterFlowers->hide();

}

void MainWindow::playFlower(){
    if(scatterFlowers!=NULL){
        //ui->pushButtonFlowerSetAndShow->setDisabled(false);
        ui->pushButtonFlowerSetAndShow->setEnabled(false);
        scatterFlowers->show();
        scatterFlowers->startScatterFlowers();
        QTimer::singleShot(flowerShowTimeSec*1000,this, [=]{
            this->scatterFlowers->stopScatterFlowers();
            this->scatterFlowers->hide();
            this->ui->pushButtonFlowerSetAndShow->setEnabled(true);
        });
    }
}

void MainWindow::slots_lastTextSelectColor(){
    QColorDialog colorDlg;
    QString colorStr = ui->lineEditLastColor->text();
    colorStr = colorStr.mid(1);
    QColor color = colorDlg.getColor(QColor(colorStr.toUInt(NULL,16)));

    //QRgb(uint) >> QColor;
    colorStr = QString("#%1%2%3")
            .arg(color.red(),2,16,QLatin1Char('0'))
            .arg(color.green(),2,16,QLatin1Char('0'))
            .arg(color.blue(),2,16,QLatin1Char('0'));
    if(colorStr != "000"){
        ui->lineEditLastTextColor->setText(colorStr);
    }
}


void MainWindow::slots_setLastTextConfig(){
    int ltw = ui->spinBoxLastTextW->value();
    int lth = ui->spinBoxLastTextH->value();
    int ltx = ui->spinBoxLastTextX->value();
    int lty = ui->spinBoxLastTextY->value();
    this->lasetTextShowForm->setGeometry(QRect(ltx,lty,ltw,lth));

    QFont font = ui->fontComboBoxLastText->currentFont();
    int fontSize= ui->spinBoxLastText->value();
    QString text = ui->lineEditLastTextContent->text();
    QString color = ui->lineEditLastTextColor->text();
    font.setPointSize(fontSize);

    this->lasetTextShowForm->setTextFont(font);
    this->lasetTextShowForm->setText(text);
    this->lasetTextShowForm->setTextColor(color);
}

void MainWindow::slots_lastTextPreview(){
    if(this->lasetTextShowForm->isHidden()){
        this->lasetTextShowForm->show();
        //this->lasetTextShowForm->setTop();
    }else{
        this->lasetTextShowForm->hide();
    }
}

void MainWindow::slots_lastTextSetMid(){
    QSize windowSize = this->lasetTextShowForm->getWinodwSize();
    QSize formSize = this->lasetTextShowForm->size();

    int x = (windowSize.width() - formSize.width()) / 2;
    int y = (windowSize.height() - formSize.height()) / 2;

    this->lasetTextShowForm->setGeometry(QRect(x,y,formSize.width(),formSize.height()));
    ui->spinBoxLastTextX->setValue(x);
    ui->spinBoxLastTextY->setValue(y);
}


void MainWindow::slots_lastTextTextLeft(){
    lasetTextShowForm->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}

void MainWindow::slots_lastTextTextMid(){
    lasetTextShowForm->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}



void MainWindow::slots_flowerSet(){
    reloadFlowerView();
}

void MainWindow::slots_flowerSetAndSHow(){
    reloadFlowerView();
    playFlower();
}

//--------------------------------
void MainWindow::slots_start(){
    if(!this->countDownTimer->isActive()){
        int sleep = ui->spinBoxStartSleep->value();
        this->countDownTimer->start(sleep);
    }

    showCountDownText = ui->checkBoxContDown->isChecked();
    showLastCountDownText = ui->checkBoxLastCountDown->isChecked();
    showEndText = ui->checkBoxLastText->isChecked();
    showFlowers = ui->checkBoxFlowers->isChecked();

    if(showCountDownText){
        this->countDownShowForm->show();
        //this->countDownShowForm->setTop();
    }else{
        this->countDownShowForm->hide();
    }
    showLastCountDownSec = ui->spinBoxLastSec->value();
    this->lastCloseUpForm->set(showLastCountDownSec);

    flowerEndTimeSec = ui->spinBoxFlowersEndTime->value();
    flowerShowTimeSec = ui->spinBoxFlowersTime->value();

    QDateTime endDateTime = ui->dateTimeEditEndTime->dateTime();
    countDownEndTime = endDateTime.toTime_t();

    QString status = qcn("Running.END:")+ endDateTime.toString("yyyy-MM-dd hh:mm:ss:zzz");
    status.append(qcn(",1:"));
    status.append(showCountDownText ? "true":"false");
    status.append(qcn(",2:"));
    status.append(showLastCountDownText ? "true":"false");
    status.append(",3:");
    status.append(showEndText ? "true":"false");
    status.append(",4:");
    status.append(showFlowers ? "true":"false");

    this->statusLable->setText(status);
    flowerShowed = false;

}
void MainWindow::slots_stop(){
    if(this->countDownTimer->isActive()){
        this->countDownTimer->stop();
    }
    QString status = "Stop...";
    this->statusLable->setText(status);
}
void MainWindow::slots_hideAll(){

}

void MainWindow::slots_menuHomePage(){
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/MountCloud/CountDown")));
}
void MainWindow::slots_about(){
    QMessageBox::information(NULL, "About", "By MountCloud\nmountcloud.org\nmountcloud@outlook.com",QMessageBox::Ok , QMessageBox::Ok);
}
