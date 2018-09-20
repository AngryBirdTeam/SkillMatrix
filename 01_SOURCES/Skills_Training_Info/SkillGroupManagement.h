#ifndef SKILLGROUPMANAGEMENT_H
#define SKILLGROUPMANAGEMENT_H

#include <QDialog>
#include <QListWidgetItem>

#include "TaskManagement.h"

namespace Ui {
class SkillGroupManagement;
}

class SkillGroupManagement : public QDialog
{
    Q_OBJECT

public:
    explicit SkillGroupManagement(QWidget *parent = nullptr);
    ~SkillGroupManagement();

public slots:
    void DisplayDelUi();
    void DisplayAddUi();

private slots:
    void closeEvent (QCloseEvent *event);

    void EnableSkillGroupButtons(QListWidgetItem *currentItem);
    void EnableSubSkillButtons(QListWidgetItem *currentItem);

    void DeleteSkillGroup();
    void DeleteSubSkill();

    void RefreshListWidget();

private:
    Ui::SkillGroupManagement *ui;

    QString selectedSkillGroup;
    QString selectedSubSkill;

    TaskManagement *taskMgmtPtr_AddSkill;
    TaskManagement *taskMgmtPtr_SubSkill;

    QStringList GetAllSkillGroupList();
    QStringList GetSubSkillsList(QString SkillGroupName);

    void DelSkillGrpBtnStatus(bool state);
    void DelSubSkillBtnStatus(bool state);

    void AddSkillGrpBtnStatus(bool state);
    void AddSubSkillBtnStatus(bool state);

    void DisplaySkillGroupManagement();
};

#endif // SKILLGROUPMANAGEMENT_H
