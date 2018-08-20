#ifndef DISPLAYADDSKILLS_H
#define DISPLAYADDSKILLS_H

#include <QDialog>
#include <QMessageBox>
#include <QSignalMapper>

#include "QuestionPreview.h"

namespace Ui {
class DisplayAddSkills;
}

class DisplayAddSkills : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayAddSkills(QWidget *parent = 0);
    ~DisplayAddSkills();

    void UpdateCurrentSkillName(QString SkillName);

public slots:
    void ClearData();

private slots:
    void AddOptionAndWeightageSlot();
    void AddQuestionSlot(); 
    void AddTextAnswerSlot();
    void PreviewQuestion();
    void RemoveOptionAndWeightageSlot();
    void SaveQuestionDetails();

    void UpdateQText();
    void UpdateOptionInfo(const QString &, int);
    void UpdateOption1Info(const QString &);
    void UpdateOption1Weightage(const QString &);
    void UpdateOption2Info(const QString &);
    void UpdateOption2Weightage(const QString &);
    void UpdateOption3Info(const QString &);
    void UpdateOption3Weightage(const QString &);
    void UpdateOption4Info(const QString &);
    void UpdateOption4Weightage(const QString &);
    void UpdateOptionType(const QString &);
    void UpdateTxtWeightage(const QString &);
    bool validateOptionWeightage();
    bool validateOptionInfo();
    bool validateQuestionDetails();
    bool validateOptionCount();

private:
    Ui::DisplayAddSkills *ui;

    unsigned int maxOptions = 4;
    unsigned int optionCount = 0;

    bool clearFlag = false;
    bool saveFlag = false;

    QMessageBox PopUpMsg;
    QString ErrorMsg;
    QString questionInfo;
    QString textAnswer;
    QString optionType ;
    QString option1Info;
    QString option2Info;
    QString option3Info;
    QString option4Info;

    QSignalMapper *mapper = new QSignalMapper();
    QuestionPreview *previewQtnPtr;

    int option1Weight = 0;
    int option2Weight = 0;
    int option3Weight = 0;
    int option4Weight = 0;
    int textAnswerWeight = 0;
    unsigned int skillId = 0;

    QString SelectedSkillName;

    void DisableOptionMenus();
    void EnableOptionMenus();
    void HideTextEditBoxes();
    void UpdateOptionList();
    void GetSkillId();
    void validateText(QString);
};

#endif // DISPLAYADDSKILLS_H
