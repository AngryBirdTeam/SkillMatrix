#include "EmployeeManagement.h"
#include "ui_EmployeeManagement.h"

#include <QToolBar>

EmployeeManagement::EmployeeManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeManagement)
{
    ui->setupUi(this);

    ui->gridLayout->setMenuBar(new QToolBar(tr("Skill Matrix")));
}

EmployeeManagement::~EmployeeManagement()
{
    delete ui;
}
