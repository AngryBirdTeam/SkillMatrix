#ifndef DISPLAYQA_H
#define DISPLAYQA_H

#include <QDialog>
#include <QMessageBox>

#include "QuestionPreview.h"
#include "DisplayInfo.h"

namespace Ui {
class DisplayQA;
}

class DisplayQA : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayQA(QWidget *parent = 0);
    ~DisplayQA();

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
    bool validateOptionInfo();
    bool validateQuestionDetails();

private:
    Ui::DisplayQA *ui;

    static unsigned int MAXOPTION_COUNT;
    unsigned int optionCount = 0;

    QString ErrorMsg;
    QString questionInfo;
    QString textAnswer;
    QString optionType ;
    QString option1Info;
    QString option2Info;
    QString option3Info;
    QString option4Info;


    QuestionPreview *previewQtnPtr;

    int option1Weight;
    int option2Weight;
    int option3Weight;
    int option4Weight;
    int textAnswerWeight;

    QString SelectedSkillName;

    DisplayInfo *displayInfoPtr;

    void Init();
    void DisableMenus();

    void HideMenus();
    void ShowMenus();

    void UpdateOptionList();

    unsigned int GetSkillId();
    void validateText(QString);

    void ClearOptionsInfo();
};

#endif // DISPLAYQA_H
