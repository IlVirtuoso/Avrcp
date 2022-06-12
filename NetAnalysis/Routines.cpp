#include "Routines.hpp"
#include <networkit/simulation/EpidemicSimulationSEIR.hpp>
namespace NetAnalysis::Routines
{
	
	std::vector<Bin*>& DiscretizeValues(const std::vector<double>& values, int spanInterval)
	{
		auto min = *std::min(values.begin(), values.end());
		auto max = *std::max(values.begin(), values.end());
		int numBins = std::ceil(((max - min) / spanInterval)) + 1;
		std::vector<Bin*>& bins = *new std::vector<Bin*>();
		double start = min;
		for (int i = 0; i < numBins; i++)
		{
			bins[i] = new Bin{ std::pair{start,start + spanInterval},0 };
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