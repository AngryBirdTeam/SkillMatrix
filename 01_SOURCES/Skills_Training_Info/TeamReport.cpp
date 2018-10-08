#include "TeamReport.h"
#include "ui_TeamReport.h"

#include <QtCharts/QPieSeries>

TeamReport::TeamReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamReport)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget(this);
    tab = new QWidget(this);
    tab1 = new QWidget(this);
    //TODO : Tab name fetched from spinbox i,e drop down of team list
    tabWidget->addTab(tab , "NEFIT");
    tabWidget->addTab(tab1 , "NEFIT- Detailed Report");
    tabWidget->setMinimumHeight(200);
    tabWidget->setMinimumWidth(1008);
    Layout = new QGridLayout(this);
    tab1Layout = new QGridLayout(this);
    //TODO : Team Memeber Name must be filled wilth Database , hardcoded for demo
    set0 = new QBarSet("Rajeev");
    set1 = new QBarSet("Nikhil");
    set2 = new QBarSet("Aiyush");
    set3 = new QBarSet("Vidya");
    set4 = new QBarSet("Princy");
    series = new QBarSeries();
    chart = new QChart();
    chartView = new QChartView(chart);
    populateTeamReport_BarChart();
    populateTeamReport_PieChart();
}

/***************************************************************************
 * Function    : populateTeamReport_BarChart
 * Input       : void
 * output      : void
 * Description : This function reads x and y data from Database and populate
 *               a bar chart
 *
****************************************************************************/
void TeamReport::populateTeamReport_BarChart()
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
    categories << "C" << "C++" << "PYTHON" << "ROBO_FRAMEWORK" << "DEVOP'S" << "LINUX";
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

void TeamReport::resizeTeamReport(int width , int height)
{
    tabWidget->resize(width , height);
}

void TeamReport::resizeTeamReportIntoDock()
{
    tabWidget->resize(1008 , 200);
}

/***************************************************************************
 * Function    : populateTeamReport_PieChart
 * Input       : void
 * output      : void
 * Description : This function reads x and y data from Database and populate
 *               a bar chart
 *
****************************************************************************/
void TeamReport::populateTeamReport_PieChart()
{

    drilldownchart *chart = new drilldownchart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *yearSeries = new QPieSeries(tab1);
    yearSeries->setName("YEAR PERFORMANCE FOR NEFIT TEAM : 2017");

    QList<QString> months;
    months << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    QList<QString> names;
    names << "Rajeev" << "Nikhil" << "Aiyush" << "Princy" << "Vidya" ;

    foreach (QString name, names) {
        QPieSeries *series = new QPieSeries(tab1);
        series->setName("Preformance of : " + name + " for Year 2017" );

        foreach (QString month, months)
        *series << new drilldownslice(qrand() % 1000, month, yearSeries);

        QObject::connect(series, SIGNAL(clicked(QPieSlice*)), chart, SLOT(handleSliceClicked(QPieSlice*)));

        *yearSeries << new drilldownslice(series->sum(), name, series);
    }

    QObject::connect(yearSeries, SIGNAL(clicked(QPieSlice*)), chart, SLOT(handleSliceClicked(QPieSlice*)));

    chart->changeSeries(yearSeries);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    tab1Layout->addWidget(chartView);
    tab1->setLayout(tab1Layout);
    tabWidget->setCurrentIndex(tabWidget->indexOf(tab1));
    this->show();
}

TeamReport::~TeamReport()
{
    delete ui;
}
