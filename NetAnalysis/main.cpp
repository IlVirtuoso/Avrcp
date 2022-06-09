#include "Analyzers.hpp"
#include "Routines.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include <QApplication>
#include <QMainWindow>
#include <Plotter.hpp>
#include<drogon/drogon.h>


const std::string basePath = "E:\\libs\\networkit\\input\\";



void StartQT(int argc, char * argv)
{
	
	QMainWindow* mainwindow = new QMainWindow();

	mainwindow->show();
	

}


int main(int argc, char* argv)
{
	using namespace NetAnalysis::GraphMeasures;
	QApplication* app = new QApplication(argc, &argv);
	auto graph = EdgeListReader(',',0).read(basePath + "lastfm_asia_edges.csv");
	auto dgtask = CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>(graph);
	dgtask.wait();

	auto dgt = dgtask.get();
	QLineSeries* result = new QLineSeries();
	graph.forNodes([&dgt, result](node v) {
		result->append(v, dgt.score(v));
		});
	NetAnalysis::Plotter::Plot(result)->show();
	app->exec();
	return 0;


}






