#include "SkillMatrixDisplay.h"
#include "ui_SkillMatrixDisplay.h"

SkillMatrixDisplay::SkillMatrixDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SkillMatrixDisplay)
{
    ui->setupUi(this);
    setWindowTitle("Skill Matrix Display");

    Init();

    CreateWidgets();

    SetupMenuBar();
    SetupToolBar();
    SetupDockWidgets();
    SetupStatusBar();

    SetAboutInfo();

    //this is done to avoid tabbed docks
    this->setDockOptions(QMainWindow::AnimatedDocks);

    //set default position as (0,0)
    this->move(0,0);

    QDesktopWidget *desktop = QApplication::desktop();
    int screenNo = desktop->primaryScreen();
    int screenWidth = desktop->availableGeometry(screenNo).width();
    int screenHeight = desktop->availableGeometry(screenNo).height();

    //set default size of window
    this->resize(screenWidth-50, screenHeight-50);
}

SkillMatrixDisplay::~SkillMatrixDisplay()
{
    delete ui;

    if(userDetailsPtr != nullptr)
    {
        delete userDetailsPtr;
        userDetailsPtr = nullptr;
    }

    if(userCreationPtr != nullptr)
    {
        delete userCreationPtr;
        userCreationPtr = nullptr;
    }

    if(skillMatrixManagementPtr != nullptr)
    {
        delete skillMatrixManagementPtr;
        skillMatrixManagementPtr = nullptr;
    }

    if(skillGroupManagementPtr != nullptr)
    {
        delete skillGroupManagementPtr;
        skillGroupManagementPtr = nullptr;
    }

    if(trainingDisplayPtr != nullptr)
    {
        delete trainingDisplayPtr;
        trainingDisplayPtr = nullptr;
    }

    if(individualReportPtr != nullptr)
    {
        delete individualReportPtr;
        individualReportPtr = nullptr;
    }

    if(teamReportPtr != nullptr)
    {
        delete teamReportPtr;
        teamReportPtr = nullptr;
    }

    if(deptReportPtr != nullptr)
    {
        delete deptReportPtr;
        deptReportPtr = nullptr;
    }
}

void SkillMatrixDisplay::Init()
{
    fileMenu = nullptr;
    viewMenu = nullptr;
    userMenu = nullptr;
    userMgnt = nullptr;
    helpMenu = nullptr;

    exitAction = nullptr;
    viewSkillSetAction = nullptr;
    userDetailsAction = nullptr;
    newUserAction = nullptr;
    editUserAction = nullptr;
    aboutAction = nullptr;
    addSkillToGrpAction = nullptr;
    editSkillGrpAction = nullptr;
    addSkillToMatrixAction = nullptr;
    editSkillInMatrixAction = nullptr;

    userMgntToolbar = nullptr;
    skillGroupToolbar = nullptr;
    skillMatrixToolbar = nullptr;

    newUserToolbtn = nullptr;
    editUserToolbtn = nullptr;
    skillGroupToolbtn = nullptr;
    displaySkillMatrixToolbtn = nullptr;
    skillMatrixMgntToolbtn = nullptr;

    userMgntMenu = nullptr;
    skillGrpMenu = nullptr;
    skillMatrixMenu = nullptr;

    newUserToolbtnAction = nullptr;
    editUserToolbtnAction = nullptr;

    dockTrainDetails = nullptr;
    dockIndReport = nullptr;
    dockTeamReport = nullptr;
    dockDeptReport = nullptr;

    lblLoggedUser = nullptr;
    lblLoggedUserType = nullptr;

    userDetailsPtr = nullptr;
    userCreationPtr = nullptr;
    skillMatrixManagementPtr = nullptr;
    skillGroupManagementPtr = nullptr;
    trainingDisplayPtr = nullptr;
    individualReportPtr = nullptr;
    teamReportPtr = nullptr;
    deptReportPtr = nullptr;
}

void SkillMatrixDisplay::CreateWidgets()
{
    userDetailsPtr = new UserDetails();
    userCreationPtr = new UserCreation();
    skillMatrixManagementPtr = new SkillMatrixManagement();
    skillGroupManagementPtr = new SkillGroupManagement();
    trainingDisplayPtr = new TrainingDisplay();
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
    connect(aboutAction, SIGNAL(triggered()), SLOT(LoadAboutSlot()));

    qDebug()<< "MenuBar generated";
}

