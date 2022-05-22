#include "statchart.h"

QT_CHARTS_USE_NAMESPACE

StatChart::StatChart(QWidget *parent)
    : QWidget{parent}
{
    m_slice = nullptr;

    // create series
    m_series = new QPieSeries();
    m_series->append("Hello", 1);
    m_series->append("ASD", 2);
    m_series->append("aASDASDA", 3);
    m_series->append("NoOtherWay", 4);
    m_series->append("Dark_Side", 5);
    m_series->setLabelsVisible();

    m_slice = new QPieSlice();
//    m_slice = m_series->slices().at(1);
//    m_slice->setExploded();
//    m_slice->setLabelVisible();
//    m_slice->setPen(QPen(Qt::darkGray, 2));
//    m_slice->setBrush(Qt::green);

    // create chart
    QChart *chart = new QChart;
    chart->addSeries(m_series);
    chart->setTitle("Doctors statistic");
    chart->setAnimationOptions(QChart::AllAnimations);

    // create chart view
    m_chartView = new QChartView(chart);

    // create main layout
    QGridLayout *baseLayout = new QGridLayout();
    baseLayout->addWidget(m_chartView, 1, 2);
    setLayout(baseLayout);
}
