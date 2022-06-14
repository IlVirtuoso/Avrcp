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
#include <networkit/io/DotGraphWriter.hpp>
#include <QFileDialog>
#include <graphviz/gvc.h>

void StartQT(int argc, char * argv)
{
	
	QMainWindow* mainwindow = new QMainWindow();

	mainwindow->show();
	

}



void DrawGraph(Agraph_t* g,GVC_t * context)
{

	gvRender(context, g, "svg", stdout);
}

void PlotGraph(NetworKit::Graph & graph)
{
	NetworKit::DotGraphWriter().write(graph, "graph.dot");
	std::ifstream* stream = new std::ifstream();
	stream->open("graph.dot");
	char* str = new char[1024];
	std::string result = "";
	while (stream->readsome(str, 1024) != 0)
	{
		result += str;
		str = new char[1024];
	}
	Agraph_t* G;
	GVC_t* gvc;
	gvc = gvContext(); /* library function */
	G = agmemread(result.c_str());
	gvLayout(gvc, G,"dot"); /* library function */
	DrawGraph(G,gvc);
	gvFreeLayout(gvc, G); /* library function */
	agclose(G); /* library function */
	gvFreeContext(gvc);
}

void AnalyzeGraph(std::string fileName)
{
	using namespace NetAnalysis::GraphMeasures;
	Graph graph = EdgeListReader(',',(NetworKit::node)0).read(fileName);

	auto analyzer = new GraphAnalyzer(graph);
	auto dgtask = analyzer->CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>();
	dgtask.wait();
	PlotGraph(graph);
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






