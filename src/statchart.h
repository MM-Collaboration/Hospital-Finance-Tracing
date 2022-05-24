#ifndef STATCHART_H
#define STATCHART_H

#include <QWidget>
#include <QGridLayout>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>

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
        explicit StatChart(QWidget *parent = nullptr, QString *title = nullptr);

        void loadSeries(QAbstractSeries *);
        void loadSeries(QLineSeries *);

        struct Pie_t {
            QString name;
            float value;
        };

    signals:

    private:
        QChartView *m_chartView;
        QAbstractSeries *m_series;
        QChart *m_chart;

};

#endif // STATCHART_H
