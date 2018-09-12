#include "DisplayAddSkills.h"
#include "ui_DisplayAddSkills.h"

#include <QSqlQuery>
#include <QDebug>

DisplayAddSkills::DisplayAddSkills(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayAddSkills)
{
    ui->setupUi(this);
    HideTextEditBoxes();
    DisableOptionMenus();

    previewQtnPtr = new QuestionPreview();

    //set the default option type
    optionType =  ui->cBoxOptionType->currentText();
    ui->leditOpt1Weight->setText("0");
    ui->leditOpt2Weight->setText("0");
    ui->leditOpt3Weight->setText("0");
    ui->leditOpt4Weight->setText("0");
    ui->leditWeightage->setText("0");

    //for Add Question
    connect(ui->pbtnAddQtn, SIGNAL(clicked()),this, SLOT(AddQuestionSlot()));

    //for Add Option and Weightage
    connect(ui->pbtnAddOptionAndWeightage, SIGNAL(clicked()), this, SLOT(AddOptionAndWeightageSlot()));

    //for save
    connect(ui->pbtnSaveQtn, SIGNAL(clicked()), this, SLOT(SaveQuestionDetails()));

    //for Question Info Update
    connect(ui->txteditQtn, SIGNAL(textChanged()), this, SLOT(UpdateQText()));

    //        //for line edit of option 1
    //    connect(ui->leditOpt1, SIGNAL(textEdited(const QString &)), mapper, SLOT(map()));
    //    mapper->setMapping(ui->leditOpt1, 1);
    //    connect(ui->leditOpt1Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption1Weightage(const QString &, QString)));

    //    //for line edit of option 2
    //    connect(ui->leditOpt2, SIGNAL(textEdited(const QString &)), mapper, SLOT(map()));
    //    mapper->setMapping(ui->leditOpt2, 2);
    //    connect(ui->leditOpt2Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption2Weightage(const QString &)));

    //    //for line edit of option 3
    //    connect(ui->leditOpt3, SIGNAL(textEdited(const QString &)), mapper, SLOT(map()));
    //    mapper->setMapping(ui->leditOpt3, 3);
    //    connect(ui->leditOpt3Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption3Weightage(const QString &)));

    //    //for line edit of option 4
    //    connect(ui->leditOpt4, SIGNAL(textEdited(const QString &)), mapper, SLOT(map()));
    //    mapper->setMapping(ui->leditOpt4, 4);

    //    connect(ui->leditOpt4Weight, SIGNAL(textEdited(const QString &)), this, SLOT(UpdateOption4Weightage(const QString &)));

    //    //Signal mapping
    //    connect(mapper, SIGNAL(mapped(const QString &, int)), this, SLOT(UpdateOption1Info(const QString &,int)));



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
DisplayAddSkills::~DisplayAddSkills()
{
    delete ui;
}

void DisplayAddSkills::HideTextEditBoxes()
{
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
}

void DisplayAddSkills::DisableOptionMenus()
{
    ui->cBoxOptionType->hide();
    ui->pbtnAddOptionAndWeightage->hide();
    ui->pbtnRemoveOpt->hide();
    ui->pbtnSaveQtn->hide();
    ui->pbtnClear->hide();
    ui->pbtnPreview->hide();
}
void DisplayAddSkills::EnableOptionMenus()
{
    ui->lblOptType->show();
    ui->cBoxOptionType->show();
    ui->pbtnAddOptionAndWeightage->show();
    ui->pbtnSaveQtn->show();
    ui->pbtnSaveQtn->setEnabled(true);
    ui->pbtnClear->show();
    ui->pbtnPreview->show();
    ui->pbtnRemoveOpt->show();

}

void DisplayAddSkills::AddQuestionSlot()
{

    ui->txteditQtn->show();
    EnableOptionMenus();

}

void DisplayAddSkills::AddOptionAndWeightageSlot()
{

    if(!questionInfo.isEmpty())
    {
        ui->cBoxOptionType->setEnabled(false);
        if(optionType == "Text Box")
        {
            ui->lblTxtAns->show();
            ui->txteditAns->show();
            ui->lblWeighatge->show();
            ui->leditWeightage->show();
            qDebug()<<"Option Count "<<optionCount;
        }
        else
        {
            optionCount++;

            qDebug()<< "Question : "<<questionInfo;

            if(optionCount <= maxOptions)
            {
                switch (optionCount)
                {

                case 1: ui->lblOpt1->show();
                    ui->leditOpt1->show();
                    ui->lblOpt1Weight->show();
                    ui->leditOpt1Weight->show();
                    break;

                case 2: if(!option1Info.isEmpty())
                    {
                        qDebug()<<option1Info<<" "<<option1Weight;
                        ui->lblOpt2->show();
                        ui->leditOpt2->show();
                        ui->lblOpt2Weight->show();
                        ui->leditOpt2Weight->show();
                    }
                    else
                    {
                        qDebug()<<option1Info<<" "<<option1Weight;
                        PopUpMsg.setText("Option 1 information is not entered");
                        PopUpMsg.exec();
                        optionCount--;
                    }
                    break;

                case 3: if(!option2Info.isEmpty())
                    {
                        ui->lblOpt3->show();
                        ui->leditOpt3->show();
                        ui->lblOpt3Weight->show();
                        ui->leditOpt3Weight->show();
                    }
                    else
                    {
                        qDebug()<<option2Info<<" "<<option2Weight;
                        PopUpMsg.setText("Option 2 information is not entered");
                        PopUpMsg.exec();
                        optionCount--;
                    }

                    break;

                case 4: if(!option3Info.isEmpty())
                    {
                        ui->lblOpt4->show();
                        ui->leditOpt4->show();
                        ui->lblOpt4Weight->show();
                        ui->leditOpt4Weight->show();
                    }
                    else
                    {
                        qDebug()<<option3Info<<" "<<option3Weight;
                        PopUpMsg.setText("Option 3 information is not entered");
                        PopUpMsg.exec();
                        optionCount--;
                    }

                    break;
                }
            }
            else
            {
                optionCount = maxOptions;
                PopUpMsg.setText("A question can have maximum of " + QString::number(maxOptions));
                PopUpMsg.exec();
            }
        }

    }
    else
    {
        PopUpMsg.setText("Question is empty");
        PopUpMsg.exec();
    }

}

void DisplayAddSkills::RemoveOptionAndWeightageSlot()
{
    qDebug()<<"Inside slot Remove option "<<optionCount;
    switch (optionCount) {
    case 0: ui->lblTxtAns->hide();
        ui->txteditAns->clear();
        ui->txteditAns->hide();
        ui->lblWeighatge->hide();
        ui->leditWeightage->hide();
        ui->leditWeightage->setText("0");
        textAnswer.clear();
        ui->cBoxOptionType->setEnabled(true);
        break;

    case 1: ui->lblOpt1->hide();
        ui->leditOpt1->hide();
        ui->leditOpt1->clear();
        ui->lblOpt1Weight->hide();
        ui->leditOpt1Weight->hide();
        ui->leditOpt1Weight->setText("0");
        optionCount--;
        ui->cBoxOptionType->setEnabled(true);
        break;

    case 2: ui->lblOpt2->hide();
        ui->leditOpt2->hide();
        ui->leditOpt2->clear();
        ui->lblOpt2Weight->hide();
        ui->leditOpt2Weight->hide();
        ui->leditOpt2Weight->setText("0");
        optionCount--;
        break;
    case 3: ui->lblOpt3->hide();
        ui->leditOpt3->hide();
        ui->leditOpt3->clear();
        ui->lblOpt3Weight->hide();
        ui->leditOpt3Weight->hide();
        ui->leditOpt3Weight->setText("0");
        optionCount--;
        break;


    case 4: ui->lblOpt4->hide();
        ui->leditOpt4->hide();
        ui->leditOpt4->clear();
        ui->lblOpt4Weight->hide();
        ui->leditOpt4Weight->hide();
        ui->leditOpt4Weight->setText("0");
        optionCount--;

        break;

    }
}


void DisplayAddSkills::SaveQuestionDetails()
{
    QSqlQuery query;
    QString strQuery;

    if(validateQuestionDetails())
    {

        strQuery = "INSERT INTO tbl_question_and_answers";

        switch (optionCount) {
        case 0: strQuery += "(fld_question,fld_answer_type,fld_text_answer,fld_text_answer_weight,fld_skill_id)";
            strQuery += " VALUES( '";
            strQuery += questionInfo;
            strQuery += "', '";
            strQuery += optionType;
            strQuery += "', '";
            strQuery += textAnswer;
            strQuery += "', '";
            strQuery += QString::number(textAnswerWeight);
            strQuery += "', '";
            strQuery += QString::number(skillId);
            strQuery += "')";
            break;

        case 1: strQuery += "(fld_question,fld_answer_type,fld_option1,fld_option1_weight,fld_skill_id)";
            strQuery += " VALUES( '";
            strQuery += questionInfo;
            strQuery += "', '";
            strQuery += optionType;
            strQuery += "', '";
            strQuery += option1Info;
            strQuery += "', '";
            strQuery += QString::number(option1Weight);
            strQuery += "', '";
            strQuery += QString::number(skillId);
            strQuery += "')";
            break;

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
            strQuery += QString::number(skillId);
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
            strQuery += QString::number(skillId);
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
            strQuery += QString::number(skillId);
            strQuery += "')";
            break;
        default:
            break;
        }


        if(query.exec(strQuery))
        {
            saveFlag = true;
            ui->pbtnSaveQtn->setEnabled(false);
            PopUpMsg.setText("Question added to the database successfuly");
            PopUpMsg.exec();
            qDebug()<<"Question added successfully";
        }
        else
        {
            qDebug()<<"ERROR = "<<query.lastQuery();
        }
    }
    else
    {
        PopUpMsg.setText(ErrorMsg);
        PopUpMsg.exec();
        ErrorMsg.clear();
    }

}

void DisplayAddSkills::ClearData()
{
    //    if(!saveFlag)
    //    {
    //        PopUpMsg.setText("Question Not saved.");
    //        PopUpMsg.exec();
    //    }
    //    else
    //{
    clearFlag = true;
    ui->txteditQtn->clear();
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
    HideTextEditBoxes();
    DisableOptionMenus();

    SelectedSkillName.clear();
    //}

}

void DisplayAddSkills::UpdateQText()
{
    questionInfo = ui->txteditQtn->toPlainText();
    qDebug()<<"Question is: "<<questionInfo;
}

void DisplayAddSkills::UpdateOptionType(const QString &optType)
{
    optionType = optType;
    qDebug()<<"Option type "<<optionType;
}

void DisplayAddSkills::AddTextAnswerSlot()
{
    textAnswer = ui->txteditAns->toPlainText();
    qDebug()<<"Text Box Answer content "<<textAnswer;
}

void::DisplayAddSkills::UpdateTxtWeightage(const QString &txtWeightage)
{
    textAnswerWeight = txtWeightage.toUInt();
    qDebug()<<"Text Answer weightage:"<<textAnswerWeight;

}

void DisplayAddSkills::UpdateOptionInfo(const QString &newText, int mapId)
{
    qDebug()<<"Inside slot update";
    switch (mapId) {
    case 1:
        option1Info = newText;
        validateText(option1Info);
        break;
    case 2:
        option2Info = newText;
        validateText(option2Info);
        break;
    case 3:
        option3Info = newText;
        validateText(option3Info);
        break;
    case 4:
        option4Info = newText;
        validateText(option4Info);
        break;
    default:
        break;
    }

}

void DisplayAddSkills::validateText(QString text)
{
    if(text.isEmpty())
    {
        PopUpMsg.setText("Empty Text");
        PopUpMsg.exec();
    }
}
void DisplayAddSkills::UpdateOption1Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 1";
    option1Info = newText;
}

