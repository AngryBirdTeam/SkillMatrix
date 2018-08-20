#include "UserCreation.h"
#include "ui_UserCreation.h"

#include <QSqlQuery>
#include <QDebug>

#include "UserInterface.h"

// UserCreation - UserCreation class constructor
UserCreation::UserCreation(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::UserCreation)
{
    ui->setupUi(this);

    ui->lineEditUserName->setMaxLength(20);
    ui->lineEditcfrmPassword->setMaxLength(20);
    ui->lineEditPassword->setMaxLength(20);

    // for change password checkbox
    connect(ui->chkboxChangePwd, SIGNAL(toggled(bool)), SLOT(SlotChangePassword(bool)));

    //for save
    connect(ui->btnSave, SIGNAL(clicked()), SLOT(Save()));

    //for close
    connect(ui->btnCancel, SIGNAL(clicked()), SLOT(CloseUserCreation()));

    //for delete
    connect(ui->btnDelete, SIGNAL(clicked()), SLOT(DeleteUser()));

    connect(ui->comboUserSelection, SIGNAL(currentIndexChanged(QString)), SLOT(UserSelectionChanged(QString)));
    connect(ui->comboUserType, SIGNAL(currentIndexChanged(QString)), SLOT(UserTypeChanged(QString)));

    UserCreateMode = "";
    strUserType = "1";

    UpdateUserCombobox();
}

// ~UserCreation - UserCreation class destructor
UserCreation::~UserCreation()
{
    delete ui;
}

// HideUserSelection - this function is used to hide user selection
void UserCreation::HideUserSelection()
{
    ui->lblSelectUser->hide();
    ui->comboUserSelection->hide();
}

// ShowUserSelection - this function is used to show user selection
void UserCreation::ShowUserSelection()
{
    ui->lblSelectUser->show();
    ui->comboUserSelection->show();
}

// HideDeleteButtuon - this function is used to hide Delete button
void UserCreation::HideDeleteButtuon()
{
    ui->btnDelete->hide();
}

// ShowDeleteButtuon - this function is used to show delete button
void UserCreation::ShowDeleteButtuon()
{
    ui->btnDelete->show();
}

// HideChangePassword - this function is used to hide change password ui
//                          component
void UserCreation::HideChangePassword()
{
    ui->chkboxChangePwd->hide();
}

// ShowChangePassword - this function is used to show change password ui
//                          component
void UserCreation::ShowChangePassword()
{
    ui->chkboxChangePwd->show();
}

// HideConfirmPassword - this function is used to hide confirm password ui
//                          component
void UserCreation::HideConfirmPassword()
{
    ui->lblPassword->hide();
    ui->lineEditPassword->hide();
    ui->lblcfrmPassword->hide();
    ui->lineEditcfrmPassword->hide();
}

// ShowConfirmPassword - this function is used to show confirm password ui
//                          component
void UserCreation::ShowConfirmPassword()
{
    ui->lblPassword->show();
    ui->lineEditPassword->show();
    ui->lblcfrmPassword->show();
    ui->lineEditcfrmPassword->show();
}

// DisableForEdit - this is a function to disable few ui components for an user
void UserCreation::DisableForEdit()
{
    ui->lblUserName->hide();
    ui->lineEditUserName->hide();
    ui->lineEditUserName->setEnabled(false);
    ui->lineEditPassword->setEnabled(false);

    HideConfirmPassword();
}

// EnableForNew - this is a function to enable few ui components for new user
void UserCreation::EnableForNew()
{
    ui->lblUserName->show();
    ui->lineEditUserName->show();
    ui->lineEditUserName->setEnabled(true);
    ui->lineEditPassword->setEnabled(true);

    ShowConfirmPassword();
}

// SlotChangePassword - this is a slot for change password
void UserCreation::SlotChangePassword(bool state)
{
    if(state == true)
    {
        ui->lineEditPassword->setEnabled(true);
        ShowConfirmPassword();
    }
    else
    {
        ui->lineEditPassword->setEnabled(false);
        HideConfirmPassword();
    }
}

