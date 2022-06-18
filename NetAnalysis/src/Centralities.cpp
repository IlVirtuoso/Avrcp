#include "Centralities.hpp"
#include <networkit/simulation/EpidemicSimulationSEIR.hpp>
#include<algorithm>
#include <networkit/centrality/DegreeCentrality.hpp>
namespace NetAnalysis::Routines
{
	using namespace NetAnalysis::GraphMeasures;
	void PlotBetweenness(GraphAnalyzer* analyzer)
	{
		auto result = analyzer->CalculateCentralityMeasureAsync<NetworKit::Betweenness>().get();
		std::vector<double> values{};
		std::vector<double> nodes{};
		analyzer->GetGraph().forNodes([&result, &values, &nodes](node v) {
			values.push_back(result.score(v));
			nodes.push_back(v);
			});

	}

	void PlotDegreeCentrality(GraphAnalyzer* analyzer)
	{
		auto result = analyzer->CalculateCentralityMeasureAsync<NetworKit::DegreeCentrality>().get();
		std::vector<double> values{};
		std::vector<double> nodes{};
		analyzer->GetGraph().forNodes([&result, &values, &nodes](node v) {
			values.push_back(result.score(v));
			nodes.push_back(v);
			});

	}

}