#pragma once
#include <QtCharts/qlineseries.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>
#include <qgraphicsview.h>
#include <qbarset.h>
#include <qbarseries.h>
namespace NetAnalysis
{

	class Plotter
	{
	private:
		QGraphicsView* currentView;
		QChart* currentChart;

	public:
		Plotter();
		void Plot(std::vector<QAbstractSeries*> series);
		void AddAxis(QAbstractAxis* axis, Qt::Alignment alignment);
		void Reset();
		const QGraphicsView* GetCurrentView() { return currentView; }
		const QChart* GetChart() const { return currentChart; }
		void PlotHistogram(const std::vector<double>& values, int numBins);
	};

}