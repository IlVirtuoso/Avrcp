#pragma once
#include <map>
#include <vector>
#include <cmath>
#include "GraphAnalyzer.hpp"
#include <networkit/centrality/LocalClusteringCoefficient.hpp>
#include <networkit/centrality/Betweenness.hpp>
#include "Plotter.hpp"
namespace NetAnalysis::Routines
{
	using namespace NetAnalysis::GraphMeasures;
	//void PlotCentralityMeasures(NetworKit::Graph& graph);

	void PlotBetweenness(GraphAnalyzer * analyzer);
	void PlotDegreeCentrality(GraphAnalyzer* analyzer);
}

