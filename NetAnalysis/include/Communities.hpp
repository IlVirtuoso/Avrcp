#pragma once
#ifndef COMMUNITIES_HPP
#define COMMUNITIES_HPP
#include <networkit/community/PLM.hpp>
#include <networkit/community/PLP.hpp>
#include <filesystem>
#include <iostream>
#include <QString>
#include <networkit/community/Modularity.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/array.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <networkit/io/DotPartitionWriter.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <networkit/community/LocalCommunityEvaluation.hpp>

namespace NetAnalysis::Routines
{
	template<typename T>
	void ShowCommunityAlgorithmData(T& algorithm, const Graph& graph, QString chartFolder = "./charts");

	void ExecuteCommunityAnalysis(GraphAnalyzer* analyzer);



	

}

#endif
