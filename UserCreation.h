#ifndef USERCREATION_H
#define USERCREATION_H

#include <QDialog>

#include <QMessageBox>
//#include <QSqlDatabase>

//#include "UserManagement/UserInterface.h"

namespace Ui {
    class UserCreation;
}

class UserCreation : public QDialog
{
    Q_OBJECT

public:
    explicit UserCreation(QWidget *parent = 0);
    ~UserCreation();

    void HideUserSelection();
    void ShowUserSelection();

    void HideDeleteButtuon();
    void ShowDeleteButtuon();

    void HideChangePassword();
    void ShowChangePassword();

    void DisableForEdit();
    void EnableForNew();

    void UpdateMode(QString);

    void LoadUserData();

private slots:
    void SlotChangePassword(bool);
    void Save();
    void CloseUserCreation();
    void DeleteUser();
    void UserSelectionChanged(QString);
    void UserTypeChanged(QString);

private:
    Ui::UserCreation *ui;
    QString UserCreateMode;
    QMessageBox PopUpMsg;
    QString strUserType;

    //Selected user data
    QString SelUser_userId;
    QString SelUser_username;
    QString SelUser_password;
    QString SelUser_userType;
    QString SelUser_tasksAssigned;
    QString SelUser_taskEditable;
    int SelUser_userStatus;

    void HideConfirmPassword();
    void ShowConfirmPassword();

    bool ValidateUsername(QString);
    bool IsUserExists(QString);
    bool ValidateNamePassword();
    void UpdateUserCombobox();

};

#endif // USERCREATION_H