void SkillMatrixDisplay::SetupToolBar()
{
    //Toolbar for User management
    userMgntToolbar =  new QToolBar(tr("User Management"));
    userMgntToolbar->setMovable(false);
    userMgntToolbar->setToolTip("User Management");

    //User Management Menu
    userMgntMenu = new QMenu();

    newUserToolbtn = new QToolButton();
    newUserToolbtn->setMenu(userMgntMenu);
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

    userMgntMenu->addAction(newUserToolbtnAction);
    userMgntMenu->addAction(editUserToolbtnAction);

    addToolBar(userMgntToolbar);

    //Toolbar for Skill Group
    skillGroupToolbar =  new QToolBar(tr("Skill Group"));
    skillGroupToolbar->setMovable(false);
    skillGroupToolbar->setToolTip("Skill Group");

    //Skill Group Menu
    skillGrpMenu = new QMenu();

    skillGroupToolbtn = new QToolButton();
    skillGroupToolbtn->setMenu(skillGrpMenu);
    skillGroupToolbtn->setToolTip("Skill Group");
    skillGroupToolbtn->setIcon(QIcon(":/Images/Images/SkillGroup.png"));
    skillGroupToolbtn->setPopupMode(QToolButton::InstantPopup);
    skillGroupToolbtn->setEnabled(true); // by default

    skillGroupToolbar->addWidget(skillGroupToolbtn);
    skillGroupToolbar->setIconSize(QSize(40,40));

    //Action for add and edit skill group
    addSkillToGrpAction = new QAction(tr("&Add Skill Group"),this);
    addSkillToGrpAction->setStatusTip(tr("Add"));
    addSkillToGrpAction->setIcon(QIcon(":/Images/Images/add.png"));

    editSkillGrpAction = new QAction(tr("&Edit Skill Group"),this);
    editSkillGrpAction->setStatusTip(tr("Edit"));
    editSkillGrpAction->setIcon(QIcon(":/Images/Images/edit.png"));

    //    editSkillGrpAction->setEnabled(false); //temporarily disabled

    connect(addSkillToGrpAction, SIGNAL(triggered()), skillGroupManagementPtr, SLOT(DisplayAddUi()) );
    connect(editSkillGrpAction, SIGNAL(triggered()), skillGroupManagementPtr, SLOT(DisplayDelUi()) );

    skillGrpMenu->addAction(addSkillToGrpAction);
    skillGrpMenu->addAction(editSkillGrpAction);

    addToolBar(skillGroupToolbar);

    //Toolbar for Skill Matrix
    skillMatrixToolbar =  new QToolBar(tr("Skill Matrix"));
    skillMatrixToolbar->setMovable(false);
    skillMatrixToolbar->setToolTip("Skill Matrix");

    displaySkillMatrixToolbtn = new QToolButton();
    displaySkillMatrixToolbtn->setToolTip("Display Skill Matrix");
    displaySkillMatrixToolbtn->setIcon(QIcon(":/Images/Images/SkillMatrix.png"));
    displaySkillMatrixToolbtn->setPopupMode(QToolButton::InstantPopup);
    displaySkillMatrixToolbtn->setEnabled(true); // by default

    skillMatrixToolbar->addWidget(displaySkillMatrixToolbtn);

    //Skill Matrix Menu
    skillMatrixMenu = new QMenu();

    skillMatrixMgntToolbtn = new QToolButton();
    skillMatrixMgntToolbtn->setMenu(skillMatrixMenu);
    skillMatrixMgntToolbtn->setToolTip("Skill Matrix Management");
    skillMatrixMgntToolbtn->setIcon(QIcon(":/Images/Images/SkillMatrixMgnt.png"));
    skillMatrixMgntToolbtn->setPopupMode(QToolButton::InstantPopup);
    skillMatrixMgntToolbtn->setEnabled(true); // by default

    connect(displaySkillMatrixToolbtn, SIGNAL(clicked()), this, SLOT(ViewSkillSet()));

    skillMatrixToolbar->addWidget(skillMatrixMgntToolbtn);

    //Action for add and edit skill matrix skills
    addSkillToMatrixAction = new QAction(tr("&Add Skill"),this);
    addSkillToMatrixAction->setStatusTip(tr("Add"));
    addSkillToMatrixAction->setIcon(QIcon(":/Images/Images/add.png"));

    editSkillInMatrixAction = new QAction(tr("&Edit Skill"),this);
    editSkillInMatrixAction->setStatusTip(tr("Edit"));
    editSkillInMatrixAction->setIcon(QIcon(":/Images/Images/edit.png"));

    editSkillInMatrixAction->setEnabled(false); //temporarily disabled

    connect(addSkillToMatrixAction, SIGNAL(triggered(bool)), this, SLOT(AddSkillSlot(bool)));
    //    connect(editSkillInMatrixAction, SIGNAL(clicked(bool)), this, SLOT(EditSkillSlot(bool)));


    skillMatrixMenu->addAction(addSkillToMatrixAction);
    skillMatrixMenu->addAction(editSkillInMatrixAction);

    skillMatrixToolbar->setIconSize(QSize(40,40));

    addToolBar(skillMatrixToolbar);

    qDebug()<< "ToolBar generated";
}

