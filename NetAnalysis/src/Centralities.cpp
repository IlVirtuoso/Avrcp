#include "Centralities.hpp"

namespace NetAnalysis::Routines
{
	template<typename T>
	void ShowCentralityResults(T& algorithm)
	{
		using namespace boost::accumulators;
		static_assert(std::is_convertible<T&, NetworKit::Centrality&>::value);
		Centrality& algo = algorithm;
		QString name(typeid(T).name());
		QString path = "./charts/" + name.replace(":", "").replace("class", "").trimmed();
		std::filesystem::create_directory(path.toStdString());
		std::ofstream out(path.toStdString() + "/statistics.txt");
		accumulator_set<double, stats<tag::mean, tag::min, tag::max, tag::variance>> acc;
		for (auto score : algo.scores()) acc(score);
		out << "Score Mean: " << mean(acc) << "\n";
		out << "Score Max: " << max(acc) << "\n";
		out << "Score Min: " << min(acc) << "\n";
		out << "Score variance: " << variance(acc) << "\n";
		out << "Teoretical maximum: " << algo.maximum() << "\n";

		matplot::hist(algo.scores(), matplot::histogram::binning_algorithm::sqrt, matplot::histogram::normalization::cummulative_count);

	}

	void AnalyzeCentrality(GraphAnalyzer* analyzer)
	{
		//auto btwTask = analyzer->CalculateCentralityMeasureAsync<Betweenness>();
		//auto clsTask = analyzer->CalculateCentralityMeasureAsync<Closeness>();
		auto degTask = analyzer->CalculateCentralityMeasureAsync<DegreeCentrality>();
		DegreeCentrality degree = degTask.get();
		ShowCentralityResults(degree);

		/*
		Closeness closeness = clsTask.get();
		ShowCentralityResults(closeness);

		Betweenness btw = btwTask.get();
		ShowCentralityResults(btw);

		*/
	}

	void AveragePathLength(GraphAnalyzer* analyzer)
	{
		using namespace boost;
		container::map<double, std::vector<double>> distanceMap{};
		int numNodes = analyzer->GetGraph().numberOfNodes();
		analyzer->GetGraph().forNodes([analyzer, &distanceMap](node v)
			{
				auto algo = analyzer->ComputeGraphDistance<Dijkstra>(v).get();
				distanceMap[v] = algo.getDistances();
			});


	}
}