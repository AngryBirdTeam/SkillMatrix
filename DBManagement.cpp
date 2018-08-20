#include "DBManagement.h"
#include "ui_DBManagement.h"

#include "UserInterface.h"

DBManagement::DBManagement(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DBManagement)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    connect(ui->Btn_BrowseSavePath,SIGNAL(clicked()),this,SLOT(DBBackupBrowse()));
    connect(ui->Btn_BrowseOpenPath,SIGNAL(clicked()),this,SLOT(DBRestoreBrowse()));
    connect(ui->BTN_BACKUP,SIGNAL(clicked()),this,SLOT(DBBackUp()));
    connect(ui->btn_restore,SIGNAL(clicked()),this,SLOT(DBRestore()));

    displayInfoPointer = DisplayInfo::getInstance();

    queryBackup.exec("select * from tbl_backup_details");

    int i = 0;
//    ui->tbl_backup->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tbl_backup->setRowCount(0);

    while(queryBackup.next())
    {
        ui->tbl_backup->insertRow(i);
        ui->tbl_backup->setItem(i,0,new QTableWidgetItem(queryBackup.value(0).toString()));
        ui->tbl_backup->setItem(i,1,new QTableWidgetItem(queryBackup.value(1).toString()));
        ui->tbl_backup->setItem(i,2,new QTableWidgetItem(queryBackup.value(2).toString()));
        ui->tbl_backup->setItem(i,3,new QTableWidgetItem(queryBackup.value(3).toString()));
    }
}

void DBManagement::DBBackupBrowse()
{
    BackupFile = QFileDialog::getSaveFileName(this,tr("Save Config"),QDir::currentPath(),"SQL(*.sql)");
    QFileInfo file(BackupFile);
    QString ext = file.completeSuffix();

    if(BackupFile != "")
    {
        if(ext != "")
        {
            BackupFile = BackupFile.remove(ext) + "sql";
        }
        else
        {
            BackupFile = BackupFile + ".sql";
        }

        QFileInfo file1(BackupFile);
        filename = file1.fileName();

        ui->le_SaveFilePath->setText(BackupFile);
    }
}

void DBManagement::DBRestoreBrowse()
{
    RestoreFile = QFileDialog::getOpenFileName(this, tr("Open Config"), QDir::currentPath(), "SQL(*.sql)");

    ui->le_OpenFilePath->setText(RestoreFile);
}

void DBManagement::DBBackUp()
{
    QString backupVersion;

    if(ui->le_SaveFilePath->text() == "")
    {
        msg.setText("Please Enter Valid Path");
        msg.exec();
    }
    else
    {
        QProcess dumpProcess;
        QStringList args;
        args << "--user=root" << "--password=password" << "--host=localhost"<<"skills";

        dumpProcess.setStandardOutputFile(BackupFile);
        dumpProcess.start("C:/Program Files (x86)/MySQL/MySQL Server 5.0/bin/mysqldump", args);

        bool backupStatus = dumpProcess.waitForFinished();

        if(backupStatus == true)
        {
            QFile dumpFile(BackupFile);
            dumpFile.open(QIODevice::ReadWrite);

            QTextStream in (&dumpFile);
            const QString dumpFilecontent = in.readAll();

            if(dumpFilecontent.contains("-- Dump completed"))
            {
                queryBackup.exec("update skills.tbl_backup_record "
                                 "set fld_backup_status=1");

                queryBackup.exec("select fld_software from skills.tbl_backup_record");

                if(queryBackup.next())
                {
                    backupVersion = queryBackup.value(0).toString();
                }

                QString strQuery = "insert into ";
                strQuery += "tbl_backup_details";
                strQuery += " (fld_db_version, fld_user_name, fld_path, fld_filename)";
                strQuery += " values (";
                strQuery += "'";
                strQuery += backupVersion;
                strQuery += "', ";
                strQuery += "'";
                strQuery += UserInterface::getUserInstance()->GetLoggedInUserName();
                strQuery += "', ";
                strQuery += "'";
                strQuery += BackupFile;
                strQuery += "', ";
                strQuery += "'";
                strQuery += filename;
                strQuery += "')";

                if(!queryBackup.exec(strQuery))
                {
                    displayInfoPointer->DisplayMessage(queryBackup.lastQuery(), DisplayInfo::MessageType::Error);
                }

                int i = 0;

                queryBackup.exec("select * from skills.tbl_backup_details");

                ui->tbl_backup->setRowCount(0);

                while(queryBackup.next())
                {
                    ui->tbl_backup->insertRow(i);
                    ui->tbl_backup->setItem(i,0,new QTableWidgetItem(queryBackup.value(0).toString()));
                    ui->tbl_backup->setItem(i,1,new QTableWidgetItem(queryBackup.value(1).toString()));
                    ui->tbl_backup->setItem(i,2,new QTableWidgetItem(queryBackup.value(2).toString()));
                    ui->tbl_backup->setItem(i,3,new QTableWidgetItem(queryBackup.value(3).toString()));
                }

                msg.setText("Back up DONE");
                msg.setIcon(QMessageBox::Information);
                msg.exec();
            }
            else
            {
                msg.setText("Backup could not complete ");
                msg.setIcon(QMessageBox::Critical);
                msg.exec();
            }
        }
        else
        {
            msg.setText("Backup FAILED "+dumpProcess.errorString());
            msg.setIcon(QMessageBox::Critical);
            msg.exec();
        }
    }
}

