#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <QMainWindow>

#include "Cell.h"
#include "NewSimDialog.h"
#include "GridWidget.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    lua_State *m_LuaState;
    Cell *m_Cells;
    NewSimDialog *m_pNewSimDialog;
    int m_iWidth, m_iHeight;
    GridWidget *m_pGrid;

private slots:
    void newSim(int width, int height, QString script);

public:
    MainWindow();

public slots:
    void tick();

};

#endif
