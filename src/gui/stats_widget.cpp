#include "stats_widget.h"

#include <QChart>
#include <QVBoxLayout>
#include <QBarSet>
#include <QStackedBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QDialogButtonBox>
#include <QColor>

typedef std::map<std::string, QColor> ColorMap;
const ColorMap COLORS = {
    { "RED", QColor(214, 39, 40) },
    { "GREEN", QColor(44, 160, 44) },
    { "BLUE", QColor(31, 119, 180) },
    { "YELLOW", QColor(255, 196, 0) },
    { "ORANGE", QColor(255, 127, 14) },
    { "PURPLE", QColor(148, 103, 189) },
    { "BLACK", QColor(26, 26, 26) },
};

const QString CHART_TITLE("Trenchcoat Size/Color Trends (Quantities)");
const QSize WIDGET_SIZE(600, 600); 

std::map<std::string, unsigned int> StatsWidget::getStocks(const std::string& color) const {
    std::map<std::string, unsigned int> stocks;

    for (const auto& size : TRENCHCOAT_SIZES) {
        stocks[size] = 0;

        for (const auto& coat : data)
            if (coat.color() == color && coat.size() == size)
                stocks[size] += coat.quantity();
    }

    return stocks;
}

StatsWidget::StatsWidget(const std::vector<Trenchcoat>& data, QWidget *parent) 
    : QDialog(parent), data(data) {

    std::map<std::string, QtCharts::QBarSet *> barSets;

    for (const auto& color : TRENCHCOAT_COLORS) {
        barSets[color] = new QtCharts::QBarSet(QString::fromStdString(color));

        barSets[color]->setColor(COLORS.at(color));

        auto stocks = getStocks(color);

        for (const auto& size : TRENCHCOAT_SIZES)
            barSets[color]->append(stocks[size]);
    }

    QtCharts::QStackedBarSeries *series = new QtCharts::QStackedBarSeries();

    for (const auto& set : barSets) 
        series->append(set.second);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle(CHART_TITLE);
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QStringList categories;
    for (const auto& size : TRENCHCOAT_SIZES)
        categories << QString::fromStdString(size);

    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &StatsWidget::accept);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    layout->addWidget(buttonBox);

    setLayout(layout);
    resize(WIDGET_SIZE);
}
