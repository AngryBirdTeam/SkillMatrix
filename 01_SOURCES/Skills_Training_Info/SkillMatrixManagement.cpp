#include "SkillMatrixManagement.h"
#include "ui_SkillMatrixManagement.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SkillMatrixManagement::SkillMatrixManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkillMatrixManagement)
{
    ui->setupUi(this);

    //  <For displaying Icon>
    IconRed = (QIcon(":/Images/Images/red.png"));
    IconGreen = (QIcon(":/Images/Images/green.png"));

    displayQAPtr = new DisplayQA();
    displayQAPtr->setEnabled(false); // by default

    displayUpdateSkillsPtr = new DisplayUpdateSkills();
    displayUpdateSkillsPtr->setEnabled(false); //by default

    ui->gridLayout->addWidget(displayQAPtr);
    ui->gridLayout->addWidget(displayUpdateSkillsPtr);

    isAddSkills = false;

    connect(this, SIGNAL(ClearOnClose()), displayQAPtr, SLOT(ClearData()));

    UpdateTreeWidgetWithSkillSets();
}

SkillMatrixManagement::~SkillMatrixManagement()
{
    delete ui;
}

void SkillMatrixManagement::UpdateTreeWidgetWithSkillSets()
{
    QString strQuery = "select *from tbl_skill_set";
    QSqlQuery query;

    if( !query.exec(strQuery) )
    {
        qDebug()<<"ERROR = "<<query.lastQuery()<<"\nlast ERROR = "<<query.lastError();
        return;
    }

    qDebug() << "query size of all skills" << query.size();

    QList<QTreeWidgetItem *> skillSetItems;
    QTreeWidgetItem *treeWidgetItemPtr;

    //iterate the records and create tree widget item for each record
    while(query.next())
    {
        treeWidgetItemPtr = new QTreeWidgetItem(ui->treeWidgetSkillSet);
        treeWidgetItemPtr->setText(0, query.value(1).toString() );
        treeWidgetItemPtr->setTextColor(0, Qt::white);

        //update sub skills for each main skill
        UpdateSubSkills(treeWidgetItemPtr, query.value(0).toUInt());

        skillSetItems.push_back( treeWidgetItemPtr );

        SkillSetNames << query.value(1).toString();
    }

    //link all main skill to the tree widget
    ui->treeWidgetSkillSet->addTopLevelItems(skillSetItems);

    QObject::connect(ui->treeWidgetSkillSet,
                     SIGNAL(itemClicked(QTreeWidgetItem *, int)),
                     this,
                     SLOT(updateSubSkillSetStatus(QTreeWidgetItem*, int)));

    //tree widget with all items expanded by default
    ui->treeWidgetSkillSet->expandAll();
}

void SkillMatrixManagement::UpdateSubSkills(QTreeWidgetItem *mainItem, unsigned int ID)
{
    QString strQuery = "select *from tbl_skill_name ";
    strQuery += "where fld_skillsetype_id = '";
    strQuery += QString::number(ID);
    strQuery += "'";

    QSqlQuery query;

    if( !query.exec(strQuery) )
    {
        qDebug()<<"ERROR = "<<query.lastQuery()<<"\nlast ERROR = "<<query.lastError();
        return;
    }

    qDebug() << "query size of skill id " << ID << " is " << query.size();

    QList<QTreeWidgetItem *> subSkillSetItems;
    QTreeWidgetItem *treeWidgetItemPtr;

    //iterate the records and create tree widget item for each record
    while(query.next())
    {
        treeWidgetItemPtr = new QTreeWidgetItem();

        treeWidgetItemPtr->setText(0, query.value(1).toString() );

        //
        treeWidgetItemPtr->setIcon(0,IconRed);
        treeWidgetItemPtr->setTextColor(0,Qt::red);

        subSkillSetItems.push_back( treeWidgetItemPtr );
    }

    //link all the sub skills to the main item
    mainItem->addChildren(subSkillSetItems);
}

void SkillMatrixManagement::updateSubSkillSetStatus(QTreeWidgetItem *item, int column)
{

    //if the main tree widget item is clicked do nothing hence this check
    if( SkillSetNames.contains( item->text(column) ) )
    {
        return;
    }

    qDebug() << "signal emitted for item clicked: item is -> " << item->text(column);

    item->setIcon(column, IconGreen);
    item->setTextColor(column, Qt::green);

    if(isAddSkills)
    {
        if( !displayQAPtr->isEnabled() )
        {
            displayQAPtr->setEnabled(true);
        }

        //emit this signal to clear the add skills ui on change of skill
        emit ClearOnClose();

        displayQAPtr->UpdateCurrentSkillName( item->text(column) );
    }
    else
    {
        if( !displayUpdateSkillsPtr->isEnabled() )
        {
            displayUpdateSkillsPtr->setEnabled(true);
        }
    }
}

void SkillMatrixManagement::DisplayPrepareSkillSet()
{
//    unsigned int count = ui->gridLayout->count();

//    qDebug() << "inside DisplayPrepareSkillSet b4 addWidget, no of items is " << count;

    ui->gridLayout->addWidget(displayQAPtr);

//    count = ui->gridLayout->count();

//    qDebug() << "inside DisplayPrepareSkillSet after addWidget, no of items is " << count;

    displayUpdateSkillsPtr->setVisible(false);
    displayQAPtr->setVisible(true);
    isAddSkills = true;
    this->show();
}

void SkillMatrixManagement::DisplaySkillSet()
{
    displayUpdateSkillsPtr->setVisible(true);
    displayQAPtr->setVisible(false);
    isAddSkills = false;

    this->show();
}

void SkillMatrixManagement::closeEvent (QCloseEvent *event)
{
    Q_UNUSED(event);

    //on close disable the ui
    displayQAPtr->setEnabled(false);
    displayUpdateSkillsPtr->setEnabled(false);

    if(isAddSkills)
    {
        //emit this signal to clear the add skills ui
        emit ClearOnClose();
    }
    else
    {
        //TODO for update skills
    }

    //close the dialog
    this->close();
}
