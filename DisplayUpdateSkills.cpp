#include "DisplayUpdateSkills.h"
#include "ui_DisplayUpdateSkills.h"

DisplayUpdateSkills::DisplayUpdateSkills(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayUpdateSkills)
{
    ui->setupUi(this);
}

DisplayUpdateSkills::~DisplayUpdateSkills()
{
    delete ui;
}
