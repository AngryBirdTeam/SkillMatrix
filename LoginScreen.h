#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QDialog>
#include <QString>

#include "MySQlDBConnect.h"
#include "AdminLoggedInScreen.h"
#include "SkillMatrixDisplay.h"
#include "EmployeeManagement.h"
#include "DBManagement.h"

#include "DisplayInfo.h"

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QDialog
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent = 0);
    ~LoginScreen();
signals:
    void UpdateUserDetails(QString);

private slots:
    void closeLoginScreen(bool);
    void onLogin(bool);
    void closeEvent (QCloseEvent *event);
    void displaySkillMatrixWin();
    void displayEmployeeMgntWin();
    void displayDBMgntWin();

private:
    Ui::LoginScreen *ui;

    static unsigned short loginNameLen;
    static unsigned short loginPwdLen;

    MySQLDBConnect *MySQLDBConnectPtr;
    AdminLoggedInScreen *adminLoggedInScreenPtr;
    SkillMatrixDisplay *skillMatrixDisplayPtr;
    EmployeeManagement *employeeManagementPtr;
    DBManagement *dbManagementPtr;
    DisplayInfo *displayInfoPointer;

    void init();
};

#endif // LOGINSCREEN_H
