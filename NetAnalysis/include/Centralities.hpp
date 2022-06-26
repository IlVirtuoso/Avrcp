#pragma once
#ifndef CENTRALITIES_HPP
#define CENTRALITIES_HPP

#include <map>
#include <vector>
#include <cmath>
#include "GraphAnalyzer.hpp"
#include <networkit/centrality/LocalClusteringCoefficient.hpp>
#include <networkit/centrality/EstimateBetweenness.hpp>
#include <networkit/centrality/Closeness.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/distance/Dijkstra.hpp>
#include <networkit/global/ClusteringCoefficient.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/container/vector.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/container/map.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <sstream>
#include <filesystem>
#include <matplot/matplot.h>

namespace NetAnalysis::Routines
{

	using DoubleAccumulator = boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean, boost::accumulators::tag::variance, boost::accumulators::tag::median, boost::accumulators::tag::max, boost::accumulators::tag::min>>;

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

	void ShowAccumulatorsFeatures(DoubleAccumulator& acc, std::ostream& out)
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

	using namespace NetAnalysis::GraphMeasures;

	void AnalyzeCentrality(GraphAnalyzer* analyzer)
	{
		auto clsTask = analyzer->CalculateCentralityMeasureAsync<Closeness>();
		auto degTask = analyzer->CalculateCentralityMeasureAsync<DegreeCentrality>();
		DegreeCentrality degree = degTask.get();
		ShowCentralityResults(degree);

		
		Closeness closeness = clsTask.get();
		ShowCentralityResults(closeness);

		EstimateBetweenness btw{ analyzer->GetGraph() ,10};
		btw.run();
		ShowCentralityResults(btw);

		
	}

	void Degree(GraphAnalyzer* analyzer)
	{
		using namespace boost;
		using namespace boost::accumulators;

		std::vector<double> degrees{};
		DoubleAccumulator acc;
		auto graph = analyzer->GetGraph();
		graph.forNodes([graph, &degrees, &acc](node v) {
			auto val = graph.degree(v);
			acc(val);
			degrees.push_back(val);
			});

		std::cout << "Degree measures" << std::endl;
		ShowAccumulatorsFeatures(acc, std::cout);
		matplot::hist(degrees)->normalization(matplot::histogram::normalization::pdf).algorithm(matplot::histogram::binning_algorithm::scott);
		matplot::show();
	}

	void AveragePathLength(GraphAnalyzer* analyzer)
	{
		using namespace boost;
		using namespace boost::accumulators;
		using std::cout;
		using std::endl;
		int numNodes = analyzer->GetGraph().numberOfNodes();
		DoubleAccumulator acc;
		cout<< "Computing AveragePathLength" <<endl;
		analyzer->GetGraph().forNodes([analyzer, &acc,&numNodes](node v)
			{
				auto algo = analyzer->ComputeGraphDistance<Dijkstra>(v).get();
				for(auto result : algo.getDistances())
					acc(result);
				cout<< "Completed at: " << (double)((v/numNodes)*100) << endl;
			});
		cout << "Path measures" << endl;
		ShowAccumulatorsFeatures(acc, cout);
	}

	void ClusteringCoefficients(GraphAnalyzer* analyzer)
	{
		using namespace boost;
		using namespace boost::accumulators;
		using std::cout;
		using std::endl;
		auto algo = NetworKit::LocalClusteringCoefficient(analyzer->GetGraph(), true);
		algo.run();

		
		std::stringstream rep{};

		DoubleAccumulator acc;

		cout << "Clustering Coefficient" << endl;
		ShowAccumulatorsFeatures(acc, rep);
		
		for (auto& value : algo.scores())acc(value);
		auto hist = matplot::hist(algo.scores());
		hist->algorithm(matplot::histogram::binning_algorithm::automatic);
		hist->normalization(matplot::histogram::normalization::pdf);
		matplot::show();
		cout << rep.str() << endl;
	}





}

#endif // !CENTRALITIES_HPP

