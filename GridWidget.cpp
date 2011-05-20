#include "GridWidget.h"

#include <QPainter>
#include <cstdlib>
#include <ctime>
#include "Cell.h"

QColor GridWidget::getBgColor(unsigned int state)
{
    switch(state)
    {
    case 0:
        return QColor(255, 255, 255);
        break;
    case 1:
        return QColor(0, 0, 0);
        break;
    case 2:
        return QColor(255, 0, 0);
        break;
    case 3:
        return QColor(0, 0, 255);
        break;
    case 4:
        return QColor(0, 255, 0);
        break;
    case 5:
        return QColor(0, 255, 255);
        break;
    case 6:
        return QColor(255, 255, 0);
        break;
    case 7:
        return QColor(255, 0, 255);
        break;
    default:
        return QColor(127, 127, 127);
    }
}

QColor GridWidget::getFgColor(unsigned int state)
{
    return QColor(255, 0, 0);
    switch(state)
    {
    case 1:
        return QColor(255, 255, 255);
        break;
    default:
        return QColor(0, 0, 0);
        break;
    }
}

GridWidget::GridWidget(QWidget *parent)
  : QWidget(parent), m_Cells(NULL)
{
}

void GridWidget::setData(Cell *cells, int width, int height)
{
    m_Cells = cells;
    m_iWidth = width;
    m_iHeight = height;
    setMinimumSize(m_iWidth * 20, m_iHeight * 20);

    srand(time(NULL));
    int i;
    for(i = 0; i < width*height; i++)
    {
        m_Cells[i].setFutureState(rand()%2);
        m_Cells[i].tick();
    }
}

void GridWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QColor(0, 0, 0));
    painter.drawRect(-99999, -99999, 99999, 99999);

    int y, x;
    for(y = 0; y < m_iHeight; y++)
    {
        for(x = 0; x < m_iWidth; x++)
        {
            Cell &cell = m_Cells[y*m_iWidth + x];
            painter.setPen(Qt::NoPen);
            painter.setBrush(getBgColor(cell.getState()));
            painter.drawRect(x*20, y*20, x*20 + 19, y*20 + 19);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(getFgColor(cell.getState()));
            painter.drawText(20*x+6, 20*y+14, QString("%1").arg(cell.getState()));
        }
    }
}
