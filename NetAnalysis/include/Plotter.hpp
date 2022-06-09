#pragma once
#include <QtCharts/qlineseries.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
namespace NetAnalysis::Plotter
{

	template<typename T>
	QChartView* Plot(const std::vector<T>& x,const std::vector<T>& y);

	QChartView* Plot(QLineSeries* series);

	QChartView* PlotHistogram();
}