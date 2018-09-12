#include "SkillMatrixDisplay.h"
#include "ui_SkillMatrixDisplay.h"

SkillMatrixDisplay::SkillMatrixDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SkillMatrixDisplay)
{
    ui->setupUi(this);
    setWindowTitle("Skill Matrix Display");

    Init();

    SetupMenuBar();
    SetupToolBar();

}

SkillMatrixDisplay::~SkillMatrixDisplay()
{
    delete ui;
}

void SkillMatrixDisplay::Init()
{
    fileMenu = nullptr;
    userMenu = nullptr;
    userMgnt = nullptr;
    helpMenu = nullptr;

    exitAction = nullptr;
    userDetailsAction = nullptr;
    newUserAction = nullptr;
    editUserAction = nullptr;
    aboutAction = nullptr;

    userDetailsPtr = new UserDetails();
    userCreationPtr = new UserCreation();
    skillMatrixManagementPtr = new SkillMatrixManagement();
}

void SkillMatrixDisplay::SetupMenuBar()
{
    //Action for EXIT
    exitAction = new QAction(tr("&Exit"),this);
    exitAction->setStatusTip(tr("Close Application"));

    //file Menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()), SLOT(ExitApplSlot()) );

    //Action for view SkillSet
    viewSkillSetAction = new QAction(tr("&Skills"),this);
    viewSkillSetAction->setStatusTip(tr("Display Skill Set"));

    //view Menu
    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(viewSkillSetAction);
    connect(viewSkillSetAction, SIGNAL(triggered()), SLOT(ViewSkillSet()) );

    //Action for User Details
    userDetailsAction = new QAction(tr("&User Details"),this);
    userDetailsAction->setStatusTip(tr("Details"));

    //user Menu
    userMenu = menuBar()->addMenu(tr("&User Data"));
    userMenu->addAction(userDetailsAction);

    //Action for new and edit user
    newUserAction = new QAction(tr("&New User"),this);
    newUserAction->setStatusTip(tr("New"));
    newUserAction->setIcon(QIcon(":/Images/Images/NewUser.png"));

    editUserAction = new QAction(tr("&Edit User"),this);
    editUserAction->setStatusTip(tr("Edit"));
    editUserAction->setIcon(QIcon(":/Images/Images/EditUser.png"));

    //Menu for user management
    userMgnt = new QMenu(tr("&User Management"));
    userMgnt->addAction(newUserAction);
    userMgnt->addAction(editUserAction);
    userMgnt->setIcon(QIcon(":/Images/Images/UserMgnt.png"));

    userMenu->addMenu(userMgnt);

    connect(userDetailsAction, SIGNAL(triggered()), SLOT(DisplayUserDetails()) );
    connect(newUserAction, SIGNAL(triggered()), SLOT(NewUserSlot()) );
    connect(editUserAction, SIGNAL(triggered()), SLOT(EditUserSlot()) );

    //Action for About
    aboutAction = new QAction(tr("&About"),this);
    aboutAction->setStatusTip(tr("About"));

    //Help Menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    //connect(aboutAction, SIGNAL(triggered()), SLOT(ExitApplSlot()) );
}

