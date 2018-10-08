#ifndef DRILLDOWNCHART_H
#define DRILLDOWNCHART_H

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QAbstractSeries;
class QPieSlice;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class drilldownchart : public QChart
{
    Q_OBJECT
public:
    explicit drilldownchart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~drilldownchart();
    void changeSeries(QAbstractSeries *series);

public Q_SLOTS:
    void handleSliceClicked(QPieSlice *slice);

private:
    QAbstractSeries *m_currentSeries;
};

#endif // DRILLDOWNCHART_H
