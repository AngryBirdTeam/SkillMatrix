#include "DisplayQA.h"
#include "ui_DisplayQA.h"

#include <QSqlQuery>
#include <QDebug>

unsigned int DisplayQA::MAXOPTION_COUNT = 4;

DisplayQA::DisplayQA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayQA)
{
    ui->setupUi(this);

    Init();
    HideMenus();
    DisableMenus();

    //for Add Question
    connect(ui->pbtnAddQtn, SIGNAL(clicked()),this, SLOT(AddQuestionSlot()));

    //for Add Option and Weightage
    connect(ui->pbtnAddOptionAndWeightage, SIGNAL(clicked()), this, SLOT(AddOptionAndWeightageSlot()));

    //for save
    connect(ui->pbtnSaveQtn, SIGNAL(clicked()), this, SLOT(SaveQuestionDetails()));

    //for Question Info Update
    connect(ui->txteditQtn, SIGNAL(textChanged()), this, SLOT(UpdateQText()));

    //for line edit of option 1
    connect(ui->leditOpt1, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption1Info(const QString &)));
    connect(ui->leditOpt1Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption1Weightage(const QString &)));

    //for line edit of option 2
    connect(ui->leditOpt2, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption2Info(const QString &)));
    connect(ui->leditOpt2Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption2Weightage(const QString &)));

    //for line edit of option 3
    connect(ui->leditOpt3, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption3Info(const QString &)));
    connect(ui->leditOpt3Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption3Weightage(const QString &)));

    //for line edit of option 4
    connect(ui->leditOpt4, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption4Info(const QString &)));
    connect(ui->leditOpt4Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption4Weightage(const QString &)));

    //for combo box to select option type
    connect(ui->cBoxOptionType, SIGNAL(currentTextChanged(const QString &)), this, SLOT(UpdateOptionType(const QString &)));

    //for Text answer
    connect(ui->txteditAns, SIGNAL(textChanged()), this, SLOT(AddTextAnswerSlot()));
    connect(ui->leditWeightage, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateTxtWeightage(const QString &)));

    //for remove Option
    connect(ui->pbtnRemoveOpt, SIGNAL(clicked()), this, SLOT(RemoveOptionAndWeightageSlot()));

    //for clear
    connect(ui->pbtnClear, SIGNAL(clicked()), this, SLOT(ClearData()));

    //for preview
    connect(ui->pbtnPreview, SIGNAL(clicked()), this, SLOT(PreviewQuestion()));

    ui->leditOpt1Weight->setValidator(new QIntValidator(0, 100, this));
    ui->leditOpt2Weight->setValidator(new QIntValidator(0, 100, this));
    ui->leditOpt3Weight->setValidator(new QIntValidator(0, 100, this));
    ui->leditOpt4Weight->setValidator(new QIntValidator(0, 100, this));

    ui->leditWeightage->setValidator(new QIntValidator(0, 100, this));
}

DisplayQA::~DisplayQA()
{
    optionCount = 0;

    delete ui;
}

void DisplayQA::Init()
{
    previewQtnPtr = nullptr;

    //set the default option type
    optionType =  ui->cBoxOptionType->currentText();
    ui->leditOpt1Weight->setText("0");
    ui->leditOpt2Weight->setText("0");
    ui->leditOpt3Weight->setText("0");
    ui->leditOpt4Weight->setText("0");
    ui->leditWeightage->setText("0");

    previewQtnPtr = new QuestionPreview();
    displayInfoPtr = DisplayInfo::getInstance();

    QPixmap imgPixMap(":/Images/Images/Grow_Skills.png");
    ui->lblImage->setPixmap(imgPixMap);
}

void DisplayQA::HideMenus()
{
    ui->lblTxtQ->hide();
    ui->txteditQtn->hide();

    ui->lblOpt1->hide();
    ui->lblOpt1Weight->hide();
    ui->leditOpt1->hide();
    ui->leditOpt1Weight->hide();

    ui->lblOpt2->hide();
    ui->lblOpt2Weight->hide();
    ui->leditOpt2->hide();
    ui->leditOpt2Weight->hide();

    ui->lblOpt3->hide();
    ui->lblOpt3Weight->hide();
    ui->leditOpt3->hide();
    ui->leditOpt3Weight->hide();

    ui->lblOpt4->hide();
    ui->lblOpt4Weight->hide();
    ui->leditOpt4->hide();
    ui->leditOpt4Weight->hide();

    ui->lblWeighatge->hide();
    ui->leditWeightage->hide();

    ui->lblTxtAns->hide();
    ui->txteditAns->hide();

    ui->lblOptType->hide();

    ui->cBoxOptionType->hide();
    ui->pbtnAddOptionAndWeightage->hide();
    ui->pbtnRemoveOpt->hide();
    ui->pbtnSaveQtn->hide();
    ui->pbtnClear->hide();
    ui->pbtnPreview->hide();
}

