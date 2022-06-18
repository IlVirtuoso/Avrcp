#pragma once
#ifndef CENTRALITIES_HPP
#define CENTRALITIES_HPP

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


	template<typename T>
	void ShowCentralityResults()
	{

		static_assert(std::is_convertible<T&, NetworKit::Centrality&>::value);
		std::string name(typeid(T).name());

		std::cout << name << std::endl;


	}

	void AnalyzeCentrality(GraphAnalyzer* analyzer)
	{
		ShowCentralityResults<Betweenness>();
	}
	
}



#endif // !CENTRALITIES_HPP

