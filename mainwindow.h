#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include "lastcloseupform.h"
#include "textshowform.h"

#include "scatterflowers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event) override;
private:
    Ui::MainWindow *ui;
    TextShowForm* countDownShowForm = NULL;
    LastCloseUpForm* lastCloseUpForm = NULL;
    TextShowForm* lasetTextShowForm = NULL;
    QTimer* countDownTimer = NULL;
    QLabel* statusLable;
    ScatterFlowers* scatterFlowers = NULL;
    bool stateyulan = false;
    bool statestart = false;
    int lastnum = 60;

    int lastExecTime = 0;

    int countDownEndTime = 0;
    bool showCountDownText = false;
    int showLastCountDownSec = 0;
    bool showLastCountDownText = false;
    bool showEndText = false;
    bool showFlowers = false;

    bool flowerShowed = false;
    int flowerEndTimeSec = 0;
    int flowerShowTimeSec = 0;

    int flowerDisplayTime = 0;



private:
    void init();
    void setCountDown(QString str,QString day,QString hour,QString minute,QString second);

    void reloadFlowerView();
    void playFlower();

private slots:
    void slots_menuHomePage();
    void slots_about();

    void slots_countDown();

    void slots_countDownSelectColor();
    void slots_countDownSetMid();
    void slots_countDownTextConfig();
    void slots_countDownPreview();
    void slots_countDownTextLeft();
    void slots_countDownTextMid();

    void slots_lastSelectColor();
    void slots_lastTimeSet();
    void slots_lastPreview();
    void slots_lastSetMid();

    void slots_lastTextSelectColor();
    void slots_setLastTextConfig();
    void slots_lastTextPreview();
    void slots_lastTextSetMid();
    void slots_lastTextTextLeft();
    void slots_lastTextTextMid();

    void slots_flowerSet();
    void slots_flowerSetAndSHow();

    void slots_start();
    void slots_stop();
    void slots_hideAll();
};
#endif // MAINWINDOW_H