void DisplayQA::ShowMenus()
{
    ui->lblTxtQ->show();
    ui->txteditQtn->show();
    ui->lblOptType->show();

    ui->cBoxOptionType->show();
    ui->pbtnAddOptionAndWeightage->show();
    ui->pbtnRemoveOpt->show();
    ui->pbtnSaveQtn->show();
    ui->pbtnClear->show();
    ui->pbtnPreview->show();
}

void DisplayQA::DisableMenus()
{
    ui->pbtnAddOptionAndWeightage->setEnabled(false);
    ui->pbtnRemoveOpt->setEnabled(false);
    ui->pbtnSaveQtn->setEnabled(false);
    ui->pbtnClear->setEnabled(false);
    ui->pbtnPreview->setEnabled(false);
}

void DisplayQA::AddQuestionSlot()
{
    ui->pbtnAddQtn->hide();
    ui->pbtnAddQtn->setEnabled(false);

    ui->lblImage->hide();

    ShowMenus();
}

void DisplayQA::AddOptionAndWeightageSlot()
{
    if( !ui->pbtnRemoveOpt->isEnabled() )
    {
        ui->pbtnRemoveOpt->setEnabled(true);
    }

    if( ui->cBoxOptionType->isEnabled() )
    {
        //disabled so that option type cannot be changed until text box added is removed
        ui->cBoxOptionType->setEnabled(false);
    }

    if(optionType == "Text Box")
    {
        if( !ui->pbtnSaveQtn->isEnabled())
        {
           ui->pbtnSaveQtn->setEnabled(true);
        }
		
        ui->lblTxtAns->show();
        ui->txteditAns->show();
        ui->lblWeighatge->show();
        ui->leditWeightage->show();

        qDebug()<<"Option Count "<<optionCount;

        if( !ui->pbtnPreview->isEnabled() )
        {
            ui->pbtnPreview->setEnabled(true);
        }
    }
    else
    {
        optionCount++;

        if(optionCount <= MAXOPTION_COUNT)
        {
            if( !ui->pbtnPreview->isEnabled() )
            {
                ui->pbtnPreview->setEnabled(true);
            }

            switch(optionCount)
            {
            case 1:
                ui->lblOpt1->show();
                ui->leditOpt1->show();
                ui->lblOpt1Weight->show();
                ui->leditOpt1Weight->show();
                break;

            case 2:
                if( option1Info.isEmpty() )
                {
                    displayInfoPtr->DisplayMessage("Option information cannot be Empty", DisplayInfo::MessageType::Error);
                    optionCount--;
                }
                else
                {
                    if( !ui->pbtnSaveQtn->isEnabled())
                    {
                       ui->pbtnSaveQtn->setEnabled(true);
                    }
					
                    ui->lblOpt2->show();
                    ui->leditOpt2->show();
                    ui->lblOpt2Weight->show();
                    ui->leditOpt2Weight->show();
                }

                break;

            case 3:
                if( option1Info.isEmpty() || option2Info.isEmpty() )
                {
                    displayInfoPtr->DisplayMessage("Option information cannot be Empty", DisplayInfo::MessageType::Error);
                    optionCount--;
                }
                else
                {
                    ui->lblOpt3->show();
                    ui->leditOpt3->show();
                    ui->lblOpt3Weight->show();
                    ui->leditOpt3Weight->show();
                }

                break;

            case 4:
                if( option1Info.isEmpty() || option2Info.isEmpty() || option3Info.isEmpty() )
                {
                    displayInfoPtr->DisplayMessage("Option information cannot be Empty", DisplayInfo::MessageType::Error);
                    optionCount--;
                }
                else
                {
                    ui->lblOpt4->show();
                    ui->leditOpt4->show();
                    ui->lblOpt4Weight->show();
                    ui->leditOpt4Weight->show();
                }

                break;

            default:
                displayInfoPtr->DisplayMessage("Invalid Option Count", DisplayInfo::MessageType::Error);
            }
        }
        else
        {
            optionCount--;
            displayInfoPtr->DisplayMessage("A question can have maximum of " + QString::number(MAXOPTION_COUNT) + " options only",            DisplayInfo::MessageType::Error);
        }
    }
}

