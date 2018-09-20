#ifndef SKILLMATRIXMANAGEMENT_H
#define SKILLMATRIXMANAGEMENT_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "DisplayQA.h"
#include "DisplayUpdateSkills.h"

namespace Ui {
class SkillMatrixManagement;
}

class SkillMatrixManagement : public QDialog
{
    Q_OBJECT

public:
    explicit SkillMatrixManagement(QWidget *parent = 0);
    ~SkillMatrixManagement();

    void DisplayPrepareSkillSet();
    void DisplaySkillSet();

signals:
    void ClearOnClose();

private slots:
    void updateSubSkillSetStatus(QTreeWidgetItem *item, int column);
    void closeEvent (QCloseEvent *event);

private:
    Ui::SkillMatrixManagement *ui;

    QIcon IconRed;
    QIcon IconGreen;

    QStringList SkillSetNames;

    DisplayQA *displayQAPtr;
    DisplayUpdateSkills *displayUpdateSkillsPtr;

    bool isAddSkills;

    void UpdateTreeWidgetWithSkillSets();
    void UpdateSubSkills(QTreeWidgetItem *mainItem, unsigned int ID);
};

#endif // SKILLMATRIXMANAGEMENT_H
