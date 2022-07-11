#pragma once
#include <boost/accumulators/framework/extractor.hpp>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/plot.h>
#include <networkit/community/CommunityDetectionAlgorithm.hpp>
#include <networkit/structures/Partition.hpp>
#include <string>
#ifndef COMMUNITIES_HPP
#define COMMUNITIES_HPP
#include "GraphAnalyzer.hpp"
#include <QString>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/array.hpp>
#include <filesystem>
#include <iostream>
#include <networkit/community/LocalCommunityEvaluation.hpp>
#include <networkit/community/Modularity.hpp>
#include <networkit/community/PLM.hpp>
#include <networkit/community/PLP.hpp>
#include <networkit/io/DotPartitionWriter.hpp>

namespace NetAnalysis::Routines
{
    using namespace NetworKit;
    using namespace NetAnalysis::GraphMeasures;

    void ShowCommunityAlgorithmData(CommunityDetectionAlgorithm &algorithm, const Graph &graph,
                                    QString chartFolder = "./charts");

    void PrintPartitions(GraphAnalyzer *analyzer, const NetworKit::Partition &partition, std::string foldername,
                         bool onePerSize);

    void ExecuteCommunityAnalysis(GraphAnalyzer *analyzer);
} // namespace NetAnalysis::Routines

#endif
