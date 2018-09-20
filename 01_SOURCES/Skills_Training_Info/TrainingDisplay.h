#ifndef TRAININGDISPLAY_H
#define TRAININGDISPLAY_H

#include <QDialog>

namespace Ui {
class TrainingDisplay;
}

class TrainingDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingDisplay(QWidget *parent = nullptr);
    ~TrainingDisplay();

private:
    Ui::TrainingDisplay *ui;
};

#endif // TRAININGDISPLAY_H
