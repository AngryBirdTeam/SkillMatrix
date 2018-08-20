#include "LoginScreen.h"
#include "ui_LoginScreen.h"
#include <QMessageBox>
#include "UserInterface.h"

unsigned short LoginScreen::loginNameLen = 20;
unsigned short LoginScreen::loginPwdLen = 100;

LoginScreen::LoginScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Skill Management Login");

    ui->lbl_unlockmsg->clear();

    ui->lineedit_username->setMaxLength(loginNameLen);
    ui->lineedit_password->setMaxLength(loginNameLen);

    ui->lineedit_password->setEchoMode(QLineEdit::Password);

    ui->lbl_unlockmsg->setText(tr("Enter Login Credentials"));

    QObject::connect(ui->pbtn_login, SIGNAL(clicked(bool)), this, SLOT(onLogin(bool)));
    QObject::connect(ui->pbtn_close, SIGNAL(clicked(bool)), this, SLOT(closeLoginScreen(bool)));

    //creates database connection
    init();

    //just for debug purpose added - remove it on release
    ui->lineedit_username->setText("eik5kor");
    ui->lineedit_password->setText("eik5kor");

//    this->setAttribute(Qt::WA_QuitOnClose, false);

}

LoginScreen::~LoginScreen()
{
    if(nullptr != MySQLDBConnectPtr)
    {
        MySQLDBConnectPtr->CloseDatabase();
        delete MySQLDBConnectPtr;
        MySQLDBConnectPtr = nullptr;
    }

    if(nullptr != adminLoggedInScreenPtr)
    {
        delete adminLoggedInScreenPtr;
        adminLoggedInScreenPtr = nullptr;
    }

    if(nullptr != skillMatrixDisplayPtr)
    {
        delete skillMatrixDisplayPtr;
        skillMatrixDisplayPtr = nullptr;
    }

    if(nullptr != employeeManagementPtr)
    {
        delete employeeManagementPtr;
        employeeManagementPtr = nullptr;
    }

    delete ui;
}

void LoginScreen::init()
{
    adminLoggedInScreenPtr = nullptr;
    skillMatrixDisplayPtr = nullptr;
    employeeManagementPtr = nullptr;

    //if database information needs to be changed update here
    MySQLDBConnectPtr = new MySQLDBConnect("localhost", "skills", "root", "password");
}

void LoginScreen::closeEvent (QCloseEvent *event)
{
    //close the application
    this->close();
}

