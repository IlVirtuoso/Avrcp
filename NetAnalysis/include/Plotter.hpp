#pragma once
#include <QApplication>
#include <QMainWindow>
#include <qcustomplot.h>
namespace NetAnalysis
{
	struct Bin
	{
		std::pair<int, int> Interval;
		int Count;
		Bin(std::pair<int, int> Interval) : Interval{ Interval }, Count{ 0 }{}
	};

	void Plot(std::vector<double> x, std::vector<double> y);
	void Plot(QVector<double> x, QVector<double> y);
	std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval);
	void PlotCountHistogram(std::vector<double> values, double BinDimension);
}