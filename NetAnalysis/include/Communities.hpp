#pragma once
#ifndef COMMUNITIES_HPP
#define COMMUNITIES_HPP
#include "GraphVisualizer.hpp"
#include "Plotter.hpp"
#include <networkit/community/PLM.hpp>
#include <networkit/community/PLP.hpp>
#include <filesystem>
#include <networkit/community/Modularity.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/array.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <networkit/io/DotPartitionWriter.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <networkit/community/LocalCommunityEvaluation.hpp>

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

		QCustomPlot* histogram = GeneratePlot();
		QCustomPlot* chart = GeneratePlot();
		histogram->setWindowTitle("Histogram: Size of cluster frequency");
		auto histg = PlotCountHistogram(values, 10, histogram, 5, true, Qt::GlobalColor::red);
		histogram->setInteractions(QCP::Interaction::iSelectPlottables);
		histogram->xAxis->scaleRange(2.0);
		histogram->yAxis->scaleRange(1.5);
		histogram->showMaximized();
		histogram->savePng(chartFolder + "/hist_cluster_size.png", 1920, 1080, 2.0);


		auto chartg = Plot(ids, values, chart, Qt::GlobalColor::red);
		chart->rescaleAxes();
		chart->xAxis->scaleRange(3);
		chart->showMaximized();
		chart->savePng(chartFolder + "/id_cluster_size.png", 1920, 1080, 2.0);

	}


	void ExecuteCommunityAnalysis(GraphAnalyzer* analyzer)
	{
		std::filesystem::create_directories("charts/PLM");
		auto comm = analyzer->ExecuteCommunityDetectionAlgorithm<NetworKit::PLM>();
		NetAnalysis::Routines::ShowCommunityAlgorithmData(comm, analyzer->GetGraph(), "./charts/PLM");

		std::filesystem::create_directories("charts/PLP");
		auto labelProp = analyzer->ExecuteCommunityDetectionAlgorithm<NetworKit::PLP>();
		NetAnalysis::Routines::ShowCommunityAlgorithmData(labelProp, analyzer->GetGraph(), "./charts/PLP");

		PlotGraph(comm.getPartition(), analyzer->GetGraph());
	}

}

#endif
