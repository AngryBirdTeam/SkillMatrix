#ifndef AboutSkillMatrix_H
#define AboutSkillMatrix_H

#include <QWidget>

namespace Ui {
class AboutSkillMatrix;
}

class AboutSkillMatrix : public QWidget
{
    Q_OBJECT

public:
    explicit AboutSkillMatrix(QWidget *parent = 0);
    ~AboutSkillMatrix();

    void SetAboutInfo(QString AboutStr);
    void SetVersionInfo(QString VersionStr);
    void SetCopyRightInfo(QString CopyRightStr);

    void DisplayAboutView();

private:
    Ui::AboutSkillMatrix *ui;
};

#endif // AboutSkillMatrix_H
