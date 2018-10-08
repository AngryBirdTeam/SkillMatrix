#include "drilldownchart.h"
#include "drilldownslice.h"

QT_CHARTS_USE_NAMESPACE

drilldownchart::drilldownchart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags),
      m_currentSeries(0)
{

}

drilldownchart::~drilldownchart()
{

}

void drilldownchart::changeSeries(QAbstractSeries *series)
{
    // NOTE: if the series is owned by the chart it will be deleted
    // here the "window" owns the series...
    if (m_currentSeries)
        removeSeries(m_currentSeries);
    m_currentSeries = series;
    addSeries(series);
    setTitle(series->name());
}

void drilldownchart::handleSliceClicked(QPieSlice *slice)
{
    drilldownslice *drilldownSlice = static_cast<drilldownslice *>(slice);
    changeSeries(drilldownSlice->drilldownSeries());
}

#include "moc_drilldownchart.cpp"
