#include "DisplayInfo.h"

//global data
bool DisplayInfo::instanceFlag = false;
DisplayInfo* DisplayInfo::displayInfoPtr = nullptr;

DisplayInfo::DisplayInfo()
{

}

DisplayInfo* DisplayInfo::getInstance()
{
    if(! instanceFlag)
    {
        displayInfoPtr = new DisplayInfo();
        instanceFlag = true;
    }

    return displayInfoPtr;
}

DisplayInfo::~DisplayInfo()
{
    displayInfoPtr = nullptr;
}

void DisplayInfo::DisplayMessage(QString msg, MessageType typeID)
{
    QMessageBox qMessageBoxObj;
    qMessageBoxObj.setFixedSize(1000, 500);
    qMessageBoxObj.setText(msg);

    switch (typeID) {
    case Normal:
        qMessageBoxObj.setIcon(QMessageBox::Information);
        break;
    case Warning:
        qMessageBoxObj.setIcon(QMessageBox::Warning);
        break;
    case Error:
        qMessageBoxObj.setIcon(QMessageBox::Critical);
        break;
    case Questions:
        qMessageBoxObj.setIcon(QMessageBox::Question);
        break;
    default:
        qMessageBoxObj.setIcon(QMessageBox::NoIcon);
        break;
    }

    qMessageBoxObj.exec();

}
