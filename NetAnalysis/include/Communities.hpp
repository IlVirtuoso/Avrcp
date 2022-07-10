#pragma once
#include <boost/accumulators/framework/extractor.hpp>
#include <matplot/freestanding/axes_functions.h>
#include <matplot/freestanding/plot.h>
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
    template <typename T>
    void ShowCommunityAlgorithmData(T &algorithm, const Graph &graph, QString chartFolder = "./charts")
    {
        static_assert(std::is_convertible<T *, NetworKit::CommunityDetectionAlgorithm *>::value);
        using std::endl;
        using namespace boost::accumulators;
        std::ofstream out((chartFolder + "/statistics.txt").toStdString().c_str());
        CommunityDetectionAlgorithm &map = algorithm;
        Modularity mod{};
        out << "Modularity: " << mod.getQuality(map.getPartition(), graph) << endl;
        out << "Partitions: " << map.getPartition().numberOfSubsets() << endl;
        out << "Element in partitions: " << map.getPartition().numberOfElements() << endl;
        std::vector<double> ids{};
        std::vector<double> values{};
        accumulator_set<double, stats<tag::mean, tag::variance, tag::min, tag::max>> acc;
        for (auto entry : map.getPartition().subsetSizeMap())
        {
            ids.push_back(entry.first);
            values.push_back(entry.second);
            acc(entry.second);
        }
        out << "Size min: " << min(acc) << endl;
        out << "Size max: " << max(acc) << endl;
        out << "Size Mean: " << mean(acc) << endl;
        out << "Size variance: " << variance(acc) << endl;
        matplot::title("Community Sizes Distribution");
        auto hist = matplot::hist(values);
        matplot::show();
    }

    void ExecuteCommunityAnalysis(GraphAnalyzer *analyzer);
} // namespace NetAnalysis::Routines

#endif