void DisplayAddSkills::UpdateOption1Weightage(const QString &newOpt1Weight)
{
    qDebug()<<"Inside slot Update option 1 Weight";
    option1Weight = newOpt1Weight.toUInt();
}

void DisplayAddSkills::UpdateOption2Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 2";
    option2Info = newText;
}

void DisplayAddSkills::UpdateOption2Weightage(const QString &newOpt2Weight)
{
    qDebug()<<"Inside slot Update option 2 Weight";
    option2Weight = newOpt2Weight.toUInt();

}

void DisplayAddSkills::UpdateOption3Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 3";
    option3Info = newText;

}

void DisplayAddSkills::UpdateOption3Weightage(const QString &newOpt3Weight)
{
    qDebug()<<"Inside slot Update option 1 Weight";
    option3Weight = newOpt3Weight.toUInt();
}

void DisplayAddSkills::UpdateOption4Info(const QString &newText)
{
    qDebug()<<"Inside slot Update option 4";
    option4Info = newText;

}

void DisplayAddSkills::UpdateOption4Weightage(const QString &newOpt4Weight)
{
    qDebug()<<"Inside slot Update option 4 Weight";
    option4Weight = newOpt4Weight.toUInt();
}

bool DisplayAddSkills :: validateOptionWeightage()
{
    unsigned int totalWeight = 0;
    bool validWeights = true;
    switch(optionCount)
    {
    case 2: totalWeight = option1Weight + option2Weight;
        if(totalWeight!=100)
        {
            ErrorMsg += "\n Total Option Weightage of 2 options is not 100";
            validWeights = false;
        }
        break;
    case 3: totalWeight = option1Weight + option2Weight + option3Weight;
        if(totalWeight!=100)
        {
            ErrorMsg +="\n Total Option Weightage of 3 options is not 100";
            validWeights = false;
        }
        break;
    case 4: totalWeight = option1Weight + option2Weight + option3Weight + option4Weight;
        if(totalWeight!=100)
        {
            ErrorMsg +="\n Total Option Weightage of 3 options is not 100";
            validWeights = false;
        }
        break;
    }
    return validWeights;
}

