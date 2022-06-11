#include "GraphAnalyzer.hpp"
#include "Routines.hpp"
#include "GraphVisualizer.hpp"
#include "Plotter.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include <QApplication>
#include <QMainWindow>
#include <networkit/centrality/DegreeCentrality.hpp>




void StartQT(int argc, char * argv)
{
	
	QMainWindow* mainwindow = new QMainWindow();

	mainwindow->show();
	

}


int main(int argc, char** argv)
{
	using namespace NetAnalysis::GraphMeasures;
	std::string programPath{ argv[0] };
	auto programFolder = programPath.substr(0, programPath.find_last_of('\\'));
	std::string fileName{ "\\lastfm_asia_edges.csv" };
	QApplication* app = new QApplication(argc, argv);
	auto graph = EdgeListReader(',',0).read((programFolder + fileName).c_str());
	auto analyzer = new GraphAnalyzer(graph);

	auto converted = NetAnalysis::ConvertGraph(graph);

	auto dgtask = analyzer->CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>();
	dgtask.wait();

	auto dgt = dgtask.get();

	QVector<double> result{};
	QVector<double> nodes{};



	QCustomPlot* barsPlot = new QCustomPlot();
	QCPBars* bar = new QCPBars(barsPlot->xAxis, barsPlot->yAxis);
	QVector<double> keys{};
	QVector<double> values{};
	graph.forNodes([&result, &nodes, &dgt, &keys,&values](node v) {
		result.append(dgt.score(v));
		nodes.append(v);

		});
	bar->addData(keys, values);
	barsPlot->show();
	barsPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

	NetAnalysis::Plot(nodes, result);
	app->exec();
	return 0;
}






