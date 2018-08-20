#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QCryptographicHash>
#include <QDebug>

class UserData
{
public:

    void init();
    UserData();
    ~UserData();

    void SetUserId(unsigned int);
    void SetUserName(QString);
    void SetPassword(QString);
    void SetUserType(QString);
    void SetCreatedBy(QString);
    void SetCreatedDateTime(QDateTime);
    void SetModifiedBy(QString);
    void SetModifiedDateTime(QDateTime);
    void SetUserStatus(bool);
    void SetInvalidLoginAttempts(int);

    unsigned int GetUserId();
    QString GetLoggedInUserName();
    QString GetPassword();
    QString GetUserType();
    QString GetCreatedBy();
    QDateTime GetCreatedDateTime();
    QString GetModifiedBy();
    QDateTime GetModifiedDateTime();
    bool GetUserStatus();
    int GetInvalidLoginAttempts();

    void UpdateDataAfterLogin(QString);

    QString GetPasswordHash(QString pass);

private:

    //holds the user details
    unsigned int userId;
    QString username;
    QString password;
    QString userType;
    QString createdBy;
    QDateTime createdDateTime;
    QString modifiedBy;
    QDateTime modifiedDateTime;
    bool userStatus;
    qint8 invalidLoginAttempts;

};

#endif // USERDATA_H
