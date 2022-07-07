#pragma once
#ifndef CENTRALITIES_HPP
#define CENTRALITIES_HPP

#include "GraphAnalyzer.hpp"
#include <QString>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>
#include <cmath>
#include <filesystem>
#include <map>
#include <matplot/matplot.h>
#include <networkit/centrality/Closeness.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/centrality/EstimateBetweenness.hpp>
#include <networkit/centrality/LocalClusteringCoefficient.hpp>
#include <networkit/distance/Dijkstra.hpp>
#include <networkit/global/ClusteringCoefficient.hpp>
#include <sstream>
#include <vector>

namespace NetAnalysis::Routines
{

    using DoubleAccumulator = boost::accumulators::accumulator_set<
        double, boost::accumulators::stats<boost::accumulators::tag::mean, boost::accumulators::tag::variance,
                                           boost::accumulators::tag::median, boost::accumulators::tag::max,
                                           boost::accumulators::tag::min>>;

    template <typename T> void ShowCentralityResults(T &algorithm)
    {
        using namespace boost::accumulators;
        static_assert(std::is_convertible<T &, NetworKit::Centrality &>::value);
        GraphMeasures::Centrality &algo = algorithm;
        QString name(typeid(T).name());
        QString path = "./charts/" + name.replace(":", "").replace("class", "").trimmed();
        std::filesystem::create_directory(path.toStdString());
        std::ofstream out(path.toStdString() + "/statistics.txt");
        accumulator_set<double, stats<tag::mean, tag::min, tag::max, tag::variance>> acc;
        for (auto score : algo.scores())
            acc(score);
        out << "Score Mean: " << mean(acc) << "\n";
        out << "Score Max: " << max(acc) << "\n";
        out << "Score Min: " << min(acc) << "\n";
        out << "Score variance: " << variance(acc) << "\n";
        out << "Teoretical maximum: " << algo.maximum() << "\n";

        matplot::hist(algo.scores(), matplot::histogram::binning_algorithm::sqrt,
                      matplot::histogram::normalization::cummulative_count);
    }

    void ShowAccumulatorsFeatures(DoubleAccumulator &acc, std::ostream &out);

    using namespace NetAnalysis::GraphMeasures;

    void AnalyzeCentrality(GraphAnalyzer *analyzer);

    void DegreeAverage(GraphAnalyzer *analyzer);

    void AveragePathLength(GraphAnalyzer *analyzer);

    void ClusteringCoefficients(GraphAnalyzer *analyzer);

} // namespace NetAnalysis::Routines

#endif // !CENTRALITIES_HPP
