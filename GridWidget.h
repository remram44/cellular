#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QAbstractItemDelegate>

class Cell;

class MyDelegate : public QAbstractItemDelegate {

    Q_OBJECT

private:
    static QColor getBgColor(unsigned int state);
    static QColor getFgColor(unsigned int state);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

};

class MyModel : public QAbstractTableModel {

private:
    Cell *m_Cells;
    int m_iWidth, m_iHeight;

public:
    void setData(Cell *cells, int width, int height);
    void cellsChanged();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

};

class GridWidget : public QWidget {

    Q_OBJECT

private:
    QTableView *m_pTable;
    MyModel *m_pModel;
    MyDelegate *m_pDelegate;

public:
    GridWidget(QWidget *parent = NULL);
    void update();
    void setData(Cell *cells, int width, int height);

};

#endif
