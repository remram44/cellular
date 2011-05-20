#include "GridWidget.h"
#include "Cell.h"

GridWidget::GridWidget()
  : m_Cells(NULL)
{
}

void GridWidget::setData(Cell *cells, int width, int height)
{
    m_Cells = cells;
    m_iWidth = width;
    m_iHeight = height;
}

void GridWidget::update()
{
    // TODO : rendering
}
