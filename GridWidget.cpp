#include "GridWidget.h"

#include <QPainter>
#include <QHeaderView>
#include <cstdlib>
#include "Cell.h"

GridWidget::GridWidget(QWidget *parent)
  : QTableView(parent)
{
    m_pDelegate = new MyDelegate;
    m_pModel = new MyModel;

    setShowGrid(true);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    horizontalHeader()->setMinimumSectionSize(1);
    verticalHeader()->setMinimumSectionSize(1);
    setModel(m_pModel);
    setItemDelegate(m_pDelegate);
}

void GridWidget::setData(Cell *cells, int width, int height)
{
    m_pModel->setData(cells, width, height);
    update();
}

void GridWidget::update()
{
    m_pModel->cellsChanged();
    resizeColumnsToContents();
    resizeRowsToContents();
}

void GridWidget::resetBlank()
{
    m_pModel->resetBlank();
}

void GridWidget::resetRandom()
{
    m_pModel->resetRandom();
}

void MyModel::setData(Cell *cells, int width, int height)
{
    m_pCells = cells;
    m_iWidth = width;
    m_iHeight = height;

    reset();
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_iHeight;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return m_iWidth;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return m_pCells[index.row()*m_iWidth + index.column()].getState();
}

QVariant MyModel::headerData(int /* section */, Qt::Orientation /* orientation */,
        int role) const
{
    if(role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}

void MyModel::cellsChanged()
{
    reset();
}

void MyModel::resetBlank()
{
    if(!m_pCells)
        return ;

    int i;
    for(i = 0; i < m_iWidth*m_iHeight; i++)
    {
        m_pCells[i].setFutureState(0);
        m_pCells[i].tick();
    }
    reset();
}

void MyModel::resetRandom()
{
    if(!m_pCells)
        return ;

    int i;
    for(i = 0; i < m_iWidth*m_iHeight; i++)
    {
        m_pCells[i].setFutureState(rand()%2);
        m_pCells[i].tick();
    }
    reset();
}

QColor MyDelegate::getBgColor(unsigned int state)
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

QColor MyDelegate::getFgColor(unsigned int state)
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

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    if(option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());
    unsigned int state = index.model()->data(index, Qt::DisplayRole).toUInt();

    painter->save();

    painter->setPen(Qt::NoPen);
    painter->setBrush(getBgColor(state));
    painter->drawRect(option.rect);

    painter->setPen(getFgColor(state));
    painter->setBrush(Qt::NoBrush);
    painter->drawText(option.rect, Qt::AlignCenter, QString("%1").arg(state));

    painter->restore();
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem & /*option*/, const QModelIndex & /*index*/) const
{
    return QSize(20, 20);
}
