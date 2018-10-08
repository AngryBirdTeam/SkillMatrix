#ifndef TEAMREPORT_H
#define TEAMREPORT_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QTabWidget>
#include <QGridLayout>
#include "drilldownchart.h"
#include "drilldownslice.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class TeamReport;
}

class TeamReport : public QWidget
{
    Q_OBJECT

public:
    explicit TeamReport(QWidget *parent = nullptr);
    void populateTeamReport_BarChart(void);
    void populateTeamReport_PieChart(void);
    void resizeTeamReport(int width , int height);
    void resizeTeamReportIntoDock();
    ~TeamReport();

private:
    Ui::TeamReport *ui;
    QBarSet *set0 ;
    QBarSet *set1 ;
    QBarSet *set2 ;
    QBarSet *set3 ;
    QBarSet *set4 ;
    QBarSeries *series;
    QChart *chart;
    QChartView *chartView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab1;
    QGridLayout *Layout;
    QGridLayout *tab1Layout;
};

#endif // TEAMREPORT_H
