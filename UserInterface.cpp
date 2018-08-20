#include "UserInterface.h"

bool UserInterface::UserInterfaceFlag = false;
UserInterface *UserInterface::UserInterfaceInst=NULL;
UserData * UserInterface::pUserData=NULL;

UserInterface::UserInterface()
{

}

UserInterface* UserInterface::getInstance()
{
    if(!UserInterfaceFlag)
    {
        UserInterfaceInst = new UserInterface();
        pUserData=new UserData();
        UserInterfaceFlag = true;
        return UserInterfaceInst;
    }
    else
    {
        return UserInterfaceInst;
    }
}

UserInterface::~UserInterface()
{
    if(NULL != pUserData)
    {
        delete pUserData;
        pUserData = NULL;
    }
    UserInterfaceInst=NULL;
}

UserData* UserInterface::getUserInstance()
{

    if(pUserData==NULL)
    {
        getInstance();
        return pUserData;
    }
    else
    {
        return pUserData;
    }
}
