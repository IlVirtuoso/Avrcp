#include "Communities.hpp"
#include "GraphAnalyzer.hpp"
#include <boost/array.hpp>
#include <boost/container/vector.hpp>
#include <cstddef>
#include <filesystem>
#include <networkit/Globals.hpp>
#include <networkit/community/PLP.hpp>
#include <networkit/io/DotGraphWriter.hpp>
#include <networkit/io/DotPartitionWriter.hpp>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

namespace NetAnalysis::Routines
{
    void ShowCommunityAlgorithmData(CommunityDetectionAlgorithm &map, const Graph &graph, QString chartFolder)
    {

        using std::endl;
        using namespace boost::accumulators;
        std::ofstream out((chartFolder + "/statistics.txt").toStdString().c_str());
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
    }

    void ExecuteCommunityAnalysis(GraphAnalyzer *analyzer)
    {
        std::filesystem::create_directories("charts/PLM");
        auto comm = PLM(analyzer->GetGraph(), true, 1.0, "balanced", 100);
        comm.run();
        NetAnalysis::Routines::ShowCommunityAlgorithmData(comm, analyzer->GetGraph(), "./charts/PLM");

        std::filesystem::create_directories("charts/PLP");
        auto labelProp = PLP{analyzer->GetGraph(), 20, 100};
        labelProp.run();
        NetAnalysis::Routines::ShowCommunityAlgorithmData(labelProp, analyzer->GetGraph(), "./charts/PLP");
        auto PLMPart = comm.getPartition();
        auto PLPPart = labelProp.getPartition();
        PrintPartitions(analyzer, PLMPart, "./data/communities/PLM", true);
        PrintPartitions(analyzer, PLPPart, "./data/communities/PLP", true);
    }

    void PrintPartitions(GraphAnalyzer *analyzer, const NetworKit::Partition &partition, std::string foldername,
                         bool onePerSize)
    {
        int commId = 0;
        std::set<size_t> sizes{};
        auto partitions = partition.getSubsets();
        for (auto part : partitions)
        {
            auto size = part.size();
            if (sizes.find(size) == sizes.end() || !onePerSize)
            {
                sizes.insert(size);
                auto gen = analyzer->GenGraphFromSubset(part);
                DotGraphWriter().write(gen, foldername + "/community_" + std::to_string(commId) + ".dot");
            }
            commId++;
        }
    }
} // namespace NetAnalysis::Routines