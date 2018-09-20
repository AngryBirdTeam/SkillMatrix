#ifndef SKILLMATRIXDISPLAY_H
#define SKILLMATRIXDISPLAY_H

#include <QMainWindow>
#include <QMenu>
#include <QToolButton>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QLabel>

#include "AboutSkillMatrix.h"
#include "SkillMatrixManagement.h"
#include "SkillGroupManagement.h"
#include "TrainingDisplay.h"
#include "UserCreation.h"
#include "UserDetails.h"

namespace Ui {
class SkillMatrixDisplay;
}

class SkillMatrixDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit SkillMatrixDisplay(QWidget *parent = 0);
    ~SkillMatrixDisplay();

    UserDetails *userDetailsPtr;
    void UpdateGUIBasedOnLoggedUser();

private slots:
    void ExitApplSlot();
    void closeEvent (QCloseEvent *event);

    void DisplayUserDetails();
    void NewUserSlot();
    void EditUserSlot();
    void ViewSkillSet();
    void LoadAboutSlot();
    void AddSkillSlot(bool state);

    void TrainDetailsDockedSlot(bool state);
    void IndReportDockedSlot(bool state);
    void TeamReportDockedSlot(bool state);
    void DeptReportDockedSlot(bool state);

    void resizeEvent(QResizeEvent *event);

private:
    Ui::SkillMatrixDisplay *ui;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *userMenu;
    QMenu *userMgnt;
    QMenu *helpMenu;

    QAction *exitAction;
    QAction *viewSkillSetAction;
    QAction *userDetailsAction;
    QAction *newUserAction;
    QAction *editUserAction;
    QAction *aboutAction;
    QAction *addSkillToGrpAction;
    QAction *editSkillGrpAction;
    QAction *addSkillToMatrixAction;
    QAction *editSkillInMatrixAction;

    QToolBar *userMgntToolbar;
    QToolBar *skillGroupToolbar;
    QToolBar *skillMatrixToolbar;

    QToolButton *newUserToolbtn;
    QToolButton *editUserToolbtn;
    QToolButton *skillGroupToolbtn;
    QToolButton *displaySkillMatrixToolbtn;
    QToolButton *skillMatrixMgntToolbtn;

    QMenu *userMgntMenu;
    QMenu *skillGrpMenu;
    QMenu *skillMatrixMenu;

    QAction *newUserToolbtnAction;
    QAction *editUserToolbtnAction;

    QDockWidget *dockTrainDetails;
    QDockWidget *dockIndReport;
    QDockWidget *dockTeamReport;
    QDockWidget *dockDeptReport;

    QLabel *lblLoggedUser;
    QLabel *lblLoggedUserType;
    QLabel *lblStatusDisplay;
	
    QString NameForHelpDisplay;
    QString VersionForHelpDisplay;
    QString CopyRightForHelpDisplay;

    AboutSkillMatrix *aboutSkillMatrixPtr;
    UserCreation *userCreationPtr;
    SkillMatrixManagement *skillMatrixManagementPtr;
    SkillGroupManagement *skillGroupManagementPtr;
    TrainingDisplay *trainingDisplayPtr;

    void Init();
    void CreateWidgets();
    void SetupMenuBar();
    void SetupToolBar();
    void SetupDockWidgets();
    void SetupStatusBar();
    void SetAboutInfo();

};

#endif // MAINDISPLAY_H
