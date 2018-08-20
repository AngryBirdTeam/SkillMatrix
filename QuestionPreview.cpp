#include "QuestionPreview.h"
#include "ui_QuestionPreview.h"

#include <QSqlQuery>
#include <QDebug>

QuestionPreview::QuestionPreview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionPreview)
{
    ui->setupUi(this);

}

QuestionPreview::~QuestionPreview()
{
    delete ui;
}

void QuestionPreview :: displayQuestion()
{
    questionInfoPtr = new QTextEdit();
    questionInfoPtr->setText(questionInfo);
    ui->verticalLayout->addWidget(questionInfoPtr);

    if(optionType == "Radio Button")
    {
        switch(optionCount)
        {
            case 2: rdbtnOption1 = new QRadioButton();
                    rdbtnOption1->setText(option1Info);
                    rdbtnOption2 = new QRadioButton();
                    rdbtnOption2->setText(option2Info);
                    ui->verticalLayout->addWidget(rdbtnOption1);
                    ui->verticalLayout->addWidget(rdbtnOption2);
            break;

            case 3: rdbtnOption1 = new QRadioButton();
                    rdbtnOption1->setText(option1Info);
                    rdbtnOption2 = new QRadioButton();
                    rdbtnOption2->setText(option2Info);
                    rdbtnOption3 = new QRadioButton();
                    rdbtnOption3->setText(option3Info);
                    ui->verticalLayout->addWidget(rdbtnOption1);
                    ui->verticalLayout->addWidget(rdbtnOption2);
                    ui->verticalLayout->addWidget(rdbtnOption3);


            break;

            case 4: rdbtnOption1 = new QRadioButton();
                    rdbtnOption1->setText(option1Info);
                    rdbtnOption2 = new QRadioButton();
                    rdbtnOption2->setText(option2Info);
                    rdbtnOption3 = new QRadioButton();
                    rdbtnOption3->setText(option3Info);
                    rdbtnOption4 = new QRadioButton();
                    rdbtnOption4->setText(option4Info);

                    ui->verticalLayout->addWidget(rdbtnOption1);
                    ui->verticalLayout->addWidget(rdbtnOption2);
                    ui->verticalLayout->addWidget(rdbtnOption3);
                    ui->verticalLayout->addWidget(rdbtnOption4);


            break;

        }
    }
    else if(optionType == "Check Box")
    {

        switch(optionCount)
        {
            case 2: chboxOption1 = new QCheckBox();
                    chboxOption1->setText(option1Info);
                    chboxOption2 = new QCheckBox();
                    chboxOption2->setText(option2Info);
                    ui->verticalLayout->addWidget(chboxOption1);
                    ui->verticalLayout->addWidget(chboxOption2);
            break;

            case 3: chboxOption1 = new QCheckBox();
                    chboxOption1->setText(option1Info);
                    chboxOption2 = new QCheckBox();
                    chboxOption2->setText(option2Info);
                    chboxOption3 = new QCheckBox();
                    chboxOption3->setText(option3Info);
                    ui->verticalLayout->addWidget(chboxOption1);
                    ui->verticalLayout->addWidget(chboxOption2);
                    ui->verticalLayout->addWidget(chboxOption3);


            break;

            case 4: chboxOption1 = new QCheckBox();
                    chboxOption1->setText(option1Info);
                    chboxOption2 = new QCheckBox();
                    chboxOption2->setText(option2Info);
                    chboxOption3 = new QCheckBox();
                    chboxOption3->setText(option3Info);
                    chboxOption4 = new QCheckBox();
                    chboxOption4->setText(option4Info);
                    ui->verticalLayout->addWidget(chboxOption1);
                    ui->verticalLayout->addWidget(chboxOption2);
                    ui->verticalLayout->addWidget(chboxOption3);
                    ui->verticalLayout->addWidget(chboxOption4);

            break;

        }
     }
    else
        {

            textAns = new QTextEdit();
            ui->verticalLayout->addWidget(textAns);
        }
    this->show();
}

void QuestionPreview :: Delete()
{
    if(questionInfoPtr!=nullptr)
    {
        delete questionInfoPtr;
    }
    if(textAns!=nullptr)
    {
        delete textAns;
    }
    if(rdbtnOption1!=nullptr)
    {

        delete rdbtnOption1;
    }
    if(rdbtnOption2!=nullptr)
    {

        delete rdbtnOption2;
    }
    if(rdbtnOption3!=nullptr)
    {
        delete rdbtnOption3;
    }
    if(rdbtnOption4!=nullptr)
    {
        delete rdbtnOption4;
    }
    if(chboxOption1!=nullptr)
    {
        delete chboxOption1;
    }
    if(chboxOption2!=nullptr)
    {
        delete chboxOption2;
    }
    if(chboxOption3!=nullptr)
    {
        delete chboxOption3;
    }
    if(chboxOption4!=nullptr)
    {
        delete chboxOption4;
    }
}

void QuestionPreview::closeEvent(QCloseEvent *event)
{
    Delete();
}




