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

    int learningPlanTblColCount;
    int learningHistoryTblColCount;

    void Init();
    void DisableTables();
    void ShowLearningPlan(QString);
    void ShowLearningHistory(QString);
};

#endif // TRAININGDISPLAY_H
