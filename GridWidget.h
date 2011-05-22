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
    Cell *m_pCells;
    int m_iWidth, m_iHeight;

public:
    void setData(Cell *cells, int width, int height);
    void cellsChanged();
    void resetBlank();
    void resetRandom();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

};

class GridWidget : public QTableView {

    Q_OBJECT

private:
    MyModel *m_pModel;
    MyDelegate *m_pDelegate;

public:
    GridWidget(QWidget *parent = NULL);
    void update();
    void setData(Cell *cells, int width, int height);

public slots:
    void resetBlank();
    void resetRandom();

};

#endif
