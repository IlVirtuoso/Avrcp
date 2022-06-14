#include "Plotter.hpp"

namespace NetAnalysis
{
	void Plot(std::vector<double> x, std::vector<double> y)
	{
		QVector<double> x1(x.begin(), x.end());
		QVector<double> y1(y.begin(), y.end());
	}

	void Plot(QVector<double> x, QVector<double> y)
	{
		QCustomPlot* customPlot = new QCustomPlot();

		customPlot->addGraph();
		customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
		customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
		customPlot->addGraph();
		customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
		// generate some points of data (y0 for first, y1 for second graph):
		// configure right and top axis to show ticks but no labels:
		// (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
		customPlot->xAxis2->setVisible(true);
		customPlot->xAxis2->setTickLabels(false);
		customPlot->yAxis2->setVisible(true);
		customPlot->yAxis2->setTickLabels(false);
		// make left and bottom axes always transfer their ranges to right and top axes:
		QObject::connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
		QObject::connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
		// pass data points to graphs:

		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		customPlot->graph(0)->rescaleAxes();
		// same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
		customPlot->graph(1)->rescaleAxes(true);
		// Note: we could have also just called customPlot->rescaleAxes(); instead
		// Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
		customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
		customPlot->graph(0)->setData(x, y);
		customPlot->show();
	}

	


	std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval)
	{
		auto max = *std::max_element(values.begin(), values.end());
		auto min = *std::min_element(values.begin(), values.end());
		int numBins = std::ceil(((max - min) / spanInterval)) + 1;
		std::vector<Bin*>& bins = *new std::vector<Bin*>();
		double start = min;
		for (int i = 0; i < numBins; i++)
		{
			auto newBin = new Bin{ std::pair{start,start + spanInterval} };
			bins.push_back(newBin);
			start += spanInterval;
		}
		for (auto value : values)
		{
			int bin = std::floor((value / max) * (numBins - 1));
			bins[bin]->Count++;
		}
		return bins;

	}

	void PlotCountHistogram(std::vector<double> values, double BinDimension)
	{
		QCustomPlot* barsPlot = new QCustomPlot();
		QCPBars* bar = new QCPBars(barsPlot->xAxis, barsPlot->yAxis);
		auto discr = DiscretizeValues(values, BinDimension);
		for (auto val : discr)
		{
			bar->addData(std::floor((val->Interval.second - val->Interval.first) / 2 + val->Interval.first), val->Count);
		}
		bar->setWidth(BinDimension);
		bar->rescaleAxes();
		barsPlot->show();
		barsPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	}
}