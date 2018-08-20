#ifndef EMPLOYEEMANAGEMENT_H
#define EMPLOYEEMANAGEMENT_H

#include <QDialog>

namespace Ui {
class EmployeeManagement;
}

class EmployeeManagement : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeManagement(QWidget *parent = 0);
    ~EmployeeManagement();

private:
    Ui::EmployeeManagement *ui;
};

#endif // EMPLOYEEMANAGEMENT_H
