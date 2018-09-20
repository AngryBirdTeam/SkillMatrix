#ifndef QUESTIONPREVIEW_H
#define QUESTIONPREVIEW_H

#include <QDialog>
#include <QTextEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>

namespace Ui {
class QuestionPreview;
}

class QuestionPreview : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionPreview(QWidget *parent = 0);
    ~QuestionPreview();

    QString questionInfo;
    QString optionType;
    QString option1Info;
    QString option2Info;
    QString option3Info;
    QString option4Info;

    unsigned int optionCount;

    void displayQuestion();



private:
    Ui::QuestionPreview *ui;

    QLabel *questionInfoPtr;
    QTextEdit *textAns;
    QRadioButton *rdbtnOption1;
    QRadioButton *rdbtnOption2;
    QRadioButton *rdbtnOption3;
    QRadioButton *rdbtnOption4;

    QCheckBox *chboxOption1;
    QCheckBox *chboxOption2;
    QCheckBox *chboxOption3;
    QCheckBox *chboxOption4;

    void Init();
    void addWidgets();
    void disableWidgets();

 private slots:
    void closeEvent (QCloseEvent *event);

};

#endif // QUESTIONPREVIEW_H
