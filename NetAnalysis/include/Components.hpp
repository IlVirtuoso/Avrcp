#pragma once
#include "GraphAnalyzer.hpp"
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <cmath>
#include <matplot/freestanding/plot.h>
#include <matplot/matplot.h>
#include <networkit/components/ComponentDecomposition.hpp>
#include <networkit/components/ConnectedComponents.hpp>
#include <networkit/graph/Graph.hpp>
#include <ostream>
#include <vector>

namespace NetAnalysis::Routines
{

    template <typename T> void ShowComponentsResult(T &algorithm)
    {
        using namespace boost::accumulators;
        using std::cout;
        using std::endl;
        static_assert(std::is_convertible<T *, NetworKit::ComponentDecomposition *>::value);
        NetworKit::ComponentDecomposition &algo = algorithm;
        accumulator_set<double, stats<tag::mean, tag::max, tag::min, tag::variance>> acc;
        std::vector<double> sizes{};
        for (auto size : algo.getComponentSizes())
        {
            acc(size.second);
            sizes.push_back(size.second);
        }
        cout << "Max Size: " << max(acc) << endl;
        cout << "Min Size: " << min(acc) << endl;
        cout << "Variance :" << variance(acc) << endl;
        cout << "Mean: " << mean(acc) << endl;
        matplot::hist(sizes);
        matplot::show();
    }

    void ExecuteComponentsAnalysis(GraphMeasures::GraphAnalyzer *analyzer);

} // namespace NetAnalysis::Routines
