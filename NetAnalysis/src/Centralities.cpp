#include "Centralities.hpp"
#include <future>
#include <networkit/centrality/Closeness.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/distance/BFS.hpp>
#include <networkit/global/ClusteringCoefficient.hpp>
#include <sstream>
#include <streambuf>
void NetAnalysis::Routines::AveragePathLength(GraphAnalyzer *analyzer)
{

    using namespace boost;
    using namespace boost::accumulators;
    using std::cout;
    using std::endl;
    log << "Average Path Length analysis";
    std::stringstream out{};
    int numNodes = analyzer->GetGraph().numberOfNodes();
    DoubleAccumulator acc;
    out << "Computing AveragePathLength";

    auto graph = analyzer->GetGraph();
    analyzer->GetGraph().forNodes([&acc, &graph](node v) {
        NetworKit::BFS algo(graph, v);
        std::async(
            [&](NetworKit::BFS algo, DoubleAccumulator acc) {
            algo.run();
            for (auto value : algo.getDistances())
                acc(value);
            log << "Completed At: " << v;
            },
            algo, acc);
    });
    out << "Path measures" << endl;
    ShowAccumulatorsFeatures(acc, out);
    log.TraceInformation(out.str());
}

void NetAnalysis::Routines::ClusteringCoefficients(GraphAnalyzer *analyzer)
{
    using namespace boost;
    using namespace boost::accumulators;
    using NetworKit::LocalClusteringCoefficient;
    using std::cout;
    using std::endl;
    auto algo = LocalClusteringCoefficient(analyzer->GetGraph(), true);
    algo.run();

    std::stringstream out{};

    DoubleAccumulator acc;

    cout << "Clustering Coefficient" << endl;
    ShowAccumulatorsFeatures(acc, out);

    for (auto &value : algo.scores())
        acc(value);
    auto hist = matplot::hist(algo.scores());
    hist->algorithm(matplot::histogram::binning_algorithm::automatic);
    hist->normalization(matplot::histogram::normalization::pdf);
    log << out.str();
}

void NetAnalysis::Routines::AnalyzeCentrality(GraphAnalyzer *analyzer)
{
    log << "Starting centrality analysis";
    auto clsTask = analyzer->CalculateCentralityMeasureAsync<Closeness>();
    auto degree = NetworKit::DegreeCentrality(analyzer->GetGraph());
    auto closeness = NetworKit::Closeness(analyzer->GetGraph());
    log.TraceInformation("Collect Degree Centrality");
    degree.run();
    ShowCentralityResults(degree, "DegreeCentrality");

    log.TraceInformation("Collect Closeness Centrality");
    closeness.run();
    ShowCentralityResults(closeness, "Closeness");

    log.TraceInformation("Collect Estimated Betwenness centrality");
    EstimateBetweenness btw{analyzer->GetGraph(), 10};
    btw.run();
    ShowCentralityResults(btw, "EstimatedBetwenness");
}

void NetAnalysis::Routines::ShowAccumulatorsFeatures(DoubleAccumulator &acc, std::ostream &out)
{
    using namespace boost;
    using namespace boost::accumulators;
    using std::cout;
    using std::endl;
    out << "Min: " << min(acc) << endl;
    out << "Max: " << max(acc) << endl;
    out << "Mean: " << mean(acc) << endl;
    out << "Variance: " << variance(acc) << endl;
}

void NetAnalysis::Routines::DegreeAverage(GraphAnalyzer *analyzer)
{
}