bool DisplayAddSkills:: validateOptionInfo()
{
    bool validOption = true;
    switch(optionCount)
    {
    case 0: if(textAnswer.isEmpty())
        {
            ErrorMsg += "\n Text Answer is empty.";
            validOption = false;
        }
        break;
    case 1: if(option1Info.isEmpty())
        {
            ErrorMsg += "\n Option 1 data is empty.";
            validOption =false;
        }
        break;
    case 2: if(option1Info == option2Info)
        {
            ErrorMsg += "\n Two options are same.";
            validOption = false;
        }
        if(option1Info.isEmpty() || option2Info.isEmpty())
        {
            ErrorMsg += "\n Option1/Option2 data is empty.";
            validOption = false;
        }
        break;
    case 3: if(option1Info == option2Info || option1Info == option3Info || option2Info == option3Info)
        {
            ErrorMsg += "\n Two or more options are same.";
            validOption = false;
        }
        if(option1Info.isEmpty() || option2Info.isEmpty() || option3Info.isEmpty())
        {
            ErrorMsg += "\n Option1/Option2/Option3 data is empty.";
            validOption = false;
        }
        break;
    case 4: if(option1Info == option2Info || option1Info == option3Info || option1Info == option4Info
               || option2Info == option3Info || option2Info == option4Info || option3Info == option4Info)
        {
            ErrorMsg += "\n Two or more options are same.";
            validOption = false;
        }
        if(option1Info.isEmpty() || option2Info.isEmpty() || option3Info.isEmpty() || option4Info.isEmpty())
        {
            ErrorMsg += "\n Option1/Option2/Option3/Option4 data is empty.";
            validOption = false;
        }
        break;


    }
    return validOption;
}

