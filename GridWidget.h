#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class Cell;

class GridWidget : public QWidget {
    Q_OBJECT

private:
    Cell *m_Cells;
    int m_iWidth, m_iHeight;

public:
    GridWidget();
    void setData(Cell *cells, int width, int height);
    void update();

};

#endif
