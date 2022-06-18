#include "Plotter.hpp"
#include <QtDataVisualization>
namespace NetAnalysis
{
	QCPGraph* Plot(std::vector<double> x, std::vector<double> y, QCustomPlot * plot, QColor lineColor)
	{
		QVector<double> x1(x.begin(), x.end());
		QVector<double> y1(y.begin(), y.end());
		return Plot(x1, y1,plot,lineColor);
	}

	QCPGraph* Plot(QVector<double> x, QVector<double> y, QCustomPlot* customPlot,QColor lineColor)
	{

		auto result = customPlot->addGraph();
		result->setData(x, y);
		result->setPen(QPen(lineColor));
		return result;
	}

	


	/*std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval)
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

	}*/


	std::vector<std::pair<boost::icl::continuous_interval<double>,int>> CountValues(std::vector<double>& values, int numBins, double precisionInterval)
	{
		using namespace boost::icl;
		auto max = *std::max_element(values.begin(), values.end());
		auto min = *std::min_element(values.begin(), values.end());
		double span = std::ceil((max - min) / numBins);
		interval_map<double, int> lookup{};
		auto start = min;
		auto result = *new std::vector<std::pair<boost::icl::continuous_interval<double>, int>>();
		for (int i = 0 ; i < numBins; i++)
		{
			auto interval = continuous_interval<double>(start, start + span);
			result.push_back(std::pair(interval,0));
			lookup.insert(std::pair(interval, i));
			start += span + precisionInterval;
		}
		for (double value : values)
		{
			int i = lookup(value);
			result[i].second++;
		}
		return result;
	}

	QCPBars* PlotCountHistogram(std::vector<double> values, int NumBins, QCustomPlot* plot, int padding, bool normalized, QColor barsColor)
	{
		QCPBars* bar = new QCPBars(plot->xAxis, plot->yAxis);
		QVector<QString> labels{};
		QVector<double> ticks;
		auto counters = CountValues(values, NumBins);
		double sum = 1;
		if (normalized)
		{
			sum = 0;
			for (const auto& value: counters) sum += value.second;
		}
		for (int i = 0 ; i < counters.size(); i++)
		{
			bar->addData(i + 1, counters.at(i).second/sum);
			labels << (std::to_string((int)counters.at(i).first.lower()) + "-" + std::to_string((int)counters.at(i).first.upper())).c_str();
			ticks << i + 1;
		}
		QSharedPointer<QCPAxisTickerText> textTicker{new QCPAxisTickerText()};
		textTicker->addTicks(ticks, labels);
		plot->xAxis->setTicker(textTicker);
		plot->yAxis->setPadding(padding);
		bar->setBrush(barsColor);
		bar->rescaleAxes();
		return bar;
	}

	QCustomPlot* GeneratePlot(QColor background, QColor axisColor)
	{
		QCustomPlot* plot = new QCustomPlot();
		plot->setBackground(background);
		plot->xAxis->setTickLabelColor(axisColor);
		plot->yAxis->setTickLabelColor(axisColor);
		return plot;
	}
}