bool DisplayAddSkills :: validateOptionCount()
{
    bool validOptionCount = true;
    if (optionType == "Radio Button" || optionType == "Check Box")
    {
        if(optionCount < 2)
        {

            ErrorMsg += "\n Minimum two options should be entered for MCQs.";
            validOptionCount = false;
        }
    }
    return validOptionCount;
}

bool DisplayAddSkills :: validateQuestionDetails()
{
    bool validQuestion = true;
    if(questionInfo.isEmpty())
    {
        ErrorMsg += "\n Question is empty.";
        validQuestion = false;
    }
    if(!(validateOptionCount() && validateOptionInfo() && validateOptionWeightage()))
    {
        validQuestion = false;
    }

    return validQuestion;
}

void DisplayAddSkills::UpdateCurrentSkillName(QString SkillName)
{
    SelectedSkillName = SkillName;

    qDebug() << "Current Skill Name is " << SelectedSkillName;
    GetSkillId();

}

void DisplayAddSkills :: GetSkillId()
{
    QSqlQuery query;
    QString strQuery;


    strQuery =  "SELECT tbl_skill_name.fld_skill_id FROM tbl_skill_name WHERE fld_skillname= '";
    strQuery += SelectedSkillName +"'";

    if(query.exec(strQuery))
    {
       query.next();
        skillId = query.value(0).toUInt();
    }
}

void DisplayAddSkills :: PreviewQuestion()
{

    previewQtnPtr->questionInfo = questionInfo;
    previewQtnPtr->option1Info = option1Info;
    previewQtnPtr->option2Info = option2Info;
    previewQtnPtr->option3Info = option3Info;
    previewQtnPtr->option4Info = option4Info;
    previewQtnPtr->optionType = optionType;
    previewQtnPtr->optionCount = optionCount;

    previewQtnPtr->displayQuestion();


}
