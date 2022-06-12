#pragma once
#include <map>
#include <vector>
#include <cmath>
namespace NetAnalysis::Routines
{
	//void PlotCentralityMeasures(NetworKit::Graph& graph);

	struct Bin
	{
		std::pair<int, int> Interval;
		int Count;
		Bin(std::pair<int,int> Interval): Interval{Interval},Count{0}{}
	};

	std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval);

}

