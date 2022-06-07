#include "Routines.hpp"
#include <networkit/simulation/EpidemicSimulationSEIR.hpp>
namespace NetAnalysis::Routines
{
	

	void PlotCentralityMeasures(NetworKit::Graph& graph)
	{
		using namespace NetAnalysis::GraphMeasures;
		auto btwTask = CalculateCentralityMeasureAsync<NetworKit::Betweenness>(graph);
		auto clsTask = CalculateCentralityMeasureAsync<NetworKit::Closeness>(graph);
		auto centralityTask = CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>(graph);
	}

}