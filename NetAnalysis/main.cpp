#include "Analyzers.hpp"
#include "Routines.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include <QApplication>
#include <QMainWindow>
#include <Plotter.hpp>
#include<drogon/drogon.h>





void StartQT(int argc, char * argv)
{
	
	QMainWindow* mainwindow = new QMainWindow();

	mainwindow->show();
	

}


int main(int argc, char** argv)
{
	using namespace NetAnalysis::GraphMeasures;
	using namespace NetAnalysis;
	std::string programPath{ argv[0] };
	auto programFolder = programPath.substr(0, programPath.find_last_of('\\'));
	std::string fileName{ "\\lastfm_asia_edges.csv" };
	QApplication* app = new QApplication(argc, argv);
	auto graph = EdgeListReader(',',0).read((programFolder + fileName).c_str());
	auto analyzer = new GraphAnalyzer(graph);

	auto dgtask = analyzer->CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>();
	dgtask.wait();

	auto dgt = dgtask.get();
	Plotter* plotter = new Plotter();

	plotter->PlotHistogram(dgt.scores(), 0);
	((QChartView*)plotter->GetCurrentView())->show();
	app->exec();
	return 0;


}






