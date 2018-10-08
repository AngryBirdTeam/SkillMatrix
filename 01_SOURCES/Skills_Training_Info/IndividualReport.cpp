#include "IndividualReport.h"
#include "ui_IndividualReport.h"
#include <QDebug>

IndividualReport::IndividualReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndividualReport)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget(this);
    tab = new QWidget(this);

    tabWidget->addTab(tab , "Individual User");
    tabWidget->setMinimumHeight(200);
    tabWidget->setMinimumWidth(1008);

    Layout = new QGridLayout(this);

    qDebug()<< "individual report constructor";

    dispBarChart();
}

/***************************************************************************
 * Function    : dispBarChart
 * Input       : void
 * output      : void
 * Description : This function reads x and y data from Database and populate
 *               a bar chart
 *
****************************************************************************/
void IndividualReport::dispBarChart()
{
    QBarSet *set0 = new QBarSet("Individual_Name");
    QBarSet *set1 = new QBarSet("Humidity Alarm");
    QStringList categories;

    QString strQuery="";
    strQuery = "SELECT * from user_report ";
//    strQuery += LoginUser;
//    strQuery += "'";
    //QSqlQuery query;

    //if(!query.exec(strQuery))
       // qDebug()<<"ERROR = "<<query.lastQuery();

    //query.next();


    *set0 << 10 << 20 << 40 << 30 << 80 << 60 << 70 <<  90 << 100;
    *set1 << 5 << 10 << 20 << 4 << 40 << 7;

//![1]

//![2]
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);


//![2]

//![3]
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]
    categories << "C" << "C++" << "Python" << "Java" << "MongoDB" << "DevOps";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
//![4]

//![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

//![7]
    Layout->addWidget(chartView);
    tab->setLayout(Layout);
    tabWidget->setCurrentIndex(tabWidget->indexOf(tab));

    this->show();
}

void IndividualReport::resizeTabWidget(int width , int height)
{
    tabWidget->resize(width , height);
}

void IndividualReport::resizeTabWidgetIntoDock()
{
    tabWidget->resize(1375 , 200);
}

IndividualReport::~IndividualReport()
{
    delete ui;
}
