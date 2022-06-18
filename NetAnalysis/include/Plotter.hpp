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

	QCustomPlot* GeneratePlot(QColor background = QColor(200, 200, 200, 20), QColor axisColor = Qt::GlobalColor::white);
	QCPGraph* Plot(std::vector<double> x, std::vector<double> y, QCustomPlot* plot, QColor lineColor);
	QCPGraph* Plot(QVector<double> x, QVector<double> y, QCustomPlot* plot, QColor lineColor);
	//std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval);
	std::vector<std::pair<boost::icl::continuous_interval<double>, int>> CountValues(std::vector<double>& values, int numBins, double precisionInterval = 1.0);
	QCPBars* PlotCountHistogram(std::vector<double> values, int NumBins,QCustomPlot* plot, int padding = 5, bool normalized = false, QColor barsColor = Qt::GlobalColor::blue);

}