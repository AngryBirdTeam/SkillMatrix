#include "DeptReport.h"
#include "ui_DeptReport.h"

DeptReport::DeptReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeptReport)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget(this);
    tab = new QWidget(this);
    //TODO : Tab name fetched from spinbox i,e drop down of team list
    tabWidget->addTab(tab , "NEFIT");
    tabWidget->setMinimumHeight(200);
    tabWidget->setMinimumWidth(1008);
    Layout = new QGridLayout(this);
    //TODO : Team Memeber Name must be filled wilth Database , hardcoded for demo
    set0 = new QBarSet("ETP1");
    set1 = new QBarSet("ETP2");
    set2 = new QBarSet("ETP3");
    set3 = new QBarSet("ETP4");
    set4 = new QBarSet("NEFIT");
    series = new QBarSeries();
    chart = new QChart();
    chartView = new QChartView(chart);

    populateDepartmentReport_BarChart();
}

/***************************************************************************
 * Function    : populateTeamReport_BarChart
 * Input       : void
 * output      : void
 * Description : This function reads x and y data from Database and populate
 *               a bar chart
 *
****************************************************************************/
void DeptReport::populateDepartmentReport_BarChart()
{
    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 8 << 20 << 4 << 6 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

//    set0->setColor(Qt::red);
//    set1->setColor(Qt::black);
//    set2->setColor(Qt::magenta);
//    set3->setColor(Qt::yellow);
//    set4->setColor(Qt::blue);
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    chart->addSeries(series);
    chart->setTitle("TEAM REPORT : NEFIT");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    //TODO: Categories (Technologies) to be filled with Database of each Team
    categories << "C" << "C++" << "PYTHON" << "HMI" ;
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setRenderHint(QPainter::Antialiasing);

    Layout->addWidget(chartView);
    tab->setLayout(Layout);
    tabWidget->setCurrentIndex(tabWidget->indexOf(tab));

    this->show();
}

void DeptReport::resizeDepartmentReport(int width , int height)
{
    tabWidget->resize(width , height);
}

void DeptReport::resizeDepartmentReportIntoDock()
{
    tabWidget->resize(1008 , 200);
}

DeptReport::~DeptReport()
{
    delete ui;
}