void DisplayQA::RemoveOptionAndWeightageSlot()
{
    qDebug()<<"Inside slot Remove option "<<optionCount;

    if(optionType == "Text Box")
    {
        ui->txteditAns->clear();
        ui->leditWeightage->setText("0");

        ui->lblTxtAns->hide();
        ui->txteditAns->hide();
        ui->lblWeighatge->hide();
        ui->leditWeightage->hide();

        ui->pbtnRemoveOpt->setEnabled(false);
        ui->pbtnPreview->setEnabled(false);

        //enabled so that option type can be changed as text box added is removed
        ui->cBoxOptionType->setEnabled(true);
    }
    else
    {
        switch (optionCount)
        {
        case 1:

            ui->leditOpt1->clear();
            ui->leditOpt1Weight->setText("0");

            ui->lblOpt1->hide();
            ui->leditOpt1->hide();
            ui->lblOpt1Weight->hide();
            ui->leditOpt1Weight->hide();

            ui->pbtnRemoveOpt->setEnabled(false);
            ui->pbtnPreview->setEnabled(false);

            ui->cBoxOptionType->setEnabled(true);

            optionCount--;

            break;

        case 2:

            ui->leditOpt2->clear();
            ui->leditOpt2Weight->setText("0");

            ui->lblOpt2->hide();
            ui->leditOpt2->hide();
            ui->lblOpt2Weight->hide();
            ui->leditOpt2Weight->hide();
            ui->pbtnSaveQtn->setEnabled(false);
            optionCount--;

            break;

        case 3:

            ui->leditOpt3->clear();
            ui->leditOpt3Weight->setText("0");

            ui->lblOpt3->hide();
            ui->leditOpt3->hide();
            ui->lblOpt3Weight->hide();
            ui->leditOpt3Weight->hide();

            optionCount--;

            break;

        case 4:

            ui->leditOpt4->clear();
            ui->leditOpt4Weight->setText("0");

            ui->lblOpt4->hide();
            ui->leditOpt4->hide();
            ui->lblOpt4Weight->hide();
            ui->leditOpt4Weight->hide();

            optionCount--;

            break;

        default:
            displayInfoPtr->DisplayMessage("Invalid Option Count", DisplayInfo::MessageType::Error);
        }
    }
}

void DisplayQA::SaveQuestionDetails()
{
    QSqlQuery query;
    QString strQuery;

    if(validateQuestionDetails())
    {

        strQuery = "INSERT INTO tbl_question_and_answers";

        if( optionType == "Text Box")
        {
            strQuery += "(fld_question,fld_answer_type,fld_text_answer,fld_text_answer_weight,fld_skill_id)";
                        strQuery += " VALUES( '";
                        strQuery += questionInfo;
                        strQuery += "', '";
                        strQuery += optionType;
                        strQuery += "', '";
                        strQuery += textAnswer;
                        strQuery += "', '";
                        strQuery += QString::number(textAnswerWeight);
                        strQuery += "', '";
                        strQuery += QString::number(GetSkillId());
                        strQuery += "')";
        }
        else
        {
            switch (optionCount)
            {

            case 2:
                strQuery += "(fld_question,fld_answer_type,fld_option1,fld_option1_weight,fld_option2,fld_option2_weight,fld_skill_id)";
                strQuery += " VALUES( '";
                strQuery += questionInfo;
                strQuery += "', '";
                strQuery += optionType;
                strQuery += "', '";
                strQuery += option1Info;
                strQuery += "', '";
                strQuery += QString::number(option1Weight);
                strQuery += "', '";
                strQuery += option2Info;
                strQuery += "', '";
                strQuery += QString::number(option2Weight);
                strQuery += "', '";
                strQuery += QString::number(GetSkillId());
                strQuery += "')";

                break;

            case 3:strQuery += "(fld_question,fld_answer_type,fld_option1,fld_option1_weight,fld_option2,fld_option2_weight,";
                strQuery += "fld_option3,fld_option3_weight,fld_skill_id)";
                strQuery += " VALUES( '";
                strQuery += questionInfo;
                strQuery += "', '";
                strQuery += optionType;
                strQuery += "', '";
                strQuery += option1Info;
                strQuery += "', '";
                strQuery += QString::number(option1Weight);
                strQuery += "', '";
                strQuery += option2Info;
                strQuery += "', '";
                strQuery += QString::number(option2Weight);
                strQuery += "', '";
                strQuery += option3Info;
                strQuery += "', '";
                strQuery += QString::number(option3Weight);
                strQuery += "', '";
                strQuery += QString::number(GetSkillId());
                strQuery += "')";
                break;

            case 4:
                strQuery += "(fld_question,fld_answer_type,fld_option1,fld_option1_weight,fld_option2,fld_option2_weight,";
                strQuery += "fld_option3,fld_option3_weight,fld_option4,fld_option4_weight,fld_skill_id)";
                strQuery += " VALUES( '";
                strQuery += questionInfo;
                strQuery += "', '";
                strQuery += optionType;
                strQuery += "', '";
                strQuery += option1Info;
                strQuery += "', '";
                strQuery += QString::number(option1Weight);
                strQuery += "', '";
                strQuery += option2Info;
                strQuery += "', '";
                strQuery += QString::number(option2Weight);
                strQuery += "', '";
                strQuery += option3Info;
                strQuery += "', '";
                strQuery += QString::number(option3Weight);
                strQuery += "', '";
                strQuery += option4Info;
                strQuery += "', '";
                strQuery += QString::number(option4Weight);
                strQuery += "', '";
                strQuery += QString::number(GetSkillId());
                strQuery += "')";
                break;

            default:
                break;
            }
        }

        if(query.exec(strQuery))
        {
            ui->pbtnSaveQtn->setEnabled(false);
            displayInfoPtr->DisplayMessage("Question added to the database successfuly", DisplayInfo::MessageType::Normal);
            qDebug()<<"Question added successfully";
            ClearData();
        }
        else
        {
            displayInfoPtr->DisplayMessage("Saving to the Database failed!" , DisplayInfo::MessageType::Error);
            qDebug()<<"ERROR = "<<query.lastQuery();
            ErrorMsg.clear();
        }
    }
    else
    {
        displayInfoPtr->DisplayMessage(ErrorMsg, DisplayInfo::MessageType::Error);
        ErrorMsg.clear();
    }
}

