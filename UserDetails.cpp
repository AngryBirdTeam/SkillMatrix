#include "UserDetails.h"
#include "ui_UserDetails.h"
#include "QDesktopWidget"

UserDetails::UserDetails(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::UserDetails)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->lst_Taskassigned->setColumnCount(1);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    ui->chkChangePwd->setStyleSheet("QCheckBox::indicator { subcontrol-position: center }");

    ui->lb_ExistingPwd->hide();
    ui->editOldPwd ->hide();
    ui->lbNewPwd->hide();
    ui->editNewPwd ->hide();
    ui->lbConfirmPwd->hide();
    ui->editConfirmPwd->hide();
    ui->pbSavePassword->hide();

    // for change password checkbox
    connect(ui->chkChangePwd, SIGNAL(toggled(bool)), SLOT(SlotChangePassword(bool)));

    //for save
    connect(ui->pbSavePassword, SIGNAL(clicked()), SLOT(Save()));

    //for close
    connect(ui->pbCancelPassword, SIGNAL(clicked()), SLOT(CloseWindow()));
}

void UserDetails::slotUpdateUserDetails(QString UserName)
{
    ui->lst_Taskassigned->clear();
    ui->lst_Taskassigned->setColumnWidth(0, 300);
    ui->lst_Taskassigned->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->lst_Taskassigned->setHorizontalHeaderLabels(QString("Tasks").split(","));

//    QString taskAssigned;
//    int rowCount = 0;

    QSqlQuery EventQuery;
    QString strQuery = "select a.fld_user_id, a.fld_username, b.fld_usertype";
    strQuery += " FROM  tbl_user a, tbl_user_type b";
    strQuery += " WHERE a.fld_usertype_id = b.fld_usertype_id";
    strQuery += " AND fld_username = '";
    strQuery += UserName;
    strQuery += "'";

    if(!EventQuery.exec(strQuery))
    {
        qDebug()<<"ERROR"<<EventQuery.lastQuery();
        return;
    }

    qDebug() << "query on user details update: " << strQuery;

    while(EventQuery.next())
    {
        ui->lb_Username->setText(EventQuery.value(1).toString());
        ui->lb_Usertype->setText(EventQuery.value(2).toString());
        break;
    }

//    if("None" != taskAssigned)
//    {
//        strQuery = "select * from tbl_usertask";

//        if(!EventQuery.exec(strQuery))
//            qDebug()<<"ERROR"<<EventQuery.lastQuery();

//        if("All" == taskAssigned)
//        {
//            while(EventQuery.next())
//            {
//                ui->lst_Taskactivated->setRowCount(rowCount+1);
//                QTableWidgetItem *item = new QTableWidgetItem(EventQuery.value(1).toString());
//                item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
//                ui->lst_Taskactivated->setItem(rowCount++,0, item);
//            }
//        }
//        else
//        {
//            QStringList taskID = taskAssigned.split( "," );

//            while(EventQuery.next())
//            {
//                bool found = false;
//                for(int i = 0; i < taskID.count(); i++)
//                {
//                    if(EventQuery.value(0) == taskID[i])
//                    {
//                        found = true;
//                        i = taskID.count();
//                    }
//                }

//                if(true == found)
//                {
//                    ui->lst_Taskactivated->setRowCount(rowCount+1);
//                    QTableWidgetItem *item = new QTableWidgetItem(EventQuery.value(1).toString());
//                    item->setFlags(item->flags() &  ~Qt::ItemIsEditable);
//                    ui->lst_Taskactivated->setItem(rowCount++,0, item);
//                }
//            }
//        }
//    }
}

void UserDetails::UpdateUserDetails()
{
    ui->chkChangePwd->setChecked(false);
}

void UserDetails::SlotChangePassword(bool state)
{
    ui->editOldPwd->setText("");
    ui->editNewPwd->setText("");
    ui->editConfirmPwd->setText("");
    if(state == true)
    {
        ui->lb_ExistingPwd->show();
        ui->editOldPwd ->show();
        ui->lbNewPwd->show();
        ui->editNewPwd ->show();
        ui->lbConfirmPwd->show();
        ui->editConfirmPwd->show();
        ui->pbSavePassword->show();
    }
    else
    {
        ui->lb_ExistingPwd->hide();
        ui->editOldPwd ->hide();
        ui->lbNewPwd->hide();
        ui->editNewPwd ->hide();
        ui->lbConfirmPwd->hide();
        ui->editConfirmPwd->hide();
        ui->pbSavePassword->hide();
    }
}

void UserDetails::Save()
{
    QString userPassword = UserInterface::getUserInstance()->GetPassword();
    QString oldPassword = ui->editOldPwd->text();
    QString newPassword = ui->editNewPwd->text();
    QString confirmPassword = ui->editConfirmPwd->text();
    QString strpasshash = "";

    if(oldPassword.trimmed() == "")
    {
        PopUpMsg.setText("Please enter old password");
        PopUpMsg.exec();
        return;
    }

    if(newPassword.trimmed() == "")
    {
        PopUpMsg.setText("Please enter new password");
        PopUpMsg.exec();
        return;
    }

    if(confirmPassword.trimmed() == "")
    {
        PopUpMsg.setText("Please enter confirm password");
        PopUpMsg.exec();
        return;
    }

    strpasshash = UserInterface::getUserInstance()->GetPasswordHash(oldPassword);
    if(userPassword != strpasshash)
    {
        PopUpMsg.setText("Password entered is wrong");
        PopUpMsg.exec();
        return;
    }

    if(newPassword != confirmPassword)
    {
        PopUpMsg.setText("New password do not match confirm password");
        PopUpMsg.exec();
        return;
    }

    strpasshash = UserInterface::getUserInstance()->GetPasswordHash(newPassword);

    QSqlQuery EventQuery;
    QString strQuery = "UPDATE tbl_user SET";

    strQuery += " fld_password = '";
    strQuery += strpasshash;
    strQuery += "'";

    strQuery += " WHERE fld_username='";
    strQuery += UserInterface::getUserInstance()->GetLoggedInUserName();
    strQuery += "'";

    if(!EventQuery.exec(strQuery))
        qDebug()<<"ERROR"<<EventQuery.lastQuery();

    UserInterface::getUserInstance()->SetPassword(strpasshash);

    PopUpMsg.setText("Password Updated Succesfully");
    PopUpMsg.exec();

    ui->chkChangePwd->setChecked(false);
}

void UserDetails::CloseWindow()
{
    ui->editOldPwd->setText("");
    ui->editNewPwd->setText("");
    ui->editConfirmPwd->setText("");

    this->close();
}

UserDetails::~UserDetails()
{
    delete ui;
}
