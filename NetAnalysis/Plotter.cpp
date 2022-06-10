#include "Plotter.hpp"





NetAnalysis::Plotter::Plotter()
{
	this->currentChart = new QChart();
	this->currentView = new QChartView(currentChart);
}


void NetAnalysis::Plotter::Plot(std::vector<QAbstractSeries*> series)
{
	for (auto serie : series)
		currentChart->addSeries(serie);
}



void NetAnalysis::Plotter::AddAxis(QAbstractAxis* axis, Qt::Alignment alignment)
{
	currentChart->addAxis(axis, alignment);
}

void NetAnalysis::Plotter::Reset()
{
}


void NetAnalysis::Plotter::PlotHistogram(const std::vector<double>& values, int numBins)
{
	QBarSeries* serie = new QBarSeries();
	QBarSet* barSet = new QBarSet("Values");
	QList<double> qlist{};
	for (auto value : values)
	{
		qlist.append(value);
	}
	barSet->append(qlist);
	serie->append(barSet);
	currentChart->addSeries(serie);
}
