#ifndef DEPTREPORT_H
#define DEPTREPORT_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class DeptReport;
}

class DeptReport : public QWidget
{
    Q_OBJECT

public:
    explicit DeptReport(QWidget *parent = nullptr);
    void populateDepartmentReport_BarChart(void);
    void resizeDepartmentReport(int width , int height);
    void resizeDepartmentReportIntoDock();

    ~DeptReport();

private:
    Ui::DeptReport *ui;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *Layout;
    QBarSet *set0 ;
    QBarSet *set1 ;
    QBarSet *set2 ;
    QBarSet *set3 ;
    QBarSet *set4 ;
    QBarSeries *series;
    QChart *chart;
    QChartView *chartView;
};

#endif // DEPTREPORT_H
