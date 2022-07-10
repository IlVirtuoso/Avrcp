#include "Communities.hpp"
namespace NetAnalysis::Routines
{
    void ExecuteCommunityAnalysis(GraphAnalyzer *analyzer)
    {
        std::filesystem::create_directories("charts/PLM");
        auto comm = analyzer->ExecuteCommunityDetectionAlgorithm<NetworKit::PLM>();
        NetAnalysis::Routines::ShowCommunityAlgorithmData(comm, analyzer->GetGraph(), "./charts/PLM");
        std::filesystem::create_directories("charts/PLP");
        auto labelProp = analyzer->ExecuteCommunityDetectionAlgorithm<NetworKit::PLP>();
        NetAnalysis::Routines::ShowCommunityAlgorithmData(labelProp, analyzer->GetGraph(), "./charts/PLP");
    }

} // namespace NetAnalysis::Routines