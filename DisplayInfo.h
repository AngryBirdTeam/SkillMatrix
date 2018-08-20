#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QString>
#include <QMessageBox>

class DisplayInfo
{
public:
    DisplayInfo();

    static DisplayInfo* getInstance();
    ~DisplayInfo();

    enum MessageType{Normal = 0, Warning = 1, Error = 2, Questions = 3};

    void DisplayMessage(QString msg, MessageType typeID);

private:
    static bool instanceFlag;
    static DisplayInfo* displayInfoPtr;
};

#endif // DISPLAYINFO_H
