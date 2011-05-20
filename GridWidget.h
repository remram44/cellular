#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class Cell;

class GridWidget : public QWidget {
    Q_OBJECT

private:
    Cell *m_Cells;
    int m_iWidth, m_iHeight;

private:
    QColor getBgColor(unsigned int state);
    QColor getFgColor(unsigned int state);

protected:
    void paintEvent(QPaintEvent *event);

public:
    GridWidget(QWidget *parent = NULL);
    void setData(Cell *cells, int width, int height);

};

#endif
