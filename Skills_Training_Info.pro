#-------------------------------------------------
#
# Project created by QtCreator 2018-07-06T13:23:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Skills_Training_Info
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    LoginScreen.cpp \
    MySQLDBConnect.cpp \
    UserCreation.cpp \
    UserDetails.cpp \
    AdminLoggedInScreen.cpp \
    UserData.cpp \
    UserInterface.cpp \
    DisplayAddSkills.cpp \
    SkillMatrixDisplay.cpp \
    EmployeeManagement.cpp \
    DBManagement.cpp \
    SkillMatrixManagement.cpp \
    DisplayUpdateSkills.cpp \
    QuestionPreview.cpp \
    DisplayInfo.cpp

HEADERS += \
    LoginScreen.h \
    MySQlDBConnect.h \
    UserCreation.h \
    UserDetails.h \
    AdminLoggedInScreen.h \
    UserData.h \
    UserInterface.h \
    DisplayAddSkills.h \
    SkillMatrixDisplay.h \
    EmployeeManagement.h \
    DBManagement.h \
    SkillMatrixManagement.h \
    DisplayUpdateSkills.h \
    QuestionPreview.h \
    DisplayInfo.h

FORMS += \
    LoginScreen.ui \
    UserCreation.ui \
    UserDetails.ui \
    AdminLoggedInScreen.ui \
    DisplayAddSkills.ui \
    SkillMatrixDisplay.ui \
    EmployeeManagement.ui \
    DBManagement.ui \
    SkillMatrixManagement.ui \
    DisplayUpdateSkills.ui \
    QuestionPreview.ui

RESOURCES += \
    icons.qrc

DISTFILES +=
