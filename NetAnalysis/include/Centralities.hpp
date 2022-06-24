#pragma once
#ifndef CENTRALITIES_HPP
#define CENTRALITIES_HPP

#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include "GraphAnalyzer.hpp"
#include <networkit/centrality/LocalClusteringCoefficient.hpp>
#include <networkit/centrality/Betweenness.hpp>
#include <networkit/centrality/Closeness.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/distance/Dijkstra.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/container/vector.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/container/map.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <filesystem>
#include "Plotter.hpp"
namespace NetAnalysis::Routines
{
	using namespace NetAnalysis::GraphMeasures;
	//void PlotCentralityMeasures(NetworKit::Graph& graph);


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
		accumulator_set<double,stats<tag::mean,tag::min,tag::max,tag::variance>> acc;
		for (auto score : algo.scores()) acc(score);
		out << "Score Mean: " << mean(acc) << "\n";
		out << "Score Max: " << max(acc) << "\n";
		out << "Score Min: " << min(acc) << "\n";
		out << "Score variance: " << variance(acc) << "\n";
		out << "Teoretical maximum: " << algo.maximum() << "\n";

		auto hist = GeneratePlot();
		auto histg = PlotCountHistogram(algo.scores(), 20, hist, true, Qt::GlobalColor::magenta);

		hist->xAxis->scaleRange(2);
		hist->savePng(path + "/" + name + "_histogram.png", 1920, 1080);






	}

	void AnalyzeCentrality(GraphAnalyzer* analyzer)
	{
		auto btwTask = analyzer->CalculateCentralityMeasureAsync<Betweenness>();
		auto clsTask = analyzer->CalculateCentralityMeasureAsync<Closeness>();
		auto degTask = analyzer->CalculateCentralityMeasureAsync<DegreeCentrality>();
		DegreeCentrality degree = degTask.get();
		ShowCentralityResults(degree);

		Closeness closeness = clsTask.get();
		ShowCentralityResults(closeness);

		Betweenness btw = btwTask.get();
		ShowCentralityResults(btw);


	}

	void AveragePathLength(GraphAnalyzer * analyzer)
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



#endif // !CENTRALITIES_HPP

