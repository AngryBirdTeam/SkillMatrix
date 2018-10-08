#ifndef INDIVIDUALREPORT_H
#define INDIVIDUALREPORT_H

#include <QWidget>
#include <QTabWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QGridLayout>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class IndividualReport;
}

class IndividualReport : public QWidget
{
    Q_OBJECT

public:
    explicit IndividualReport(QWidget *parent = nullptr);
    void dispBarChart();
    void resizeTabWidget(int width , int height);
    void resizeTabWidgetIntoDock();

    ~IndividualReport();

private:
    Ui::IndividualReport *ui;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *Layout;

};

#endif // INDIVIDUALREPORT_H
