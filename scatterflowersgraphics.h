#ifndef SCATTERFLOWERSGRAPHICS_H
#define SCATTERFLOWERSGRAPHICS_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class ScatterFlowersGraphics : public QWidget
{
    Q_OBJECT

public:
    enum GraphicsType
    {
        Circle,
        Rect
    };

    struct DrawGraphicsInfo
    {
        GraphicsType type;
        QColor color;
        qreal angle;
        int sideLength;

        DrawGraphicsInfo() : type(Circle), color(Qt::white), angle(0), sideLength(1)
        {}
    };

public:
    ~ScatterFlowersGraphics();

    static ScatterFlowersGraphics* getGraphics(const DrawGraphicsInfo& graphicsInfo, QWidget *parent = nullptr);
    void setGraphicsParameter(const DrawGraphicsInfo& graphicsInfo);
    void setGraphicsHidden(bool hidden);
    void setMaxSideLength(int maxSideLength);

private:
    explicit ScatterFlowersGraphics(QWidget *parent = nullptr);

    void drawGraphics(QPainter& painter, const DrawGraphicsInfo& graphicsInfo);
    void drawCircle(QPainter& painter, const DrawGraphicsInfo& graphicsInfo);
    void drawRect(QPainter& painter, const DrawGraphicsInfo& graphicsInfo);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_maxSideLength;

    DrawGraphicsInfo m_graphicsInfo;

    bool m_update;

    bool m_isHidden;
};

#endif // SCATTERFLOWERSGRAPHICS_H
