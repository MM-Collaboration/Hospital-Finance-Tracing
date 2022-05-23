#include "statchart.h"

QT_CHARTS_USE_NAMESPACE

StatChart::StatChart(QWidget *parent)
    : QWidget{parent}
{
    m_slice = nullptr;

    // create series
    m_series = new QPieSeries();
    m_series->append("Нет данных", 1);
    m_series->setLabelsVisible();

//    m_slice = new QPieSlice();
//    m_slice = m_series->slices().at(1);
//    m_slice->setExploded();
//    m_slice->setLabelVisible();
//    m_slice->setPen(QPen(Qt::darkGray, 2));
//    m_slice->setBrush(Qt::green);

    // create chart
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->setTitle("Doctors statistic");
    m_chart->setAnimationOptions(QChart::AllAnimations);
    m_chart->legend()->setAlignment(Qt::AlignRight);

    // create chart view
    m_chartView = new QChartView(m_chart);

    // create main layout
    QGridLayout *baseLayout = new QGridLayout();
    baseLayout->addWidget(m_chartView, 1, 2);
    setLayout(baseLayout);
}

void StatChart::loadSeries(QPieSeries *series) {
    m_series = series;
    m_chart->removeAllSeries();
    m_chart->addSeries(series);
}
