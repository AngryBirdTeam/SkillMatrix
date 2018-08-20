#include "UserData.h"

void UserData::init()
{
    username = "";
    password = "";
    userType = "";
    createdBy = "";
    QDateTime temp;
    createdDateTime = temp;
    modifiedBy = "";
    modifiedDateTime = temp;
    userStatus = false;
    invalidLoginAttempts = -1;
}

UserData::UserData()
{
    init();
}

UserData::~UserData()
{
}

void UserData::SetUserId(unsigned int Id)
{
    userId = Id;
}

void UserData::SetUserName(QString Name)
{
    username = Name;
}

void UserData::SetPassword(QString Pwd)
{
    password = Pwd;
}

void UserData::SetUserType(QString Type)
{
    userType = Type;
}

void UserData::SetCreatedBy(QString usercreatedby)
{
    createdBy = usercreatedby;
}

void UserData::SetCreatedDateTime(QDateTime localDatetime)
{
    createdDateTime = localDatetime;
}

void UserData::SetModifiedBy(QString usermodifiedby)
{
    modifiedBy = usermodifiedby;
}

void UserData::SetModifiedDateTime(QDateTime localDatetime)
{
    modifiedDateTime = localDatetime;
}

void UserData::SetUserStatus(bool state)
{
    userStatus = state;
}

void UserData::SetInvalidLoginAttempts(int count)
{
    invalidLoginAttempts = count;
}

unsigned int UserData::GetUserId()
{
    return userId;
}

QString UserData::GetLoggedInUserName()
{
    return username;
}

QString UserData::GetPassword()
{
    return password;
}

QString UserData::GetUserType()
{
    return userType;
}

QString UserData::GetCreatedBy()
{
    return createdBy;
}

QDateTime UserData::GetCreatedDateTime()
{
    return createdDateTime;
}

QString UserData::GetModifiedBy()
{
    return modifiedBy;
}

QDateTime UserData::GetModifiedDateTime()
{
    return modifiedDateTime;
}

bool UserData::GetUserStatus()
{
    return userStatus;
}

int UserData::GetInvalidLoginAttempts()
{
    return invalidLoginAttempts;
}

void UserData::UpdateDataAfterLogin(QString LoginUser)
{

    QString strQuery="";
    strQuery = "SELECT * from tbl_user where fld_username='";
    strQuery += LoginUser;
    strQuery += "'";
    QSqlQuery query;

    if(!query.exec(strQuery))
        qDebug()<<"ERROR = "<<query.lastQuery();

    query.next();

    SetUserId(query.value(0).toInt());

    SetUserName(query.value(1).toString());

    SetPassword(query.value(2).toString());

    int UsertypeId = query.value(3).toInt();
    if(UsertypeId == 1)
    {
        SetUserType("Administrator");
    }
    else if(UsertypeId == 2)
    {
        SetUserType("Normal User");
    }
    else if(UsertypeId == 3)
    {
        SetUserType("Privileged User");
    }

    SetCreatedBy(query.value(4).toString());

    SetCreatedDateTime(query.value(5).toDateTime());

    SetModifiedBy(query.value(6).toString());

    SetModifiedDateTime(query.value(7).toDateTime());

    SetUserStatus(query.value(8).toBool());

    SetInvalidLoginAttempts(query.value(9).toInt());

}

QString UserData::GetPasswordHash(QString pass)
{
    QByteArray passArray;
    passArray.append(pass);

    QString encodedPass = QString(QCryptographicHash::hash(passArray,QCryptographicHash::Md5).toHex());

    return encodedPass;
}
