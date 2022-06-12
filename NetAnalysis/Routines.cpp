#include "Routines.hpp"
#include <networkit/simulation/EpidemicSimulationSEIR.hpp>
#include<algorithm>
namespace NetAnalysis::Routines
{
	
	std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval)
	{
		auto max = *std::max_element(values.begin(), values.end());
		auto min = *std::min_element(values.begin(), values.end());
		int numBins = std::ceil(((max - min) / spanInterval)) + 1;
		std::vector<Bin*>& bins = *new std::vector<Bin*>();
		double start = min;
		for (int i = 0; i < numBins; i++)
		{
			auto newBin = new Bin{ std::pair{start,start + spanInterval}}; 
			bins.push_back(newBin);
			start += spanInterval;
		}
		for (auto value : values)
		{
			int bin = std::floor((value / max) * numBins);
			bins[bin]->Count++;
		}
		return bins;

	}


}