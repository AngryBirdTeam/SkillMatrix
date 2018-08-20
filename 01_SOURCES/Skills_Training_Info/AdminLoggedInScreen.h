#ifndef ADMINLOGGEDINSCREEN_H
#define ADMINLOGGEDINSCREEN_H

#include <QDialog>

namespace Ui {
    class AdminLoggedInScreen;
}

class AdminLoggedInScreen : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLoggedInScreen(QWidget *parent = 0);
    ~AdminLoggedInScreen();

private:
    Ui::AdminLoggedInScreen *ui;
    void initialize();

private slots:
    void adminSelection();
    void closeEvent (QCloseEvent *event);
    void enableOKBtn(bool state);

public:
signals:
    void skillMatrixGUI();
    void databaseGUI();
    void empMgntGUI();

};

#endif // ADMINLOGGEDINSCREEN_H
