#include "TaskManagement.h"
#include "ui_TaskManagement.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

TaskManagement::TaskManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskManagement)
{
    ui->setupUi(this);

}

TaskManagement::TaskManagement(QString Type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskManagement)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->pbtnOK->setEnabled(false);

    displayInfoPtr = DisplayInfo::getInstance();

    if(Type == "Add Skill")
    {
        QPixmap imgPixmap(":/Images/Images/NewSkill.png");
        ui->lblImage->setPixmap(imgPixmap);
        UiType = Type;

        ui->lblHeading->setText("Enter the New Skill Category");
    }
    else if(Type == "Sub Skill")
    {
        //TBD
        QPixmap imgPixmap(":/Images/Images/NewSkill.png");
        ui->lblImage->setPixmap(imgPixmap);
        UiType = Type;

        ui->lblHeading->setText("Enter the Sub Skill Name");
    }
    else
    {
        //TBD
    }

    SavedToDB = false;

    connect(ui->lineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateNewSkillText(const QString &)));
    connect(ui->pbtnOK, SIGNAL(clicked()), SLOT(UpdateTaskToDB()));
    connect(ui->pbtnClose, SIGNAL(clicked()), SLOT(CloseUi()));
}

TaskManagement::~TaskManagement()
{
    delete ui;
}




void TaskManagement::UpdateNewSkillText(const QString &newSkillName)
{
    if(newSkillName.isEmpty())
    {
        if(ui->pbtnOK->isEnabled())
        {
            ui->pbtnOK->setEnabled(false);
        }
    }
    else
    {
        newSkill =  newSkillName;
        ui->pbtnOK->setEnabled(true);
        qDebug()<<"New Skill is: "<<newSkill;


    }
}

void TaskManagement::DisplayTaskMgmt()
{

    //    if(UiType == "Add Skill")
    //    {
    this->show();
    //    }
    //    else
    //    {
    //        //TBD
    //    }
}

void TaskManagement::UpdateTaskToDB()
{
    QSqlQuery query;
    QString strQuery;
    QSqlRecord result;

    if(UiType == "Add Skill")
     {  //Check if skill already exists
         if(isSkillExists())
         {
           displayInfoPtr->DisplayMessage("Skill already exists", DisplayInfo::MessageType::Error);
           return;
         }
         else
         {
             //implement save to db logic here - pop up msg on success and failure
             strQuery = "INSERT INTO tbl_skill_set (fld_skillset_type) VALUES('";
             strQuery+= newSkill;
             strQuery+= "')";

             if(query.exec(strQuery))
             {
                 displayInfoPtr->DisplayMessage("New Skill added successfuly", DisplayInfo::MessageType::Normal );
                 qDebug()<<"Question added successfully";
             }
             else
             {
                 displayInfoPtr->DisplayMessage("Failed to add new skill", DisplayInfo::MessageType::Error );
                 qDebug()<<"ERROR = "<<query.lastQuery();
             }

             //close this ui
             CloseUi();

             //emit a user defined signal to refresh the list widget
             emitNewSkillCategory();
         }

    }
    else if(UiType == "Sub Skill")
    {
        //TBD
    }
    else
    {
        //TBD
    }
}

bool TaskManagement::isSkillExists()
{
    QSqlQuery query;
    QString strQuery;
    strQuery = "SELECT *FROM tbl_skill_set WHERE fld_skillset_type='";
    strQuery+= newSkill;
    strQuery+= "'";
    if(query.exec(strQuery))
    {

       if(query.next())
       {
          return true;
       }
       else
       {
           return false;
       }
    }
    else
    {
        displayInfoPtr->DisplayMessage("Failed to execute query", DisplayInfo::MessageType::Error);
        return false;
    }
}

void TaskManagement::CloseUi()
{
    ui->lineEdit->clear();
    ui->pbtnOK->setEnabled(false);
    this->close();
}
