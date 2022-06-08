#include "Analyzers.hpp"
#include "Routines.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include<drogon/drogon.h>
#include "Gui/QtClass.h"
const std::string basePath = "E:\\libs\\networkit\\input\\";






int main(int argc, char* argv)
{
	using namespace NetAnalysis::GraphMeasures;
	QApplication* app = new QApplication(argc, &argv);
	QMainWindow* mainwindow = new QMainWindow();

	Ui_MainWindow* mainUI = new Ui_MainWindow{};
	mainUI->setupUi(mainwindow);

	mainwindow->show();
	app->exec();

	return 0;


}






