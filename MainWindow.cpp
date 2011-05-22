#include "MainWindow.h"

#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow()
  : QMainWindow(NULL), m_LuaState(NULL), m_Cells(NULL)
{
    m_pNewSimDialog = new NewSimDialog(this);
    connect(m_pNewSimDialog, SIGNAL(newSim(int, int, QString)),
        this, SLOT(newSim(int, int, QString)));
    m_pNewSimDialog->hide();

    QMenu *fileMenu = menuBar()->addMenu(trUtf8("&File"));
    {
        QAction *newSim = new QAction(trUtf8("&New simulation..."), this);
        connect(newSim, SIGNAL(triggered()), m_pNewSimDialog, SLOT(show()));
        fileMenu->addAction(newSim);
    }
    fileMenu->addSeparator();
    {
        QAction *quitAct = new QAction(trUtf8("&Quit"), this);
        connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
        fileMenu->addAction(quitAct);
    }

    setCentralWidget(new QFrame);
    QHBoxLayout *layout = new QHBoxLayout;
    m_pGrid = new GridWidget;
    layout->addWidget(m_pGrid);
    {
        QVBoxLayout *right = new QVBoxLayout;

        QPushButton *blank = new QPushButton(trUtf8("Empty the grid"));
        blank->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(blank, SIGNAL(clicked()), m_pGrid, SLOT(resetBlank()));
        right->addWidget(blank);

        QPushButton *random = new QPushButton(trUtf8("Randomize"));
        random->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(random, SIGNAL(clicked()), m_pGrid, SLOT(resetRandom()));
        right->addWidget(random);

        QPushButton *t = new QPushButton(trUtf8("Tick"));
        t->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(t, SIGNAL(clicked()), this, SLOT(tick()));
        right->addWidget(t);

        layout->addLayout(right);
    }
    // TODO : slider to set a simulation speed (and disable the Tick button)
    centralWidget()->setLayout(layout);
}

void MainWindow::newSim(int width, int height, QString script)
{
    if(m_Cells)
        delete[] m_Cells;

    if(m_LuaState)
        lua_close(m_LuaState);
    m_LuaState = lua_open();
    luaL_openlibs(m_LuaState);

    if(luaL_loadstring(m_LuaState, script.toAscii()) != 0)
    {
        QMessageBox::critical(this, trUtf8("Error from Lua"),
                trUtf8("Error loading script:\n%1").arg(lua_tostring(m_LuaState, -1)));
    }

    if(lua_pcall(m_LuaState, 0, 0, 0) != 0)
    {
        QMessageBox::critical(this, trUtf8("Error from Lua"),
                trUtf8("Error starting script:\n%1").arg(lua_tostring(m_LuaState, -1)));
    }

    m_Cells = new Cell[width*height];
    m_iWidth = width;
    m_iHeight = height;
    m_pGrid->setData(m_Cells, width, height);
}

void MainWindow::tick()
{
    if(!m_Cells)
        return ;
    int y, x;
    for(y = 0; y < m_iHeight; y++)
    {
        for(x = 0; x < m_iWidth; x++)
        {
            Cell &cell = m_Cells[y*m_iWidth + x];
            lua_getglobal(m_LuaState, "tick");
            lua_pushinteger(m_LuaState, cell.getState());
            lua_createtable(m_LuaState, 0, 8);
            int i, j;
            for(j = -1; j <= 1; j++)
            {
                if(y+j < 0 || y+j >= m_iHeight)
                    continue;
                for(i = -1; i <= 1; i++)
                {
                    if(i == 0 && j == 0)
                        continue;
                    if(x+i < 0 || x+i >= m_iWidth)
                        continue;
                    QString key = QString("%1;%2").arg(i).arg(j);
                    lua_pushstring(m_LuaState, key.toAscii());
                    lua_pushinteger(m_LuaState, m_Cells[(y+j)*m_iWidth + x+i].getState());
                    lua_settable(m_LuaState, -3);
                }
            }
            if(lua_pcall(m_LuaState, 2, 1, 0) != 0)
            {
                QMessageBox::critical(this, trUtf8("Error from Lua"),
                        trUtf8("An error occurred:\n%1").arg(lua_tostring(m_LuaState, -1)));
            }
            cell.setFutureState(lua_tointeger(m_LuaState, -1));
        }
    }

    for(y = 0; y < m_iHeight; y++)
    {
        for(x = 0; x < m_iWidth; x++)
            m_Cells[y*m_iWidth + x].tick();
    }

    m_pGrid->update();
}
