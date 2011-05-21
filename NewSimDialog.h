#ifndef NEWSIMDIALOG_H
#define NEWSIMDIALOG_H

#include <QDialog>
#include <QSlider>

class MainWindow;

class NewSimDialog : public QDialog {

    Q_OBJECT

private:
    MainWindow *m_pMainWindow;
    QSlider *m_pWidthSlider;
    QSlider *m_pHeightSlider;

private slots:
    void ok();

public:
    NewSimDialog(MainWindow *parent);

signals:
    void newSim(int width, int height, QString script);

};

#endif
