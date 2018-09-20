#include "AboutSkillMatrix.h"
#include "ui_AboutSkillMatrix.h"

AboutSkillMatrix::AboutSkillMatrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutSkillMatrix)
{
    ui->setupUi(this);

    ui->lblIcon->setPixmap(QPixmap(":/Images/Images/AboutSkillMatrix.png"));
}

AboutSkillMatrix::~AboutSkillMatrix()
{
    delete ui;
}

void AboutSkillMatrix::SetAboutInfo(QString AboutStr)
{
    ui->lblCopyright->setText(AboutStr);
    ui->lblCopyright->setAlignment(Qt::AlignCenter);
}

void AboutSkillMatrix::SetVersionInfo(QString VersionStr)
{
    VersionStr.prepend("Version : ");

    ui->lblVersion->setText(VersionStr);
    ui->lblVersion->setAlignment(Qt::AlignCenter);
}

void AboutSkillMatrix::SetCopyRightInfo(QString CopyRightStr)
{
    CopyRightStr.prepend("Copyright : ");

    ui->lblCopyright->setText(CopyRightStr);
    ui->lblCopyright->setAlignment(Qt::AlignCenter);
}

void AboutSkillMatrix::DisplayAboutView()
{
    //Brings the Window to active view if its not active
    if(! this->isActiveWindow() )
    {
        this->activateWindow();
    }

    this->show();
}
