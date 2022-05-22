#ifndef STATCHART_H
#define STATCHART_H

#include <QWidget>
#include <QGridLayout>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

class PenTool;
class BrushTool;
class CustomSlice;

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QPieSeries;
class QPieSlice;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class StatChart : public QWidget
{
        Q_OBJECT
    public:
        explicit StatChart(QWidget *parent = nullptr);

    signals:

    private:
        QChartView *m_chartView;
        QPieSeries *m_series;
        QPieSlice *m_slice;

};

#endif // STATCHART_H
