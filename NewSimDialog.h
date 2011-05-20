#ifndef NEWSIMDIALOG_H
#define NEWSIMDIALOG_H

#include <QDialog>

class MainWindow;

class NewSimDialog : public QDialog {

    Q_OBJECT

private:
    MainWindow *m_pMainWindow;

private slots:
    void ok();

public:
    NewSimDialog(MainWindow *parent);

signals:
    void newSim(int width, int height, QString script);

};

#endif
