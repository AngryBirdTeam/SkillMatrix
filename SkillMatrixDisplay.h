#ifndef SKILLMATRIXDISPLAY_H
#define SKILLMATRIXDISPLAY_H

#include <QMainWindow>
#include <QMenu>
#include <QToolButton>

#include "UserDetails.h"
#include "UserCreation.h"
#include "SkillMatrixManagement.h"

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

    void AddSkillSlot(bool state);

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

    QToolBar *userMgntToolbar;
    QToolBar *skillMatrixToolbar;

    QToolButton *newUserToolbtn;
    QToolButton *editUserToolbtn;
    QToolButton *displaySkillMatrixToolbtn;
    QToolButton *addSkillToMatrixToolbtn;
    QToolButton *editSkillInMatrixToolbtn;

    QMenu *UserMgntMenu;
    QAction *newUserToolbtnAction;
    QAction *editUserToolbtnAction;

    UserCreation *userCreationPtr;
    SkillMatrixManagement *skillMatrixManagementPtr;

    void Init();
    void SetupMenuBar();
    void SetupToolBar();
};

#endif // MAINDISPLAY_H
