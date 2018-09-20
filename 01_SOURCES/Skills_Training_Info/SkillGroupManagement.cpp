#include "SkillGroupManagement.h"
#include "ui_SkillGroupManagement.h"

#include <QSqlQuery>
#include <QDebug>

SkillGroupManagement::SkillGroupManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkillGroupManagement)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Skill Group Management");

    taskMgmtPtr_AddSkill = new TaskManagement("Add Skill");
    taskMgmtPtr_SubSkill = new TaskManagement("Sub Skill");

    connect(taskMgmtPtr_AddSkill, SIGNAL(emitNewSkillCategory()), this, SLOT(RefreshListWidget()));

    connect(ui->pbtnAddSkillGrp, SIGNAL(clicked()), taskMgmtPtr_AddSkill, SLOT(DisplayTaskMgmt()) );
    connect(ui->pbtnAddSubSkill, SIGNAL(clicked()), taskMgmtPtr_SubSkill, SLOT(DisplayTaskMgmt()) );

    connect(ui->pbtnDelSkillGrp, SIGNAL(clicked()), SLOT(DeleteSkillGroup()) );
    connect(ui->pbtnDelSubSkill, SIGNAL(clicked()), SLOT(DeleteSubSkill()) );

    connect(ui->SkillGrpListWgt, SIGNAL(itemClicked(QListWidgetItem *)),
            SLOT(EnableSkillGroupButtons(QListWidgetItem*)) );

    connect(ui->SubSkillListWgt, SIGNAL(itemClicked(QListWidgetItem *)),
            SLOT(EnableSubSkillButtons(QListWidgetItem*)) );

    DelSkillGrpBtnStatus(false);
    DelSubSkillBtnStatus(false);

    AddSkillGrpBtnStatus(false);
    AddSubSkillBtnStatus(false);

    ui->pbtnAddSkillGrp->hide();
    ui->pbtnAddSubSkill->hide();
    ui->pbtnDelSkillGrp->hide();
    ui->pbtnDelSubSkill->hide();
}

SkillGroupManagement::~SkillGroupManagement()
{
    delete ui;

    if(taskMgmtPtr_AddSkill != nullptr)
    {
        delete taskMgmtPtr_AddSkill;
        taskMgmtPtr_AddSkill = nullptr;
    }

    if(taskMgmtPtr_SubSkill != nullptr)
    {
        delete taskMgmtPtr_SubSkill;
        taskMgmtPtr_SubSkill = nullptr;
    }
}

void SkillGroupManagement::DisplayAddUi()
{   
    AddSkillGrpBtnStatus(true);

    ui->pbtnAddSkillGrp->show();
    ui->pbtnAddSubSkill->show();

    DisplaySkillGroupManagement();
}

void SkillGroupManagement::DisplayDelUi()
{
    DelSkillGrpBtnStatus(true);

    ui->pbtnDelSkillGrp->show();
    ui->pbtnDelSubSkill->show();

    DisplaySkillGroupManagement();
}

void SkillGroupManagement::DisplaySkillGroupManagement()
{
    QStringList NamesList;

    NamesList = GetAllSkillGroupList();

    ui->SkillGrpListWgt->addItems(NamesList);

    this->show();
}

void SkillGroupManagement::RefreshListWidget()
{
    ui->SkillGrpListWgt->clear();
    ui->SubSkillListWgt->clear();

    DisplaySkillGroupManagement();
}

QStringList SkillGroupManagement::GetAllSkillGroupList()
{
    ui->SkillGrpListWgt->clear();
    ui->SubSkillListWgt->clear();

    QSqlQuery query;
    QString strQuery = "select fld_skillset_type from tbl_skill_set";

    QStringList SkillGroupList;

    if( !query.exec(strQuery) )
    {
        //error
        return SkillGroupList;
    }

    while(query.next())
    {
        SkillGroupList.push_back( query.value(0).toString() );
    }

    return SkillGroupList;
}

