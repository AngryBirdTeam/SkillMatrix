#include "TrainingDisplay.h"
#include "ui_TrainingDisplay.h"

TrainingDisplay::TrainingDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingDisplay)
{
    ui->setupUi(this);
}

TrainingDisplay::~TrainingDisplay()
{
    delete ui;
}
