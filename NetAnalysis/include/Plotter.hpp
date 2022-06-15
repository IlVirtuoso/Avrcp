#pragma once
#include <QApplication>
#include <QMainWindow>
#include <qcustomplot.h>
#include <boost/icl/interval.hpp>
#include <boost/icl/interval_map.hpp>
namespace NetAnalysis
{
	/*struct Bin
	{
		std::pair<int, int> Interval;
		int Count;
		Bin(std::pair<int, int> Interval) : Interval{ Interval }, Count{ 0 }{}
	};*/

	QCustomPlot* Plot(std::vector<double> x, std::vector<double> y);
	QCustomPlot* Plot(QVector<double> x, QVector<double> y);
	//std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval);
	std::vector<std::pair<boost::icl::continuous_interval<double>, int>> CountValues(std::vector<double>& values, int numBins, double precisionInterval = 1.0);
	QCustomPlot* PlotCountHistogram(std::vector<double> values, int NumBins, int padding = 5);
}