#ifndef USERDETAILS_H
#define USERDETAILS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "UserInterface.h"

namespace Ui {
    class UserDetails;
}

class UserDetails : public QWidget
{
    Q_OBJECT

public:
    explicit UserDetails(QWidget *parent = 0);
    ~UserDetails();

    void UpdateUserDetails();

    Ui::UserDetails *ui;

public slots:
    void slotUpdateUserDetails(QString);

private:
    QMessageBox PopUpMsg;

private slots:
    void SlotChangePassword(bool);
    void Save();
    void CloseWindow();

};

#endif // USERDETAILS_H
