#pragma once
#include "GraphAnalyzer.hpp"
#include "Routines.hpp"
#include "GraphVisualizer.hpp"
#include "Plotter.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include <QApplication>
#include <QMainWindow>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <QFileDialog>


void StartQT(int argc, char * argv)
{
	
	QMainWindow* mainwindow = new QMainWindow();

	mainwindow->show();
	

}

void AnalyzeGraph(std::string fileName)
{
	using namespace NetAnalysis::GraphMeasures;
	Graph graph = EdgeListReader(',',(NetworKit::node)0).read(fileName);

	auto analyzer = new GraphAnalyzer(graph);
	auto converted = NetAnalysis::ConvertGraph(graph);

	auto dgtask = analyzer->CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>();
	dgtask.wait();

	auto dgt = dgtask.get();

	auto discr = NetAnalysis::Routines::DiscretizeValues(dgt.scores(), 50);

	QVector<double> result{};
	QVector<double> nodes{};


	QCustomPlot* barsPlot = new QCustomPlot();
	QCPBars* bar = new QCPBars(barsPlot->xAxis, barsPlot->yAxis);
	graph.forNodes([&result, &nodes, &dgt](node v) {
		result.append(dgt.score(v));
		nodes.append(v);
		});
	
	for (auto val : discr)
	{
		bar->addData(val->Interval.first, val->Count);
	}

	barsPlot->show();
	barsPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

	NetAnalysis::Plot(nodes, result);

}



int main(int argc, char** argv)
{
	QApplication* app = new QApplication(argc, argv);


	auto fileName = QFileDialog::getOpenFileName();
	AnalyzeGraph(fileName.toStdString());
	app->exec();
	return 0;
}






