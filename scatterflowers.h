#ifndef SCATTERFLOWERS_H
#define SCATTERFLOWERS_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMap>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include "scatterflowersgraphics.h"

namespace Ui {
class ScatterFlowers;
}


class ScatterFlowers : public QWidget
{
    Q_OBJECT

public:
    ScatterFlowers(QWidget *parent = nullptr);
    ScatterFlowers(int kMaxGraphicsCount,int playCount,int width,int height,QWidget *parent = nullptr);
    ~ScatterFlowers();

    void startScatterFlowers();
    void stopScatterFlowers();

    bool getFlowerIsStart();
    void setTop();
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    struct GraphicsInfo
    {
        QPoint startPoint;
        QPoint endPoint;
        bool isShow;
        ScatterFlowersGraphics::DrawGraphicsInfo drawGraphicsinfo;
        ScatterFlowersGraphics* scatterFlowersGraphics;
        QAbstractAnimation* animation;

        GraphicsInfo() : startPoint(0,0), endPoint(0,0), isShow(false), scatterFlowersGraphics(nullptr) {}
    };

private:
    void initUI();
    int randNumber(int range);
    ScatterFlowersGraphics::GraphicsType randGraphics();
    qreal randAngle();
    QColor randColor();
    int randSideLength();
    QPoint randGraphicsPos(bool isStart);

    void updateGraphicsInfo();
    int graphicsCount();

    bool flowerIsStart = false;
    int w = 400;
    int h = 400;
    int playCount = -1;

private:
    //QPropertyAnimation* m_scatterFlowersAnimation;
    //QMap<int, GraphicsInfo> m_graphicsInfoMap;
    QParallelAnimationGroup* m_animationGroup;

    const int m_maxSideLength;
    const int m_animationTime;
    int m_graphicsCount;
    int m_maxGraphicsCount;
    int kMaxGraphicsCount = 60;   //最大数量60
};

#endif // SCATTERFLOWERS_H
