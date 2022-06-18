#include "main.hpp"

void StartQT(int argc, char * argv)
{
	
	QMainWindow* mainwindow = new QMainWindow();

	mainwindow->show();
	

}








int main(int argc, char** argv)
{
	QApplication* app = new QApplication(argc, argv);
	auto fileName = QFileDialog::getOpenFileName();
	auto analyzer = new NetAnalysis::GraphMeasures::GraphAnalyzer();
	analyzer->LoadGraph(fileName.toStdString());
	NetAnalysis::Routines::ExecuteCommunityAnalysis(analyzer);
	
	app->exec();
	return 0;
}






