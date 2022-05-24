#include "statchart.h"

QT_CHARTS_USE_NAMESPACE

StatChart::StatChart(QWidget *parent, QString *title)
    : QWidget{parent}
{
//    // create series
//    m_pieSeries = new QPieSeries();
//    m_pieSeries->append("Нет данных", 1);
//    m_pieSeries->setLabelsVisible();

    // create chart
    m_chart = new QChart();
//    m_chart->addSeries(m_pieSeries);
    m_chart->setTitle(*title);
    m_chart->setAnimationOptions(QChart::AllAnimations);
    m_chart->legend()->setAlignment(Qt::AlignRight);

    // create chart view
    m_chartView = new QChartView(m_chart);
    m_chartView->chart()->legend()->setFont(QFont("Arial", 12));
    m_chartView->setRenderHint(QPainter::Antialiasing);

    // create main layout
    QGridLayout *baseLayout = new QGridLayout();
    baseLayout->addWidget(m_chartView, 1, 2);
    setLayout(baseLayout);
}

void StatChart::loadSeries(QAbstractSeries *series) {
    m_series = series;
    m_chart->removeAllSeries();
    m_chart->addSeries(series);
}

void StatChart::loadSeries(QLineSeries *series) {
    m_series = series;
    m_chart->legend()->hide();
    m_chart->removeAllSeries();
    m_chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Дата");
    axisX->setLabelFormat("%i");
//    axisX->setTickCount(3);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setTitleText("Цена");
    axisY->setLabelFormat("%g");
    axisY->setBase(80.0);
    axisY->setMinorTickCount(-1);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_chartView->setRenderHint(QPainter::Antialiasing);
}
