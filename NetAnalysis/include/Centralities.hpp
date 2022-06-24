#pragma once
#ifndef CENTRALITIES_HPP
#define CENTRALITIES_HPP

#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include "GraphAnalyzer.hpp"
#include <networkit/centrality/LocalClusteringCoefficient.hpp>
#include <networkit/centrality/Betweenness.hpp>
#include <networkit/centrality/Closeness.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/distance/Dijkstra.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/container/vector.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/container/map.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <filesystem>
#include <matplot/matplot.h>
namespace NetAnalysis::Routines
{
	using namespace NetAnalysis::GraphMeasures;
	//void PlotCentralityMeasures(NetworKit::Graph& graph);


	template<typename T>
	void ShowCentralityResults(T& algorithm);

	void AnalyzeCentrality(GraphAnalyzer* analyzer);

	void AveragePathLength(GraphAnalyzer* analyzer);
	
}



#endif // !CENTRALITIES_HPP

