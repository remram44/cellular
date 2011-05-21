#include "NewSimDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
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
    setModal(true);
    QHBoxLayout *layout = new QHBoxLayout;
    {
        QFormLayout *left = new QFormLayout;
        m_pWidthSlider = new QSlider(Qt::Horizontal);
        m_pWidthSlider->setRange(3, 100);
        m_pWidthSlider->setValue(16);
        left->addRow(trUtf8("&Width:"), m_pWidthSlider);
        m_pHeightSlider = new QSlider(Qt::Horizontal);
        m_pHeightSlider->setRange(3, 100);
        m_pHeightSlider->setValue(16);
        left->addRow(trUtf8("&Height:"), m_pHeightSlider);
        {
            QHBoxLayout *buttons = new QHBoxLayout;
            QPushButton *ok = new QPushButton(trUtf8("Ok"));
            connect(ok, SIGNAL(clicked()), this, SLOT(ok()));
            buttons->addWidget(ok);
            QPushButton *cancel = new QPushButton(trUtf8("Cancel"));
            connect(cancel, SIGNAL(clicked()), this, SLOT(hide()));
            buttons->addWidget(cancel);
            left->addRow(buttons);
        }
        layout->addLayout(left);
    }
    m_pScript = new QTextEdit;
    m_pScript->setAcceptRichText(false);
    m_pScript->setPlainText(defaultScript);
    layout->addWidget(m_pScript);
    setLayout(layout);
}

void NewSimDialog::ok()
{
    emit newSim(m_pWidthSlider->value(), m_pHeightSlider->value(), m_pScript->toPlainText());
    hide();
}