void SkillMatrixDisplay::SetupToolBar()
{
    //Toolbar for User management
    userMgntToolbar =  new QToolBar(tr("User Management"));
    userMgntToolbar->setMovable(false);
    userMgntToolbar->setToolTip("User Management");

    //User Management Icon
    UserMgntMenu = new QMenu();

    newUserToolbtn = new QToolButton();
    newUserToolbtn->setMenu(UserMgntMenu);
    newUserToolbtn->setToolTip("User Management");
    newUserToolbtn->setIcon(QIcon(":/Images/Images/UserMgnt.png"));
    newUserToolbtn->setPopupMode(QToolButton::InstantPopup);
    newUserToolbtn->setEnabled(true); // by default

    userMgntToolbar->addWidget(newUserToolbtn);
    userMgntToolbar->setIconSize(QSize(40,40));

    //Action for new and edit user
    newUserToolbtnAction = new QAction(tr("&New User"),this);
    newUserToolbtnAction->setStatusTip(tr("New"));
    newUserToolbtnAction->setIcon(QIcon(":/Images/Images/NewUser.png"));

    editUserToolbtnAction = new QAction(tr("&Edit User"),this);
    editUserToolbtnAction->setStatusTip(tr("Edit"));
    editUserToolbtnAction->setIcon(QIcon(":/Images/Images/EditUser.png"));

    connect(newUserToolbtnAction, SIGNAL(triggered()), SLOT(NewUserSlot()) );
    connect(editUserToolbtnAction, SIGNAL(triggered()), SLOT(EditUserSlot()) );

    UserMgntMenu->addAction(newUserToolbtnAction);
    UserMgntMenu->addAction(editUserToolbtnAction);

    userMgntToolbar->addSeparator();
    addToolBar(userMgntToolbar);

    //Toolbar for Skill Matrix
    skillMatrixToolbar =  new QToolBar(tr("Skill Matrix"));
    skillMatrixToolbar->setMovable(false);
    skillMatrixToolbar->setToolTip("Skill Matrix");

    displaySkillMatrixToolbtn = new QToolButton();
    displaySkillMatrixToolbtn->setToolTip("Display Skill Matrix");
    displaySkillMatrixToolbtn->setIcon(QIcon(":/Images/Images/SkillMatrix.png"));
    displaySkillMatrixToolbtn->setPopupMode(QToolButton::InstantPopup);
    displaySkillMatrixToolbtn->setEnabled(true); // by default

    addSkillToMatrixToolbtn = new QToolButton();
    addSkillToMatrixToolbtn->setToolTip("Add New Skill");
    addSkillToMatrixToolbtn->setIcon(QIcon(":/Images/Images/add.png"));
    addSkillToMatrixToolbtn->setPopupMode(QToolButton::InstantPopup);
    addSkillToMatrixToolbtn->setEnabled(true); // by default

    editSkillInMatrixToolbtn = new QToolButton();
    editSkillInMatrixToolbtn->setToolTip("Edit Skill Matrix");
    editSkillInMatrixToolbtn->setIcon(QIcon(":/Images/Images/edit.png"));
    editSkillInMatrixToolbtn->setPopupMode(QToolButton::InstantPopup);
    editSkillInMatrixToolbtn->setEnabled(true); // by default

    skillMatrixToolbar->addWidget(displaySkillMatrixToolbtn);
    skillMatrixToolbar->addWidget(addSkillToMatrixToolbtn);
    skillMatrixToolbar->addWidget(editSkillInMatrixToolbtn);

    connect(addSkillToMatrixToolbtn, SIGNAL(clicked(bool)), this, SLOT(AddSkillSlot(bool)));
    connect(displaySkillMatrixToolbtn, SIGNAL(clicked()), this, SLOT(ViewSkillSet()));

    skillMatrixToolbar->setIconSize(QSize(40,40));

    skillMatrixToolbar->addSeparator();
    addToolBar(skillMatrixToolbar);

}

void SkillMatrixDisplay::ExitApplSlot()
{
    this->close();
}

void SkillMatrixDisplay::closeEvent(QCloseEvent *event)
{
    ExitApplSlot();
}

void SkillMatrixDisplay::DisplayUserDetails()
{
    userDetailsPtr->show();
}

void SkillMatrixDisplay::NewUserSlot()
{
    userCreationPtr->setWindowTitle("Create New User");
    userCreationPtr->HideUserSelection();
    userCreationPtr->EnableForNew();
    userCreationPtr->HideChangePassword();
    userCreationPtr->HideDeleteButtuon();
    userCreationPtr->UpdateMode("New");

    userCreationPtr->show();
}

void SkillMatrixDisplay::EditUserSlot()
{
    userCreationPtr->setWindowTitle("Edit/Delete User");
    userCreationPtr->ShowUserSelection();
    userCreationPtr->DisableForEdit();
    userCreationPtr->ShowChangePassword();
    userCreationPtr->ShowDeleteButtuon();
    userCreationPtr->LoadUserData();
    userCreationPtr->UpdateMode("Edit");

    userCreationPtr->show();
}

void SkillMatrixDisplay::UpdateGUIBasedOnLoggedUser()
{
    if( UserInterface::getUserInstance()->GetUserType() == "Administrator" )
    {
        userMgnt->setEnabled(true);
    }
    else if( UserInterface::getUserInstance()->GetUserType() == "Normal User" )
    {
        userMgnt->setEnabled(false);
    }
    else if( UserInterface::getUserInstance()->GetUserType() == "Privileged User" )
    {
        userMgnt->setEnabled(false);
    }
}

void SkillMatrixDisplay::ViewSkillSet()
{
    if(!skillMatrixManagementPtr->isActiveWindow())
    {
        skillMatrixManagementPtr->activateWindow();
    }

    skillMatrixManagementPtr->DisplaySkillSet();
}

void SkillMatrixDisplay::AddSkillSlot(bool state)
{
    if(!skillMatrixManagementPtr->isActiveWindow())
    {
        skillMatrixManagementPtr->activateWindow();
    }

    skillMatrixManagementPtr->DisplayPrepareSkillSet();
}
