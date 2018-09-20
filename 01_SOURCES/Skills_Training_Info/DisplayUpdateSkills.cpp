#include "DisplayUpdateSkills.h"
#include "ui_DisplayUpdateSkills.h"

DisplayUpdateSkills::DisplayUpdateSkills(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayUpdateSkills)
{
    ui->setupUi(this);

    QPixmap imgPixMap(":/Images/Images/Ready_Set_Go.png");
    ui->lblImage->setPixmap(imgPixMap);
    ui->lblImage->show();
}

DisplayUpdateSkills::~DisplayUpdateSkills()
{
    delete ui;
}
