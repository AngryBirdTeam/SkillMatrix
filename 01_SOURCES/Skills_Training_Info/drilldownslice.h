#ifndef DRILLDOWNSLICE_H
#define DRILLDOWNSLICE_H

#include <QtCharts/QPieSlice>

QT_CHARTS_BEGIN_NAMESPACE
class QAbstractSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class drilldownslice : public QPieSlice
{
    Q_OBJECT

public:
    drilldownslice(qreal value, QString prefix, QAbstractSeries *drilldownSeries);
    virtual ~drilldownslice();
    QAbstractSeries *drilldownSeries() const;

public Q_SLOTS:
    void updateLabel();
    void showHighlight(bool show);

private:
    QAbstractSeries *m_drilldownSeries;
    QString m_prefix;
};

#endif // DRILLDOWNSLICE_H
