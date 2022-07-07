#include "Centralities.hpp"
#include <networkit/global/ClusteringCoefficient.hpp>

void NetAnalysis::Routines::AveragePathLength(GraphAnalyzer *analyzer)
{

    using namespace boost;
    using namespace boost::accumulators;
    using std::cout;
    using std::endl;
    int numNodes = analyzer->GetGraph().numberOfNodes();
    DoubleAccumulator acc;
    cout << "Computing AveragePathLength" << endl;
    analyzer->GetGraph().forNodes([analyzer, &acc, &numNodes](node v) {
        auto algo = analyzer->ComputeGraphDistance<Dijkstra>(v).get();
        for (auto result : algo.getDistances())
            acc(result);
        cout << "Completed at: " << (double)((v / numNodes) * 100) << endl;
    });
    cout << "Path measures" << endl;
    ShowAccumulatorsFeatures(acc, cout);
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

    std::stringstream rep{};

    DoubleAccumulator acc;

    cout << "Clustering Coefficient" << endl;
    ShowAccumulatorsFeatures(acc, rep);

    for (auto &value : algo.scores())
        acc(value);
    auto hist = matplot::hist(algo.scores());
    hist->algorithm(matplot::histogram::binning_algorithm::automatic);
    hist->normalization(matplot::histogram::normalization::pdf);
    matplot::show();
    cout << rep.str() << endl;
}

void NetAnalysis::Routines::AnalyzeCentrality(GraphAnalyzer *analyzer)
{
    auto clsTask = analyzer->CalculateCentralityMeasureAsync<Closeness>();
    auto degTask = analyzer->CalculateCentralityMeasureAsync<DegreeCentrality>();
    DegreeCentrality degree = degTask.get();
    ShowCentralityResults(degree);

    Closeness closeness = clsTask.get();
    ShowCentralityResults(closeness);

    EstimateBetweenness btw{analyzer->GetGraph(), 10};
    btw.run();
    ShowCentralityResults(btw);
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