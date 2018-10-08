#include "drilldownslice.h"

QT_CHARTS_USE_NAMESPACE

drilldownslice::drilldownslice(qreal value, QString prefix, QAbstractSeries *drilldownSeries)
    : m_drilldownSeries(drilldownSeries),
      m_prefix(prefix)
{
    setValue(value);
    updateLabel();
    setLabelFont(QFont("Arial", 8));
    connect(this, SIGNAL(percentageChanged()), this, SLOT(updateLabel()));
    connect(this, SIGNAL(hovered(bool)), this, SLOT(showHighlight(bool)));
}

drilldownslice::~drilldownslice()
{

}

QAbstractSeries *drilldownslice::drilldownSeries() const
{
    return m_drilldownSeries;
}

void drilldownslice::updateLabel()
{
    QString label = m_prefix;
    label += " $";
    label += QString::number(this->value());
    label += ", ";
    label += QString::number(this->percentage() * 100, 'f', 1);
    label += "%";
    setLabel(label);
}

void drilldownslice::showHighlight(bool show)
{
    setLabelVisible(show);
    setExploded(show);
}

#include "moc_drilldownslice.cpp"
