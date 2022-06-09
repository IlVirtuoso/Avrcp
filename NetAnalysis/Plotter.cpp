#include "Plotter.hpp"
#include <qbarseries.h>
#include <qbarset.h>

template<typename T>
QLineSeries* FillSeries(const std::vector<T>& x, const std::vector<T>& y)
{
	static_assert(std::is_convertible<T, double>::value);
	QLineSeries* lineSeries = new QLineSeries();
	auto xItr = x.begin();
	auto yItr = y.begin();
	while (xItr != x.end() && yItr != y.end())
	{
		lineSeries->append(*xItr, *yItr);
	}
	return lineSeries;
}

QChartView* NetAnalysis::Plotter::Plot(QLineSeries* series)
{
	QChart* lineChart = new QChart();
	lineChart->addSeries(series);
	QChartView* view = new QChartView(lineChart);
	lineChart->show();
	return view;
}

QChartView* NetAnalysis::Plotter::PlotHistogram()
{

}

template<typename T>
QChartView* NetAnalysis::Plotter::Plot(const std::vector<T>& x, const std::vector<T>& y)
{
	Plot(FillSeries(x, y));
}
