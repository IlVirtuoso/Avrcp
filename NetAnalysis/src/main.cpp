#pragma once
#include "GraphAnalyzer.hpp"
#include "Centralities.hpp"
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






int main(int argc, char** argv)
{
	QApplication* app = new QApplication(argc, argv);

	
	auto fileName = QFileDialog::getOpenFileName();
	auto analyzer = new NetAnalysis::GraphMeasures::GraphAnalyzer();
	analyzer->LoadGraph(fileName.toStdString());
	NetAnalysis::Routines::PlotDegreeCentrality(analyzer);
	//NetAnalysis::Routines::PlotBetweenness(analyzer);
	app->exec();
	return 0;
}






