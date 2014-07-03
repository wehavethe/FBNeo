#include <QtWidgets>
#include "romdirsdialog.h"
#include "ui_romdirsdialog.h"
#include "burner.h"

TCHAR szAppRomPaths[DIRS_MAX][MAX_PATH] = { { _T("roms/") } };

RomDirsDialog::RomDirsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RomDirsDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Edit ROM paths"));

    m_group = new QButtonGroup(this);
    m_group->addButton(ui->btnEditPath1, 0);
    m_group->addButton(ui->btnEditPath2, 1);
    m_group->addButton(ui->btnEditPath3, 2);
    m_group->addButton(ui->btnEditPath4, 3);

    m_handlers[0] = util::PathHandler(szAppRomPaths[0], ui->lePath1, 0);
    m_handlers[1] = util::PathHandler(szAppRomPaths[1], ui->lePath2, 1);
    m_handlers[2] = util::PathHandler(szAppRomPaths[2], ui->lePath3, 2);
    m_handlers[3] = util::PathHandler(szAppRomPaths[3], ui->lePath4, 3);

    connect(m_group, SIGNAL(buttonClicked(int)), this, SLOT(editPath(int)));
}

RomDirsDialog::~RomDirsDialog()
{
    delete ui;
}

int RomDirsDialog::exec()
{
    for (int i = 0; i < DIRS_MAX; i++)
        m_handlers[i].stringToEditor();

    if (QDialog::exec() == QDialog::Accepted) {
        for (int i = 0; i < DIRS_MAX; i++)
            m_handlers[i].editorToString();
    }
}

void RomDirsDialog::editPath(int no)
{
    m_handlers[no].browse(this);
}
