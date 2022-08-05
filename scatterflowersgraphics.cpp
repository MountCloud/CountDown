#include "scatterflowersgraphics.h"
#include <QPixmap>
#include <QDebug>

ScatterFlowersGraphics::ScatterFlowersGraphics(QWidget *parent) : QWidget(parent),
    m_maxSideLength(20),
    m_update(false),
    m_isHidden(false)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    setFixedSize(m_maxSideLength, m_maxSideLength);
}

ScatterFlowersGraphics::~ScatterFlowersGraphics()
{

}

ScatterFlowersGraphics* ScatterFlowersGraphics::getGraphics(const DrawGraphicsInfo& graphicsInfo, QWidget *parent)
{
    ScatterFlowersGraphics* ret = new ScatterFlowersGraphics(parent);

    if(ret != nullptr)
    {
        ret->setGraphicsParameter(graphicsInfo);
    }

    return ret;
}

void ScatterFlowersGraphics::setGraphicsParameter(const DrawGraphicsInfo& graphicsInfo)
{
    m_graphicsInfo = graphicsInfo;

    m_update = true;
}

void ScatterFlowersGraphics::setGraphicsHidden(bool hidden)
{
    m_isHidden = hidden;

    update();
}

void ScatterFlowersGraphics::setMaxSideLength(int maxSideLength)
{
    m_maxSideLength = maxSideLength;

    setFixedSize(m_maxSideLength, m_maxSideLength);
}

void ScatterFlowersGraphics::drawGraphics(QPainter& painter, const DrawGraphicsInfo& graphicsInfo)
{
    switch (graphicsInfo.type)
    {
        case Circle:
        {
            drawCircle(painter, graphicsInfo);
            break;
        }

        case Rect:
        {
            drawRect(painter, graphicsInfo);
            break;
        }

        default:
            drawCircle(painter, graphicsInfo);
            break;
    }
}

void ScatterFlowersGraphics::drawCircle(QPainter& painter, const DrawGraphicsInfo& graphicsInfo)
{
    if((0 < graphicsInfo.sideLength) && (graphicsInfo.sideLength <= m_maxSideLength) &&
       (0 <= graphicsInfo.angle) && (graphicsInfo.angle <= 90))
    {
        int x = this->width() / 2;
        int y = this->height() / 2;
        int r = graphicsInfo.sideLength / 2;

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(graphicsInfo.color);
        painter.translate(x, y);
        painter.rotate(graphicsInfo.angle);
        painter.translate(-x, -y);
        painter.drawEllipse(QPoint(x,y), r, r);
    }
}

void ScatterFlowersGraphics::drawRect(QPainter& painter, const DrawGraphicsInfo& graphicsInfo)
{
    if((0 < graphicsInfo.sideLength) && (graphicsInfo.sideLength <= m_maxSideLength) &&
       (0 <= graphicsInfo.angle) && (graphicsInfo.angle <= 90))
    {
        int centerX = this->width() / 2;
        int centerY = this->height() / 2;

        int x = (this->width() - graphicsInfo.sideLength) / 2;
        int y = (this->height() - graphicsInfo.sideLength) / 2;

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(graphicsInfo.color);
        painter.translate(centerX, centerY);
        painter.rotate(graphicsInfo.angle);
        painter.translate(-centerX, -centerY);
        painter.drawRect(QRect(x, y, graphicsInfo.sideLength, graphicsInfo.sideLength));
    }
}

void ScatterFlowersGraphics::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(m_isHidden)
    {
        DrawGraphicsInfo info = m_graphicsInfo;
        info.color = QColor(255,255,255, 0);

        drawGraphics(painter, info);
    }
    else
    {
        drawGraphics(painter, m_graphicsInfo);
    }
}