void LoginScreen::onLogin(bool clickstate)
{
    ui->lbl_unlockmsg->clear();

    QString loginPwd = ui->lineedit_password->text();
    QString loginUserName = ui->lineedit_username->text();
    QString strQuery = "";
    QString errorMsg;

    if( MySQLDBConnectPtr->isDBOpen() )
    {
        strQuery = "SELECT * from tbl_user where fld_username = '";
        strQuery += loginUserName;
        strQuery += "'";

        QSqlQuery query;

        if( !query.exec(strQuery) )
        {
            errorMsg = "Error: last query was: ";
            errorMsg.append( query.lastQuery() );
            errorMsg.append("\n");
            errorMsg.append( query.lastError().text() );

            QMessageBox::critical(0, QObject::tr("DatabaseError"),
                                  errorMsg);
            return;
        }

        if( query.next() )// user exists it enters
        {
            unsigned int userTypeId = query.value(3).toInt(); // usertype id
            QString dbPwd = query.value(2).toString(); // user password
            unsigned int dbLoginAtmpt = query.value(9).toInt(); //user invalid login attempts
            bool userStatus = query.value(8).toBool();

            if(userStatus  && (dbLoginAtmpt >= 0 && dbLoginAtmpt < 3)) // status is active enter
            {
                if(dbPwd == UserInterface::getUserInstance()->GetPasswordHash(loginPwd)) // password matches
                    //if(dbPwd == loginPwd) // password matches
                {
                    this->close();

                    displayInfoPointer->DisplayMessage("Login Successful", DisplayInfo::MessageType::Normal);

                    strQuery = "UPDATE tbl_user SET fld_invalid_login_attempts='";
                    strQuery += "0";
                    strQuery += "'";
                    strQuery += " WHERE fld_username='";
                    strQuery += loginUserName;
                    strQuery += "'";

                    if( !query.exec(strQuery) )
                    {
                        displayInfoPointer->DisplayMessage(query.lastQuery(), DisplayInfo::MessageType::Error);

                        displayInfoPointer->DisplayMessage(query.lastError().text(), DisplayInfo::MessageType::Error);

                        return;
                    }

                    UserInterface::getUserInstance()->UpdateDataAfterLogin(loginUserName);

                    skillMatrixDisplayPtr = new SkillMatrixDisplay();

                    employeeManagementPtr = new EmployeeManagement();

                    dbManagementPtr = new DBManagement();

                    QObject::connect(this, SIGNAL(UpdateUserDetails(QString)), skillMatrixDisplayPtr->userDetailsPtr, SLOT(slotUpdateUserDetails(QString)));

                    emit UpdateUserDetails(loginUserName);

                    if(userTypeId == 1)
                    {
                        //administrator specific GUI
                        adminLoggedInScreenPtr = new AdminLoggedInScreen();
                        adminLoggedInScreenPtr->show();

                        connect(adminLoggedInScreenPtr, SIGNAL(skillMatrixGUI()), this, SLOT(displaySkillMatrixWin()));
                        connect(adminLoggedInScreenPtr, SIGNAL(empMgntGUI()), this, SLOT(displayEmployeeMgntWin()));
                        connect(adminLoggedInScreenPtr, SIGNAL(databaseGUI()), this, SLOT(displayDBMgntWin()));
                    }
                    else
                    {
                        //other users GUI
                        displaySkillMatrixWin();
                    }
                }
                else
                {
                    if(userTypeId != 1) // admin type no block
                    {
                        dbLoginAtmpt = dbLoginAtmpt + 1;
                        strQuery = "UPDATE tbl_user SET fld_invalid_login_attempts='";
                        strQuery += QString::number(dbLoginAtmpt);
                        strQuery += "'";
                        strQuery += " WHERE fld_username='";
                        strQuery += loginUserName;
                        strQuery += "'";

                        if( !query.exec(strQuery) )
                        {
                            displayInfoPointer->DisplayMessage(query.lastQuery(), DisplayInfo::MessageType::Error);

                            displayInfoPointer->DisplayMessage(query.lastError().text(), DisplayInfo::MessageType::Error);

                            return;
                        }

                        ui->lbl_unlockmsg->clear();
                        ui->lbl_unlockmsg->setText(tr("Wrong password"));
                        ui->lineedit_username->setFocus();

                        if(dbLoginAtmpt == 2)    //when limit set to 2 use == 1
                        {
                            ui->lbl_unlockmsg->clear();
                            ui->lbl_unlockmsg->setText(tr("Wrong password: last login attempt"));
                            ui->lineedit_username->setFocus();
                        }
                        else if(dbLoginAtmpt >= 3)
                        {
                            QString strQuery = "UPDATE tbl_user SET fld_activated_status='";
                            strQuery += "0";
                            strQuery += "',";
                            strQuery += " WHERE fld_username='";
                            strQuery += loginUserName;
                            strQuery += "'";

                            if(!query.exec(strQuery))
                            {
                                displayInfoPointer->DisplayMessage(query.lastQuery(), DisplayInfo::MessageType::Error);

                                displayInfoPointer->DisplayMessage(query.lastError().text(), DisplayInfo::MessageType::Error);
                                return;
                            }

                            ui->lbl_unlockmsg->clear();
                            ui->lbl_unlockmsg->setText(tr("User is blocked"));
                            ui->lineedit_username->setFocus();
                        }
                    }
                    else
                    {
                        ui->lbl_unlockmsg->clear();
                        ui->lbl_unlockmsg->setText(tr("Wrong password"));
                        ui->lineedit_username->setFocus();
                    }
                }
            }
            else
            {
                ui->lbl_unlockmsg->clear();
                ui->lbl_unlockmsg->setText(tr("User is Deactivated: Cannot Login"));
                ui->lineedit_username->setFocus();
            }
        }
        else
        {
            ui->lbl_unlockmsg->clear();
            ui->lbl_unlockmsg->setText(tr("Invalid UserName: Please enter Valid UserName"));
            ui->lineedit_username->setFocus();
        }
    }
    else
    {
        ui->lbl_unlockmsg->setText(tr("Unable to connect to database"));
    }
}

void LoginScreen::closeLoginScreen(bool clickstate)
{
    this->close();
}

void LoginScreen::displaySkillMatrixWin()
{
    skillMatrixDisplayPtr->UpdateGUIBasedOnLoggedUser();
    skillMatrixDisplayPtr->show();
}

void LoginScreen::displayEmployeeMgntWin()
{
    employeeManagementPtr->show();
}

void LoginScreen::displayDBMgntWin()
{
    dbManagementPtr->show();
}
