#ifndef DBMANAGEMENT_H
#define DBMANAGEMENT_H

#include <QDialog>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>

#include "DisplayInfo.h"

namespace Ui {
    class DBManagement;
}

class DBManagement : public QDialog
{
    Q_OBJECT

public:
    explicit DBManagement(QWidget *parent = 0);
    ~DBManagement();

private:
    Ui::DBManagement *ui;
    QString BackupFile;
    QString RestoreFile;
    QMessageBox msg;
    QString filename;
    QSqlQuery queryBackup;

    DisplayInfo *displayInfoPointer;

private slots:
    void DBBackupBrowse();
    void DBRestoreBrowse();
    void DBBackUp();
    void DBRestore();
    void truncateTables();

};

#endif // DBMANAGEMENT_H