void DisplayQA::ClearData()
{
    ui->txteditQtn->clear();

    ClearOptionsInfo();

    ui->pbtnAddQtn->show();
    ui->pbtnAddQtn->setEnabled(true);

    QPixmap imgPixMap(":/Images/Images/Grow_Skills.png");
    ui->lblImage->setPixmap(imgPixMap);
    ui->lblImage->show();

    ui->cBoxOptionType->setEnabled(true);

    SelectedSkillName.clear();

    HideMenus();
    DisableMenus();
}

void DisplayQA::ClearOptionsInfo()
{
    ui->txteditAns->clear();

    ui->leditWeightage->setText("0");

    ui->leditOpt1->clear();
    ui->leditOpt1Weight->setText("0");

    ui->leditOpt2->clear();
    ui->leditOpt2Weight->setText("0");

    ui->leditOpt3->clear();
    ui->leditOpt3Weight->setText("0");

    ui->leditOpt4->clear();
    ui->leditOpt4Weight->setText("0");

}

void DisplayQA::UpdateQText()
{
    questionInfo = ui->txteditQtn->toPlainText();

    if( questionInfo.isEmpty() )
    {
        DisableMenus();
        ClearOptionsInfo();

        if(optionType == "Text Box")
        {
            RemoveOptionAndWeightageSlot();
        }
        else
        {
            while(optionCount)
            {
                RemoveOptionAndWeightageSlot();
            }
        }

        return;
    }

    if( !ui->pbtnAddOptionAndWeightage->isEnabled() )
    {
        ui->pbtnAddOptionAndWeightage->setEnabled(true);
    }

    if( !ui->pbtnClear->isEnabled() )
    {
        ui->pbtnClear->setEnabled(true);
    }

    qDebug()<<"Question is: "<<questionInfo;
}

void DisplayQA::UpdateOptionType(const QString &optType)
{
    optionType = optType;
    qDebug()<<"Option type "<<optionType;
}

void DisplayQA::AddTextAnswerSlot()
{
    textAnswer = ui->txteditAns->toPlainText();
    qDebug()<<"Text Box Answer content "<<textAnswer;
}

void::DisplayQA::UpdateTxtWeightage(const QString &txtWeightage)
{
    textAnswerWeight = txtWeightage.toUInt();
    qDebug()<<"Text Answer weightage:"<<textAnswerWeight;

}

