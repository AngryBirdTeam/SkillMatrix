#include "AdminLoggedInScreen.h"
#include "ui_AdminLoggedInScreen.h"
#include <QDebug>

AdminLoggedInScreen::AdminLoggedInScreen(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::AdminLoggedInScreen)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Admin Management");

    initialize();

    connect(ui->pbtnOK, SIGNAL(clicked(bool)), this, SLOT(adminSelection()));

    connect(ui->radiobtnDBMgnt, SIGNAL(toggled(bool)), this, SLOT(enableOKBtn(bool)));
    connect(ui->radiobtnEmpMgnt, SIGNAL(toggled(bool)), this, SLOT(enableOKBtn(bool)));
    connect(ui->radiobtnSkillMatrix, SIGNAL(toggled(bool)), this, SLOT(enableOKBtn(bool)));
}

void AdminLoggedInScreen::initialize()
{
    ui->pbtnOK->setEnabled(false);

    //DB management instance creation - future
}

void AdminLoggedInScreen::adminSelection()
{
    if( ui->radiobtnDBMgnt->isChecked() )
    {
        qDebug() << "emitted databaseGUI signal";
        this->close();

        emit databaseGUI();
    }
    else if( ui->radiobtnSkillMatrix->isChecked() )
    {
        qDebug() << "emitted skillMatrixGUI signal";
        this->close();

        emit skillMatrixGUI();
    }
    else if( ui->radiobtnEmpMgnt->isChecked() )
    {
        qDebug() << "emitted employee management GUI signal";
        this->close();

        emit empMgntGUI();
    }
}

void AdminLoggedInScreen::closeEvent (QCloseEvent *event)
{
    //close the application
    this->close();
}

AdminLoggedInScreen::~AdminLoggedInScreen()
{
    delete ui;
}

void AdminLoggedInScreen::enableOKBtn(bool state)
{
    ui->pbtnOK->setEnabled(state);
}
