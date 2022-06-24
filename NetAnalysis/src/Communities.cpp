#include "Communities.hpp"
namespace NetAnalysis::Routines
{
	template<typename T>
	void ShowCommunityAlgorithmData(T& algorithm, const Graph& graph, QString chartFolder = "./charts")
	{
		static_assert(std::is_convertible<T*, NetworKit::CommunityDetectionAlgorithm*>::value);
		using std::endl;
		using namespace boost::accumulators;
		std::ofstream out((chartFolder + "/statistics.txt").toStdString().c_str());
		CommunityDetectionAlgorithm& map = algorithm;
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


	}


	void ExecuteCommunityAnalysis(GraphAnalyzer* analyzer)
	{
		std::filesystem::create_directories("charts/PLM");
		auto comm = analyzer->ExecuteCommunityDetectionAlgorithm<NetworKit::PLM>();
		NetAnalysis::Routines::ShowCommunityAlgorithmData(comm, analyzer->GetGraph(), "./charts/PLM");

		std::filesystem::create_directories("charts/PLP");
		auto labelProp = analyzer->ExecuteCommunityDetectionAlgorithm<NetworKit::PLP>();
		NetAnalysis::Routines::ShowCommunityAlgorithmData(labelProp, analyzer->GetGraph(), "./charts/PLP");

	}
}