void SkillMatrixDisplay::SetupDockWidgets()
{
    //Training Details
    dockTrainDetails = new QDockWidget(tr("Training Details"), this);
    dockTrainDetails->setWidget(trainingDisplayPtr);

    QDesktopWidget *desktopWid = QApplication::desktop();

    int screenWidth = desktopWid->screenGeometry().width()-16;
    int screenHeight = desktopWid->screenGeometry().height()-50;

    dockTrainDetails->resize(screenWidth/3, screenHeight);

    addDockWidget(Qt::LeftDockWidgetArea, dockTrainDetails);
    QObject::connect(dockTrainDetails, SIGNAL(topLevelChanged ( bool )), SLOT(TrainDetailsDockedSlot(bool)));

    //Individual
    dockIndReport = new QDockWidget(tr("Individual Report"), this);

#ifdef SampleGraphs1
    QPixmap pixmap(":/Images/Images/Individual_Graph_Example.png");
    QLabel *maplabel = new QLabel();
    maplabel->setMinimumSize(1375, 100);
    maplabel->setMaximumSize(1900, 1030);
    maplabel->setPixmap(pixmap);
    dockIndReport->setWidget(maplabel);
#else
    dockIndReport->setMinimumSize(1375, 200);
    dockIndReport->setMaximumSize(1900, 1030);

    individualReportPtr = new IndividualReport(dockIndReport);
    dockIndReport->setWidget(individualReportPtr);
#endif

    dockIndReport->resize(screenWidth/2, screenHeight/3);

    addDockWidget(Qt::RightDockWidgetArea, dockIndReport);
    QObject::connect(dockIndReport, SIGNAL(topLevelChanged ( bool )), SLOT(IndReportDockedSlot(bool)));
    this->centralWidget()->setContentsMargins(0,0,0,0);

    //Team
    dockTeamReport = new QDockWidget(tr("Team Report"), this);

#ifdef SampleGraphs1
    QPixmap pixmap1(":/Images/Images/Team_Graph_Example.png");
    QLabel *maplabel1 = new QLabel();
    maplabel1->setMinimumSize(1375, 100);
    maplabel1->setMaximumSize(1900, 1030);
    maplabel1->setPixmap(pixmap1);
    dockTeamReport->setWidget(maplabel1);
#else
    dockTeamReport->setMinimumSize(1375, 200);
    dockTeamReport->setMaximumSize(1900, 1030);

    teamReportPtr = new TeamReport(dockTeamReport);
    dockTeamReport->setWidget(teamReportPtr);
#endif

    dockTeamReport->resize(screenWidth/2, screenHeight/3);

    addDockWidget(Qt::RightDockWidgetArea, dockTeamReport);
    QObject::connect( dockTeamReport, SIGNAL(topLevelChanged ( bool )), SLOT(TeamReportDockedSlot(bool)) );

    //Dept
    dockDeptReport = new QDockWidget(tr("Department Report"), this);

#ifdef SampleGraphs1
    QPixmap pixmap2(":/Images/Images/Dept_Graph_Example.png");
    QLabel *maplabel2 = new QLabel();
    maplabel2->setMinimumSize(1375, 100);
    maplabel2->setMaximumSize(1900, 1030);
    maplabel2->setPixmap(pixmap2);
    dockDeptReport->setWidget(maplabel2);
#else
    dockDeptReport->setMinimumSize(1375, 200);
    dockDeptReport->setMaximumSize(1900, 1030);

    deptReportPtr = new DeptReport(dockDeptReport);
    dockDeptReport->setWidget(deptReportPtr);
#endif

    dockDeptReport->resize(screenWidth/2, screenHeight/3);

    addDockWidget(Qt::RightDockWidgetArea, dockDeptReport);
    QObject::connect( dockDeptReport, SIGNAL(topLevelChanged ( bool )), SLOT(DeptReportDockedSlot(bool)) );

    qDebug()<< "DockWidgets generated";
}

