#ifndef DISPLAYUPDATESKILLS_H
#define DISPLAYUPDATESKILLS_H

#include <QDialog>

namespace Ui {
class DisplayUpdateSkills;
}

class DisplayUpdateSkills : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayUpdateSkills(QWidget *parent = 0);
    ~DisplayUpdateSkills();

private:
    Ui::DisplayUpdateSkills *ui;
};

#endif // DISPLAYUPDATESKILLS_H
