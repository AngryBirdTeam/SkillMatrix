#include "TrainingDisplay.h"
#include "ui_TrainingDisplay.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

TrainingDisplay::TrainingDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingDisplay)
{
    ui->setupUi(this);

    Init();

    DisableTables();

    //Function to display the learning plan for a particular user
    ShowLearningPlan("kmv7kor");
    ShowLearningHistory("kmv7kor");
}

TrainingDisplay::~TrainingDisplay()
{
    delete ui;
}

void TrainingDisplay::Init()
{
    //ui->tblLearningHistory->clear();
    //ui->grpBoxLearningPlan->clear();
    learningPlanTblColCount = 4;
    learningHistoryTblColCount = 2;

   // QStringList learningPlanHeader = {"Skill Type", "Skill Name", "Due Date", "Status"};
   // QStringList learningHistoryHeader = {"Skill Type", "Skill Name"};

}
void TrainingDisplay::DisableTables()
{
    ui->tblLearningPlan->hide();
    ui->tblLearningHistory->hide();
    ui->lblNoTraining->hide();
    ui->lblNoLearningRecord->hide();
}

void TrainingDisplay::ShowLearningPlan(QString User)
{
    QString strQuery;
    int result, index=0;

    QStringList learningPlanHeader = {"Skill Type", "Skill Name", "Due Date", "Status"};

    strQuery = "SELECT *FROM tbl_learning_plan WHERE fld_username='";
    strQuery+= User;
    strQuery+= "'AND fld_status!='Completed'";

    QSqlQuery query(strQuery);
    qDebug()<<"ERROR = "<<query.lastQuery();


    result = query.size();
    if(result>0)
    {
        //Set number of rows and columns in the table
        ui->tblLearningPlan->setColumnCount(learningPlanTblColCount);
        ui->tblLearningPlan->setRowCount(result);

        ui->tblLearningPlan->setHorizontalHeaderLabels(learningPlanHeader);

        while(query.next())
        {
            ui->tblLearningPlan->setItem(index,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tblLearningPlan->setItem(index,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tblLearningPlan->setItem(index,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tblLearningPlan->setItem(index,3,new QTableWidgetItem(query.value(4).toString()));
            index++;
        }
        ui->tblLearningPlan->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tblLearningPlan->show();
    }
    else
    {

        ui->lblNoTraining->show();
    }

}

void TrainingDisplay::ShowLearningHistory(QString User)
{
   QString strQuery;
   int result, index=0;

   QStringList learningHistoryHeader = {"Skill Type", "Skill Name"};

   strQuery = "SELECT *FROM tbl_learning_plan WHERE fld_username='";
   strQuery+= User;
   strQuery+= "'AND fld_status='Completed'" ;

   QSqlQuery query(strQuery);

   result = query.size();
   if(result>0)
   {
       //Set number of rows and columns in the table
       ui->tblLearningHistory->setColumnCount(learningHistoryTblColCount);
       ui->tblLearningHistory->setRowCount(result);

       ui->tblLearningHistory->setHorizontalHeaderLabels(learningHistoryHeader);


       while(query.next())
       {
           ui->tblLearningHistory->setItem(index,0,new QTableWidgetItem(query.value(0).toString()));
           ui->tblLearningHistory->setItem(index,1,new QTableWidgetItem(query.value(1).toString()));
           index++;
       }
       ui->tblLearningHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
       ui->tblLearningHistory->show();
   }
   else
   {
     ui->lblNoLearningRecord->show();
   }

}

