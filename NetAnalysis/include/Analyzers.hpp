#pragma once
#include <networkit/graph/Graph.hpp>
#include <networkit/io/EdgeListReader.hpp>
#include <networkit/centrality/DegreeCentrality.hpp>
#include <networkit/centrality/Betweenness.hpp>
#include <networkit/centrality/Closeness.hpp>
#include <networkit/distance/BFS.hpp>
#include <networkit/distance/Dijkstra.hpp>
#include <networkit/distance/STSP.hpp>
#include <networkit/io/DotGraphWriter.hpp>
#include <networkit/auxiliary/Parallelism.hpp>
#include <networkit/community/CommunityDetectionAlgorithm.hpp>
#include <networkit/auxiliary/Parallel.hpp>
#include <networkit/community/PLM.hpp>
#include <future>
#include <iostream>

namespace NetAnalysis::GraphMeasures
{



	using namespace NetworKit;


	template<class T>
	std::future<T> ComputeAlgorithmAsync(Algorithm* const algo)
	{
		return std::async([algo]() {
			algo->run();
			return (T&)*algo;
			});
	}

	template<class T>
	std::future<T> CalculateCentralityMeasureAsync(Graph& graph)
	{
		static_assert(std::is_convertible<T*, NetworKit::Centrality*>::value);
		std::promise<T>* promise = new std::promise<T>();
		Centrality* algo = (Centrality*)new T{ graph };
		return ComputeAlgorithmAsync<T>(algo);
	}

	template<class T>
	std::future<T> DetectCommunitiesAsync(Graph& graph)
	{
		static_assert(std::is_convertible<T*, NetworKit::CommunityDetectionAlgorithm*>::value);
		CommunityDetectionAlgorithm* algo = new T{ graph };
		return ComputeAlgorithmAsync<T>(algo);
	}

	template<class T>
	std::future<T> ComputeGraphDistance(Graph& graph, node source)
	{
		static_assert(std::is_convertible<T*, NetworKit::SSSP*>::value);
		SSSP* algo = new T{ graph,source };
		return ComputeAlgorithmAsync<T>(algo);
	}

	template<class T>
	std::future<T> ComputeGraphDistance(Graph& graph, node source, node target)
	{
		static_assert(std::is_convertible<T*, NetworKit::SSSP*>::value);
		SSSP* algo = new T{ graph,source,target };
		return ComputeAlgorithmAsync<T>(algo);
	}

	


}