void SkillMatrixDisplay::IndReportDockedSlot(bool state)
{
    if(state)
    {
        QRect screenres = QApplication::desktop()->screenGeometry();
        dockIndReport->move( QPoint(screenres.x(), screenres.y()) );
        dockIndReport->resize(screenres.width()-20, screenres.height()-80);

#ifndef SampleGraphs1
        individualReportPtr->resizeTabWidget(screenres.width() - 40, screenres.height() - 100);
    }
    else
    {
        individualReportPtr->resizeTabWidgetIntoDock();
        qDebug() << "state is false";
#endif
    }
}

void SkillMatrixDisplay::TeamReportDockedSlot(bool state)
{
    if(state)
    {
        QRect screenres = QApplication::desktop()->screenGeometry();
        dockTeamReport->move( QPoint(screenres.x(), screenres.y()) );
        dockTeamReport->resize(screenres.width()-20, screenres.height()-80);

#ifndef SampleGraphs1
        teamReportPtr->resizeTeamReport(screenres.width() - 40, screenres.height() - 100);
    }
    else
    {
        teamReportPtr->resizeTeamReportIntoDock();
        qDebug() << "state is false";
#endif
    }
}

void SkillMatrixDisplay::DeptReportDockedSlot(bool state)
{
    if(state)
    {
        QRect screenres = QApplication::desktop()->screenGeometry();
        dockDeptReport->move( QPoint(screenres.x(), screenres.y()) );
        dockDeptReport->resize(screenres.width(), screenres.height());

#ifndef SampleGraphs1
        deptReportPtr->resizeDepartmentReport(screenres.width() - 40, screenres.height() - 100);
    }
    else
    {
        deptReportPtr->resizeDepartmentReportIntoDock();
        qDebug() << "state is false";
#endif
    }
}

void SkillMatrixDisplay::TrainDetailsDockedSlot(bool state)
{
    if(state)
    {
        QRect screenres = QApplication::desktop()->screenGeometry();
        dockTrainDetails->move( QPoint(screenres.x(), screenres.y()) );
        dockTrainDetails->resize(screenres.width()-50, screenres.height()-100);
    }
}

void SkillMatrixDisplay::SetupStatusBar()
{
    lblLoggedUser = new QLabel();
    lblLoggedUserType = new QLabel();
    lblStatusDisplay = new QLabel();

    lblLoggedUser->setText( UserInterface::getUserInstance()->GetLoggedInUserName() );
    lblLoggedUserType->setText( UserInterface::getUserInstance()->GetUserType() );
    lblStatusDisplay->setText(""); //default empty string

    statusBar()->addWidget(lblLoggedUser);
    statusBar()->addWidget(lblLoggedUserType);
    statusBar()->addWidget(lblStatusDisplay);

    qDebug()<< "StatusBar generated";
}

void SkillMatrixDisplay::ExitApplSlot()
{
    this->close();
}

void SkillMatrixDisplay::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

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
    Q_UNUSED(state);

    if(!skillMatrixManagementPtr->isActiveWindow())
    {
        skillMatrixManagementPtr->activateWindow();
    }

    skillMatrixManagementPtr->DisplayPrepareSkillSet();
}

void SkillMatrixDisplay::SetAboutInfo()
{
    //About Information Initialized
    NameForHelpDisplay = "Skill Matrix";
    VersionForHelpDisplay = "1.0";
    CopyRightForHelpDisplay = QString::fromLatin1("©2018 Nefit@RBEI");

    //Settings About Information
    aboutSkillMatrixPtr = new AboutSkillMatrix();
    aboutSkillMatrixPtr->SetAboutInfo(NameForHelpDisplay);
    aboutSkillMatrixPtr->SetVersionInfo(VersionForHelpDisplay);
    aboutSkillMatrixPtr->SetCopyRightInfo(CopyRightForHelpDisplay);
}

void SkillMatrixDisplay::LoadAboutSlot()
{
    aboutSkillMatrixPtr->DisplayAboutView();
}
