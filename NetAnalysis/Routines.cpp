#include "Routines.hpp"
#include <networkit/simulation/EpidemicSimulationSEIR.hpp>
namespace NetAnalysis::Routines
{


	TGraph* PopulateGraph(NetworKit::Graph& g, NetworKit::Centrality & algo )
	{
		using namespace NetworKit;
		TGraph* plot = new TGraph();
		g.forNodes([&algo,plot](node v) {
			plot->AddPoint(v, algo.score(v));
			});
		return plot;
	}
	

	void PlotCentralityMeasures(NetworKit::Graph& graph)
	{
		using namespace NetAnalysis::GraphMeasures;
		auto btwTask = CalculateCentralityMeasureAsync<NetworKit::Betweenness>(graph);
		auto clsTask = CalculateCentralityMeasureAsync<NetworKit::Closeness>(graph);
		auto centralityTask = CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>(graph);
	}

}