// Save - this function is used to save user details to database
void UserCreation::Save()
{
    qDebug() << "inside save slot";

    if(UserCreateMode == "New")
    {
        if(!ValidateUsername(ui->lineEditUserName->text()))
        {
            return;
        }

        //user exists?
        if(!IsUserExists(ui->lineEditUserName->text()))
        {
            PopUpMsg.setText("User name already exists");
            PopUpMsg.exec();
            ui->lineEditUserName->setFocus();
            return;
        }

        if(!ValidateNamePassword())
        {
            return;
        }

        QString strpasshash = UserInterface::getUserInstance()->GetPasswordHash(ui->lineEditPassword->text());
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        QSqlQuery EventQuery;
        QString strQuery = "insert into tbl_user(fld_username, fld_password, fld_usertype_id, fld_created_by,";
        strQuery += " fld_created_date_time, fld_activated_status) ";
        strQuery += " values('";
        strQuery += ui->lineEditUserName->text();
        strQuery += "', '";
        strQuery += strpasshash;
        strQuery += "', '";
        strQuery += strUserType;
        strQuery += "', '";
        strQuery += UserInterface::getUserInstance()->GetLoggedInUserName();
        strQuery += "', '";
        strQuery += time;
        strQuery += "', '";

        if(ui->chkboxLocked->isChecked() == 0)
        {
            strQuery += "1";
        }
        else
        {
            strQuery += "0";
        }

        strQuery += "')";

        if(!EventQuery.exec(strQuery))
        {
            qDebug()<<"ERROR"<<EventQuery.lastQuery();
            return;
        }

        PopUpMsg.setText("User Created Succesfully");

        UpdateUserCombobox();
    }
    else if(UserCreateMode == "Edit")
    {
        bool userDataChanged = false;
        QString strpasshash = "";
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString userSelected = ui->comboUserSelection->currentText();

        if(!ValidateUsername(userSelected))
        {
            return;
        }

        //user exists?
        if(IsUserExists(userSelected))
        {
            return;
        }

        QSqlQuery EventQuery;
        QString strQuery = "UPDATE tbl_user SET";

        if(ui->chkboxChangePwd->isChecked() == 1)
        {
            if(!ValidateNamePassword())
            {
                return;
            }

            strpasshash = UserInterface::getUserInstance()->GetPasswordHash(ui->lineEditPassword->text());

            if(strpasshash != SelUser_password)
            {
                userDataChanged = true;
                SelUser_password = strpasshash;

                strQuery += " fld_password = '";
                strQuery += strpasshash;
                strQuery += "',";
            }
        }

        if(ui->comboUserType->currentText() != SelUser_userType)
        {
            userDataChanged = true;
            SelUser_userType = ui->comboUserType->currentText();
            strQuery += " fld_usertype_id = '";
            strQuery += strUserType;
            strQuery += "',";
        }

        if(ui->chkboxLocked->isChecked() != !SelUser_userStatus)
        {
            userDataChanged = true;
            if(ui->chkboxLocked->isChecked() == 0)
            {
                SelUser_userStatus = 1;
                strQuery += " fld_activated_status = '";
                strQuery += "1";
                strQuery += "',";
                strQuery += " fld_invalid_login_attempts = '";
                strQuery += "0";
                strQuery += "',";
            }
            else
            {
                SelUser_userStatus = 0;
                strQuery += " fld_activated_status = '";
                strQuery += "0";
                strQuery += "',";
            }
        }

        if(true == userDataChanged)
        {
            strQuery += " fld_modified_by = '";
            strQuery += UserInterface::getUserInstance()->GetLoggedInUserName();
            strQuery += "',";

            strQuery += " fld_modified_date_time = '";
            strQuery += time;
            strQuery += "'";

            strQuery += " WHERE fld_username='";
            strQuery += userSelected;
            strQuery += "'";

            if(!EventQuery.exec(strQuery))
            {
                qDebug()<<"ERROR"<<EventQuery.lastQuery();
                return;
            }
        }

        PopUpMsg.setText("User Updated Succesfully");
    }

    PopUpMsg.exec();

    ui->chkboxChangePwd->setChecked(0);
    ui->lineEditUserName->setText("");
    ui->lineEditPassword->setText("");
    ui->lineEditcfrmPassword->setText("");
    ui->chkboxLocked->setChecked(false);
}

// CloseUserCreation - this function is used to close user creation ui
void UserCreation::CloseUserCreation()
{
    qDebug() << "inside CloseUserCreation";

    ui->comboUserSelection->clear();
    ui->lineEditUserName->setText("");
    ui->lineEditPassword->setText("");
    ui->lineEditcfrmPassword->setText("");
    ui->chkboxLocked->setChecked(false);

    this->close();
}

// DeleteUser - this function is used to delete user
void UserCreation::DeleteUser()
{
    qDebug() << "inside DeleteUser";

    QString userSelected = ui->comboUserSelection->currentText();

    if(userSelected != "")
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "User Delete", "Are you sure you want to delete this user?.\nClick Yes to delete user.\nClick No to cancel.",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            QSqlQuery EventQuery;
            QString strQuery = "delete from tbl_user where fld_username='";
            strQuery += userSelected;
            strQuery += "'";

            if(!EventQuery.exec(strQuery))
            {
                qDebug()<<"ERROR"<<EventQuery.lastQuery();
                return;
            }

            ui->comboUserSelection->clear();
            ui->lineEditUserName->setText("");
            ui->lineEditPassword->setText("");
            ui->lineEditcfrmPassword->setText("");
            ui->chkboxLocked->setChecked(false);

            UpdateUserCombobox();

            PopUpMsg.setText("User Deleted Succesfully");
            PopUpMsg.exec();
        }
    }
}