void DBManagement::DBRestore()
{
    int restore = 0;
    int restoreSuccessFile = 0;
    int restoreFailFile = 0;
    int failureCount = 0;

    QString queryFail="FAILED TO RESTORE: ";
    QString querySuccess="SUCCESS!! RESTORED: ";

    if(ui->le_OpenFilePath->text().endsWith(".sql"))
    {
        QSqlQuery queryDB1,queryDB2;
        float DB1version = 0.0;
        float DB2version = 0.0;

        queryBackup.exec("select fld_backup_status from skills.tbl_backup_record");

        while(queryBackup.next())
        {
            if(queryBackup.value(0)==0)
            {
                QMessageBox msgBox;
                msgBox.setText("Current Database Backup is not taken\nDo you want to continue anyway?");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                int ret = msgBox.exec();

                switch (ret)
                {
                case QMessageBox::Yes:
                    restore = 1;
                    break;
                case QMessageBox::No:
                    break;
                default:
                    // should never be reached
                    break;
                }
            }
            else
            {
                restore = 1;
            }
        }

        do
        {
            if(restore==1 && failureCount<3)
            {
                QSqlQuery query;
                QString debugDB1String;
                QString debugDB2String;

                query.exec("drop database skillsrestore");

                if(query.exec("Create database skillsrestore"))
                {
                    //restore skills DB to skillsrestore DB
                    QProcess dumpProcess;
                    QStringList args;
                    args << "--user=root" << "--password=password" << "skillsrestore";
                    dumpProcess.setStandardInputFile(RestoreFile);
                    dumpProcess.start("C:/Program Files (x86)/MySQL/MySQL Server 5.0/bin/mysql", args);
                    dumpProcess.waitForFinished();

                    queryDB1.exec("select fld_database from skills.tbl_backup_record");

                    if(queryDB1.next())
                    {
                        DB1version = queryDB1.value(0).toString().toFloat();
                    }

                    queryDB2.exec("select fld_database from skillsrestore.tbl_backup_record");

                    if(queryDB2.next())
                    {
                        DB2version = queryDB2.value(0).toString().toFloat();
                    }

                    if(DB1version >= DB2version)
                    {
                        QSqlQuery queryTables;
                        queryTables.exec("set foreign_key_checks = 0");

                        truncateTables();

                        if(queryTables.exec("use skillsrestore"))
                        {
                            queryTables.exec("show tables");

                            while(queryTables.next())
                            {
                                if(queryTables.value(0).toString()!="tbl_backup_record"
                                   && queryTables.value(0).toString()!="tbl_backup_details"
                                   && queryTables.value(0).toString()!="tbl_user")
                                {
                                    QSqlQuery queryFields;
                                    QList<QString> db1FieldString;
                                    QList<QString> db2FieldString;
                                    QString dbFieldString = "";
                                    debugDB1String = "explain skills."+queryTables.value(0).toString();
                                    debugDB2String = "explain skillsrestore."+queryTables.value(0).toString();

                                    queryFields.exec(debugDB1String);

                                    while(queryFields.next())
                                    {
                                        db1FieldString.append(queryFields.value(0).toString());
                                    }
                                    \
                                    queryFields.exec(debugDB2String);

                                    while(queryFields.next())
                                    {
                                        db2FieldString.append(queryFields.value(0).toString());
                                    }

                                    for(int i=0;i<db1FieldString.length();i++)
                                    {
                                        if(db2FieldString.contains(db1FieldString.at(i)))
                                        {
                                            dbFieldString = dbFieldString + db1FieldString.at(i)+",";
                                        }
                                    }

                                    dbFieldString = dbFieldString.remove(dbFieldString.length()-1,dbFieldString.length());
                                    QString queryString = "insert into skills."+queryTables.value(0).toString()+"("+dbFieldString+")select  "+dbFieldString+" from skillsrestore."+queryTables.value(0).toString()+" union all "+"select "+dbFieldString+" from skills."+queryTables.value(0).toString();

                                    QSqlQuery queryMerge;
                                    qDebug()<<queryString;

                                    if(queryMerge.exec(queryString))
                                    {
                                        restoreSuccessFile++;
                                        qDebug()<<queryTables.value(0).toString()<<"SUCCESS";
                                        querySuccess = querySuccess + "\n"+queryTables.value(0).toString();
                                    }
                                    else
                                    {
                                        restoreFailFile++ ;
                                        qDebug()<<queryTables.value(0).toString()<<"FAIL";
                                        queryFail = queryFail + "\n"+queryTables.value(0).toString();
                                    }
                                }
                            }

                            if(restoreSuccessFile>=1)
                            {
                                msg.setText("Restore DONE\n");
                                msg.exec();
                            }
                        }
                        else
                        {
                            failureCount++;
                            break;
                        }

                        queryTables.exec("set foreign_key_checks = 1");

                        queryTables.exec("drop database skillsrestore");

                        queryTables.exec("use comint");

                    }
                    else
                    {
                        msg.setText("Current Database Version is lower than the Backup Version");
                        msg.setIcon(QMessageBox::Critical);
                        msg.exec();
                    }
                }
                else
                {
                    failureCount++;
                    break;
                }
            }
            else
            {
                msg.setText("Restore failed: "+QString::number(failureCount)+" time(s): Database table not found");
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        }while(failureCount>=1 && failureCount<=3);
    }
    else
    {
        msg.setText("Select Valid File");
        msg.exec();
    }
}

void DBManagement::truncateTables()
{
    QSqlQuery queryTruncate;
    queryTruncate.exec("SELECT Concat('TRUNCATE TABLE ',table_schema,'.',TABLE_NAME, ';')FROM INFORMATION_SCHEMA.TABLES where table_schema in ('skillsrestore')");

    while(queryTruncate.next())
    {
        QString queryStr;
        queryStr= queryTruncate.value(0).toString().replace("skillsrestore","skills");
        if(!queryStr.contains("tbl_backup_record;")
            && !queryStr.contains("tbl_backup_details;") && !queryStr.contains("tbl_user;"))
            {
            QSqlQuery truncateTable;

            if(!truncateTable.exec(queryStr))
            {
                displayInfoPointer->DisplayMessage(truncateTable.lastQuery(), DisplayInfo::MessageType::Error);
            }
        }
    }
}

DBManagement::~DBManagement()
{
    delete ui;
}
