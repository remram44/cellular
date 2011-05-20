#include "NewSimDialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include "MainWindow.h"

static const char *const defaultScript =
    "function tick(status, neighbours)\n"
    "    local total = 0\n"
    "    for k, v in pairs(neighbours) do\n"
    "        total = total + v\n"
    "    end\n"
    "    if status == 0 and total == 3 then\n"
    "        return 1\n"
    "    elseif status == 1 and (total == 2 or total == 3) then\n"
    "        return 1\n"
    "    else\n"
    "        return 0\n"
    "    end\n"
    "end\n";

NewSimDialog::NewSimDialog(MainWindow *parent)
  : QDialog(parent), m_pMainWindow(parent)
{
    // TODO : NewSimDialog
    setModal(true);
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *ok = new QPushButton(trUtf8("Ok"));
    connect(ok, SIGNAL(clicked()), this, SLOT(ok()));
    layout->addWidget(ok);
    setLayout(layout);
}

void NewSimDialog::ok()
{
    emit newSim(16, 16, defaultScript);
    hide();
}