// UpdateMode - this function is used to update mode
void UserCreation::UpdateMode(QString mode)
{
    int index = 0;
    qDebug() << "inside UpdateMode" << "Mode = " << mode;

    UserCreateMode = mode;

    ui->comboUserType->clear();

    QSqlQuery EventQuery;
    QString strQuery = "select * from tbl_user_type";

    if(!EventQuery.exec(strQuery))
    {
        qDebug()<<"ERROR"<<EventQuery.lastQuery();
        return;
    }

    while(EventQuery.next())
    {
        ui->comboUserType->insertItem(index++, EventQuery.value(1).toString());
    }

    UpdateUserCombobox();
}

// ValidateUsername - this function is used to validate username
bool UserCreation::ValidateUsername(QString username)
{
    QString _username = username.trimmed();

    if(_username.isEmpty())
    {
        PopUpMsg.setText("UserName is empty");
        PopUpMsg.exec();
        return false;
    }

    return true;
}

// IsUserExists - this function is used to verify whether the user exists or not
bool UserCreation::IsUserExists(QString username)
{
    bool userExists = false;
    QString _username = username.trimmed();

    QSqlQuery EventQuery;
    QString strQuery = "select fld_username from tbl_user where fld_username='";
    strQuery += _username;
    strQuery += "'";

    if(!EventQuery.exec(strQuery))
    {
        qDebug()<<"ERROR"<<EventQuery.lastQuery();
        return false;
    }

    while(EventQuery.next())
    {
        userExists = true;
        break;
    }

    if(true == userExists)
    {
        return false;
    }

    return true;
}

// ValidateNamePassword - this function is used to validate username & password
bool UserCreation::ValidateNamePassword()
{
    qDebug() << "inside ValidateNamePassword";

    if((ui->lineEditPassword->text().isEmpty()) || (ui->lineEditcfrmPassword->text().isEmpty()))
    {
        PopUpMsg.setText("Passwords are empty");
        PopUpMsg.exec();
        return false;
    }
    else if(ui->lineEditPassword->text() != ui->lineEditcfrmPassword->text())
    {
        PopUpMsg.setText("Passwords Do Not Match");
        PopUpMsg.exec();
        return false;
    }

    return true;
}

// UpdateUserCombobox - this function is used to update combo box
void UserCreation::UpdateUserCombobox()
{
    int index = 0;
    ui->comboUserSelection->clear();

    QSqlQuery EventQuery;
    QString strQuery = "select fld_username from tbl_user";

    if(!EventQuery.exec(strQuery))
    {
        qDebug()<<"ERROR"<<EventQuery.lastQuery();
        return;
    }

    while(EventQuery.next())
    {
        if(UserInterface::getUserInstance()->GetLoggedInUserName() != EventQuery.value(0).toString())
            ui->comboUserSelection->insertItem(index++, EventQuery.value(0).toString());
    }
}

// UserSelectionChanged - this function is used to update ui based on user
//                          selection
void UserCreation::UserSelectionChanged(QString value)
{
    ui->chkboxChangePwd->setChecked(false);
    ui->lineEditPassword->setText("");
    ui->lineEditcfrmPassword->setText("");

    LoadUserData();
}

// UserTypeChanged - this function is used to update details when User Type
//                  Changes
void UserCreation::UserTypeChanged(QString)
{
    QSqlQuery EventQuery;
    QString strQuery = "select * from tbl_user_type";

    if(!EventQuery.exec(strQuery))
    {
        qDebug()<<"ERROR"<<EventQuery.lastQuery();
        return;
    }

    while(EventQuery.next())
    {
        if(EventQuery.value(1).toString() == ui->comboUserType->currentText())
        {
            strUserType = EventQuery.value(0).toString();
            break;
        }
    }
}

// LoadUserData - This function is used to load user data
void UserCreation::LoadUserData()
{
    QString userSelected = "";

    if(ui->comboUserSelection->count() > 0)
    {
        userSelected = ui->comboUserSelection->currentText();
        QSqlQuery EventQuery;
        QString strQuery = "select b.fld_usertype, a.fld_password, a.fld_activated_status";
        strQuery += " FROM tbl_user a, tbl_user_type b";
        strQuery += " WHERE a.fld_usertype_id = b.fld_usertype_id";
        strQuery += " AND a.fld_username='";
        strQuery += userSelected;
        strQuery += "'";

        if(!EventQuery.exec(strQuery))
        {
            qDebug()<<"ERROR"<<EventQuery.lastQuery();
            return;
        }

        qDebug() << "query = " << strQuery;

        while(EventQuery.next())
        {
            int index = ui->comboUserType->findText(EventQuery.value(0).toString());
            if(index >= 0 && index < ui->comboUserType->count())
                ui->comboUserType->setCurrentIndex(index);
            ui->chkboxLocked->setChecked(!EventQuery.value(2).toInt());

            SelUser_username = userSelected;
            SelUser_password = EventQuery.value(1).toString();
            SelUser_userType = EventQuery.value(0).toString();
            SelUser_userStatus = EventQuery.value(2).toInt();

            break;
        }
    }
}
