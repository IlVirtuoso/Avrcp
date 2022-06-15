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






