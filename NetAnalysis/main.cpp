#include "Analyzers.hpp"
#include <future>
#include <networkit/io/EdgeListReader.hpp>
#include<drogon/drogon.h>

#include<TApplication.h>
#include <TCanvas.h>
#include <TH1I.h>
#include <TGraph.h>
#include <TGraph2D.h>
const std::string basePath = "E:\\libs\\networkit\\input\\";





int main(int argc, char* argv)
{
	using namespace drogon;
	using namespace NetAnalysis::GraphMeasures;
	auto graph = NetworKit::EdgeListReader(',', 0).read(basePath + "lesmiserables_edges.csv");

	auto clsTask = CalculateCentralityMeasureAsync<NetworKit::Closeness>(graph);
	auto centralityTask = CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>(graph);

	
	drogon::app().registerHandler("/btw", [&graph](const HttpRequestPtr& req,
		std::function<void(const HttpResponsePtr&)>&& callback) {

			auto btw = CalculateCentralityMeasureAsync<NetworKit::Betweenness>(graph);
			btw.wait();
			Json::Value mex;
			std::string values = "";
			auto vx = btw.get().scores();
			for (auto v : vx)
				values += std::to_string(v) + std::string(",");
			mex["response"] = values;
			auto resp = HttpResponse::newHttpJsonResponse(mex);
			callback(resp);
		});
		
	app().registerHandler("/test?username={name}",
		[](const HttpRequestPtr& req,
			std::function<void(const HttpResponsePtr&)>&& callback,
			const std::string& name)
		{
			Json::Value json;
			json["result"] = "ok";
			json["message"] = std::string("hello,") + name;
			auto resp = HttpResponse::newHttpJsonResponse(json);
			callback(resp);
		});

	drogon::app().setDocumentRoot("./netanalyst").addListener("127.0.0.1", 8080).run();

}


int UseRoot(int argc, char* argv)
{
	using namespace NetAnalysis::GraphMeasures;

	TApplication* app = new TApplication("NetAnalysis", &argc, &argv);
	auto graph = NetworKit::EdgeListReader(',', 0).read(basePath + "lesmiserables_edges.csv");
	auto btwTask = CalculateCentralityMeasureAsync<NetworKit::Betweenness>(graph);
	auto clsTask = CalculateCentralityMeasureAsync<NetworKit::Closeness>(graph);
	auto centralityTask = CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>(graph);


	centralityTask.wait();

	TCanvas* c1 = new TCanvas();
	c1->Divide(3, 1);
	c1->cd(1);
	auto centrality = centralityTask.get();
	TH1I* g = new TH1I("centrality", "cent", 10, 0, centrality.maximum());
	g->SetFillStyle(1);
	graph.forNodes([g, &centrality](node v) {
		g->Fill(centrality.score(v));
		});

	g->Draw("LEGO1");
	c1->Update();
	btwTask.wait();
	clsTask.wait();

	c1->cd(2);
	TGraph* btwg = new TGraph();
	auto btw = btwTask.get();
	graph.forNodes([btwg, &btw](node v) {
		btwg->AddPoint(v, btw.score(v));
		});
	btwg->Draw();

	TGraph* clsG = new TGraph();
	c1->cd(3);

	auto cls = clsTask.get();

	graph.forNodes([&cls, clsG](node v) {
		clsG->AddPoint(v, cls.score(v));
		});

	clsG->Draw("ALP");
	clsG->SetEditable(false);
	c1->Update();
	std::cout << btw.maximum() << std::endl;
	TCanvas* c2 = new TCanvas();
	c2->cd();

	TGraph2D* tgraph = new TGraph2D();
	graph.forNodes([&tgraph, &btw, &cls](node v) {
		tgraph->AddPoint(v, btw.score(v), cls.score(v));
		});
	tgraph->Draw("tri1 p0");
	app->Run();

	return 0;


}






