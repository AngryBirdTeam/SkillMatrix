#ifndef TASKMANAGEMENT_H
#define TASKMANAGEMENT_H

#include <QDialog>

#include "DisplayInfo.h"

namespace Ui {
class TaskManagement;
}

class TaskManagement : public QDialog
{
    Q_OBJECT

public:
    explicit TaskManagement(QWidget *parent = nullptr);
    ~TaskManagement();
    explicit TaskManagement(QString Type, QWidget *parent = nullptr);

signals:
    void emitNewSkillCategory();

public slots:
    void DisplayTaskMgmt();

private:
    Ui::TaskManagement *ui;

    QString UiType;
    QString newSkill;
    bool SavedToDB;

    DisplayInfo *displayInfoPtr;

    bool isSkillExists();

private slots:
    void UpdateNewSkillText(const QString &);
    void UpdateTaskToDB();
    void CloseUi();

};

#endif // TASKMANAGEMENT_H