void DisplayQA::validateText(QString text)
{
    if(text.isEmpty())
    {
        displayInfoPtr->DisplayMessage("Empty Text", DisplayInfo::MessageType::Error);
    }
}
void DisplayQA::UpdateOption1Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 1";
    option1Info = newText;
}

void DisplayQA::UpdateOption1Weightage(const QString &newOpt1Weight)
{
    qDebug()<<"Inside slot Update option 1 Weight";
    option1Weight = newOpt1Weight.toUInt();
}

void DisplayQA::UpdateOption2Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 2";
    option2Info = newText;
}

void DisplayQA::UpdateOption2Weightage(const QString &newOpt2Weight)
{
    qDebug()<<"Inside slot Update option 2 Weight";
    option2Weight = newOpt2Weight.toUInt();

}

void DisplayQA::UpdateOption3Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 3";
    option3Info = newText;

}

void DisplayQA::UpdateOption3Weightage(const QString &newOpt3Weight)
{
    qDebug()<<"Inside slot Update option 1 Weight";
    option3Weight = newOpt3Weight.toUInt();
}

void DisplayQA::UpdateOption4Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 4";
    option4Info = newText;

}

void DisplayQA::UpdateOption4Weightage(const QString &newOpt4Weight)
{
    qDebug()<<"Inside slot Update option 4 Weight";
    option4Weight = newOpt4Weight.toUInt();
}

bool DisplayQA::validateOptionInfo()
{
    bool validOption = true;

    if( optionType == "Text Box")
    {
        if(textAnswer.isEmpty())
        {
            ErrorMsg += "\n Text Answer is empty.";
            validOption = false;
        }
    }
    else
    {
        switch(optionCount)
        {

        case 2:if(option1Info.isEmpty() || option2Info.isEmpty())
            {
                ErrorMsg += "\n Option1/Option2 data is empty.";
                validOption = false;
                break;
            }
            if(option1Info == option2Info)
            {
                ErrorMsg += "\n Two options are same.";
                validOption = false;
            }

            break;
        case 3: if(option1Info.isEmpty() || option2Info.isEmpty() || option3Info.isEmpty())
            {
                ErrorMsg += "\n Option1/Option2/Option3 data is empty.";
                validOption = false;
                break;
            }
            if(option1Info == option2Info || option1Info == option3Info || option2Info == option3Info)
            {
                ErrorMsg += "\n Two or more options are same.";
                validOption = false;
            }

            break;
        case 4:  if(option1Info.isEmpty() || option2Info.isEmpty() || option3Info.isEmpty() || option4Info.isEmpty())
            {
                ErrorMsg += "\n Option1/Option2/Option3/Option4 data is empty.";
                validOption = false;
                break;
            }
            if(option1Info == option2Info || option1Info == option3Info || option1Info == option4Info
                   || option2Info == option3Info || option2Info == option4Info || option3Info == option4Info)
            {
                ErrorMsg += "\n Two or more options are same.";
                validOption = false;
            }
            break;
        default:
            break;

        }
    }

    return validOption;
}

bool DisplayQA :: validateQuestionDetails()
{
    bool validQuestion = true;
    if(!(validateOptionInfo()))
    {
        validQuestion = false;
    }

    return validQuestion;
}

void DisplayQA::UpdateCurrentSkillName(QString SkillName)
{
    SelectedSkillName = SkillName;

    qDebug() << "Current Skill Name is " << SelectedSkillName;

}

unsigned int DisplayQA::GetSkillId()
{
    QSqlQuery query;
    QString strQuery;
    unsigned int skillId = 0;

    strQuery =  "SELECT tbl_skill_name.fld_skill_id FROM tbl_skill_name WHERE fld_skillname= '";
    strQuery += SelectedSkillName +"'";

    if(query.exec(strQuery))
    {
        query.next();
        skillId = query.value(0).toUInt();
    }
    return skillId;
}

void DisplayQA :: PreviewQuestion()
{

    if(!previewQtnPtr->isActiveWindow())
    {
        previewQtnPtr->activateWindow();
    }
    previewQtnPtr->questionInfo = questionInfo;
    qDebug()<<"Question: "<<questionInfo;
    previewQtnPtr->option1Info = option1Info;
    qDebug()<<"option1Info: "<<option1Info;
    previewQtnPtr->option2Info = option2Info;
    previewQtnPtr->option3Info = option3Info;
    previewQtnPtr->option4Info = option4Info;
    previewQtnPtr->optionType = optionType;
    previewQtnPtr->optionCount = optionCount;

    previewQtnPtr->displayQuestion();


}
