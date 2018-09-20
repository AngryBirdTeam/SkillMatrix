#include "QuestionPreview.h"
#include "ui_QuestionPreview.h"

#include <QSqlQuery>
#include <QDebug>

QuestionPreview::QuestionPreview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionPreview)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Init();

    addWidgets();

    disableWidgets();

}

QuestionPreview::~QuestionPreview()
{
    delete ui;
}

void QuestionPreview :: Init()
{
    questionInfoPtr = nullptr;
    textAns = nullptr;
    rdbtnOption1 = nullptr;
    rdbtnOption2 = nullptr;
    rdbtnOption3 = nullptr;
    rdbtnOption4 = nullptr;

    chboxOption1 = nullptr;
    chboxOption2 = nullptr;
    chboxOption3 = nullptr;
    chboxOption4 = nullptr;
}

void QuestionPreview :: addWidgets()
{
    questionInfoPtr = new QLabel();

    rdbtnOption1 = new QRadioButton();
    rdbtnOption2 = new QRadioButton();
    rdbtnOption3 = new QRadioButton();
    rdbtnOption4 = new QRadioButton();

    chboxOption1 = new QCheckBox();
    chboxOption2 = new QCheckBox();
    chboxOption3 = new QCheckBox();
    chboxOption4 = new QCheckBox();

    textAns = new QTextEdit();

    ui->verticalLayout->addWidget(questionInfoPtr);

    ui->verticalLayout->addWidget(rdbtnOption1);
    ui->verticalLayout->addWidget(rdbtnOption2);
    ui->verticalLayout->addWidget(rdbtnOption3);
    ui->verticalLayout->addWidget(rdbtnOption4);

    ui->verticalLayout->addWidget(chboxOption1);
    ui->verticalLayout->addWidget(chboxOption2);
    ui->verticalLayout->addWidget(chboxOption3);
    ui->verticalLayout->addWidget(chboxOption4);

    ui->verticalLayout->addWidget(textAns);
}


void QuestionPreview::displayQuestion()
{
    questionInfoPtr->setText(questionInfo);
    questionInfoPtr->setVisible(true);

    switch(optionCount)
    {

    case 1:
        if(optionType == "Radio Button")
        {
            rdbtnOption1->setText(option1Info);
            rdbtnOption1->setVisible(true);

        }
        else if(optionType == "Check Box")
        {
            chboxOption1->setText(option1Info);
            chboxOption1->setVisible(true);

        }
        else
        {
            textAns->setVisible(true);
        }

        break;
    case 2:

        if(optionType == "Radio Button")
        {
            rdbtnOption1->setText(option1Info);
            rdbtnOption2->setText(option2Info);

            rdbtnOption1->setVisible(true);
            rdbtnOption2->setVisible(true);
        }
        else if(optionType == "Check Box")
        {
            chboxOption1->setText(option1Info);
            chboxOption2->setText(option2Info);

            chboxOption1->setVisible(true);
            chboxOption2->setVisible(true);
        }

            break;

    case 3:
        if(optionType == "Radio Button")
        {
            rdbtnOption1->setText(option1Info);
            rdbtnOption2->setText(option2Info);
            rdbtnOption3->setText(option3Info);

            rdbtnOption1->setVisible(true);
            rdbtnOption2->setVisible(true);
            rdbtnOption3->setVisible(true);
        }
        else if(optionType == "Check Box")
        {
            chboxOption1->setText(option1Info);
            chboxOption2->setText(option2Info);
            chboxOption3->setText(option3Info);

            chboxOption1->setVisible(true);
            chboxOption2->setVisible(true);
            chboxOption3->setVisible(true);
        }
        break;

    case 4:
        if(optionType == "Radio Button")
        {
            rdbtnOption1->setText(option1Info);
            rdbtnOption2->setText(option2Info);
            rdbtnOption3->setText(option3Info);
            rdbtnOption4->setText(option4Info);

            rdbtnOption1->setVisible(true);
            rdbtnOption2->setVisible(true);
            rdbtnOption3->setVisible(true);
            rdbtnOption4->setVisible(true);
        }
        else if(optionType == "Check Box")
        {
            chboxOption1->setText(option1Info);
            chboxOption2->setText(option2Info);
            chboxOption3->setText(option3Info);
            chboxOption4->setText(option4Info);

            chboxOption1->setVisible(true);
            chboxOption2->setVisible(true);
            chboxOption3->setVisible(true);
            chboxOption4->setVisible(true);
        }

        break;

    default:
        textAns->setVisible(true);
        break;
    }

    this->show();
}

void QuestionPreview::disableWidgets()
{
    
    questionInfoPtr->setVisible(false);

    rdbtnOption1->setVisible(false);
    rdbtnOption2->setVisible(false);
    rdbtnOption3->setVisible(false);
    rdbtnOption4->setVisible(false);

    chboxOption1->setVisible(false);
    chboxOption2->setVisible(false);
    chboxOption3->setVisible(false);
    chboxOption4->setVisible(false);

    textAns->setVisible(false);
    
}

void QuestionPreview::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    disableWidgets();
}