QStringList SkillGroupManagement::GetSubSkillsList(QString SkillGroupName)
{
    QStringList SubSkillList;

    QSqlQuery query;

    QString strQuery;

    strQuery = "select fld_skillsetype_id from tbl_skill_set where fld_skillset_type = '";
    strQuery += SkillGroupName;
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return SubSkillList;
    }

    if( !query.next() )
    {
        //error
        return SubSkillList;
    }

    strQuery = "select fld_skillname from tbl_skill_name where fld_skillsetype_id = '";
    strQuery += QString::number( query.value(0).toInt() );
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return SubSkillList;
    }

    while(query.next())
    {
        SubSkillList.push_back( query.value(0).toString() );
    }

    return SubSkillList;
}

void SkillGroupManagement::EnableSkillGroupButtons(QListWidgetItem *currentItem)
{
    if( currentItem != nullptr )
    {
        if(currentItem->text() != selectedSkillGroup)
        {
            ui->SubSkillListWgt->clear();
            selectedSkillGroup = currentItem->text();

            QStringList NamesList = GetSubSkillsList(selectedSkillGroup);

            ui->SubSkillListWgt->addItems(NamesList);
        }
    }
}

void SkillGroupManagement::EnableSubSkillButtons(QListWidgetItem *currentItem)
{
    if( currentItem != nullptr )
    {
        if(currentItem->text() != selectedSubSkill)
        {
            selectedSubSkill =  currentItem->text();
        }
    }
}

void SkillGroupManagement::AddSkillGrpBtnStatus(bool state)
{
    ui->pbtnAddSkillGrp->setEnabled(state);
}

void SkillGroupManagement::AddSubSkillBtnStatus(bool state)
{
    ui->pbtnAddSubSkill->setEnabled(state);
}

void SkillGroupManagement::DelSkillGrpBtnStatus(bool state)
{
    ui->pbtnDelSkillGrp->setEnabled(state);
}

void SkillGroupManagement::DelSubSkillBtnStatus(bool state)
{
    ui->pbtnDelSubSkill->setEnabled(state);
}

void SkillGroupManagement::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    this->close();

    DelSkillGrpBtnStatus(false);
    DelSubSkillBtnStatus(false);

    AddSkillGrpBtnStatus(false);
    AddSubSkillBtnStatus(false);

    selectedSkillGroup.clear();
    selectedSubSkill.clear();

    ui->pbtnAddSkillGrp->hide();
    ui->pbtnAddSubSkill->hide();
    ui->pbtnDelSkillGrp->hide();
    ui->pbtnDelSubSkill->hide();
}

void SkillGroupManagement::DeleteSkillGroup()
{
    QSqlQuery query;

    QString strQuery;

    strQuery = "select fld_skillsetype_id from tbl_skill_set where fld_skillset_type = '";
    strQuery += selectedSkillGroup;
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return;
    }

    if( !query.next() )
    {
        //error
        return;
    }

    qDebug() << "ID for selected skill " << selectedSkillGroup << " is : " << query.value(0).toInt();

    strQuery = "delete from tbl_skill_name where fld_skillsetype_id = '";
    strQuery += QString::number( query.value(0).toInt() );
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return;
    }

    qDebug() << "data from tbl_skill_name deleted";

    strQuery = "delete from tbl_skill_set where fld_skillset_type = '";
    strQuery += selectedSkillGroup;
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return;
    }

    qDebug() << "data from tbl_skill_set deleted";

    ui->SkillGrpListWgt->clear();
    ui->SubSkillListWgt->clear();

    //update the new data for view
    DisplaySkillGroupManagement();

}

void SkillGroupManagement::DeleteSubSkill()
{
    QSqlQuery query;

    QString strQuery;

    strQuery = "select fld_skillsetype_id from tbl_skill_set where fld_skillset_type = '";
    strQuery += selectedSkillGroup;
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return;
    }

    qDebug() << "ID for selected skill " << selectedSkillGroup << " is : " << query.value(0).toInt();

    strQuery = "delete from tbl_skill_name where fld_skillname = '";
    strQuery += selectedSubSkill;
    strQuery += "'";

    if( !query.exec(strQuery) )
    {
        //error
        return;
    }

    qDebug() << "data from tbl_skill_name deleted";

    ui->SkillGrpListWgt->clear();
    ui->SubSkillListWgt->clear();

    //update the new data for view
    DisplaySkillGroupManagement();
}
