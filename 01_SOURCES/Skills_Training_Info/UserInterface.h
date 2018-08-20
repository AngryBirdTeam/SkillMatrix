#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "UserData.h"

class UserInterface
{
private:
    UserInterface();
    static bool UserInterfaceFlag;
    static  UserInterface *UserInterfaceInst;
    static UserData *pUserData;    

public:

    ~UserInterface();

    static UserInterface * getInstance();
    static UserData * getUserInstance();

};

#endif // USERINTERFACE_H
