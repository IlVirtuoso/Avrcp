#include "main.hpp"
#include <matplot/matplot.h>

void StartQT(int argc, char ** argv)
{


}



int main(int argc, char** argv)
{
	QApplication* app = new QApplication(argc, argv);
	auto fileName = QFileDialog::getOpenFileName();
	auto analyzer = new NetAnalysis::GraphMeasures::GraphAnalyzer();
	analyzer->LoadGraph(fileName.toStdString());
	//NetAnalysis::Routines::ExecuteCommunityAnalysis(analyzer);
	NetAnalysis::Routines::AnalyzeCentrality(analyzer);
	//NetAnalysis::Routines::AveragePathLength(analyzer);
	using namespace matplot;

	

	
	return app->exec();

}