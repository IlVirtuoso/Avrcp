#include "Analyzers.hpp"
#include "Routines.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include<drogon/drogon.h>

#include<TApplication.h>
#include <TCanvas.h>
#include <TH1I.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TButton.h>
const std::string basePath = "E:\\libs\\networkit\\input\\";






int main(int argc, char* argv)
{
	using namespace NetAnalysis::GraphMeasures;

	TApplication* app = new TApplication("NetAnalysis", &argc, &argv);

	app->Run();

	return 0;


}






