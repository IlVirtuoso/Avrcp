#include "Components.hpp"
#include <networkit/components/ConnectedComponents.hpp>
namespace NetAnalysis::Routines
{
    void ExecuteComponentsAnalysis(GraphMeasures::GraphAnalyzer *analyzer)
    {
        // auto task = analyzer->ComputeComponentsDecomposition<NetworKit::ConnectedComponents>();
        auto algo = NetworKit::ConnectedComponents{analyzer->GetGraph()};
        algo.run();
        ShowComponentsResult(algo);
    }
} // namespace NetAnalysis::Routines