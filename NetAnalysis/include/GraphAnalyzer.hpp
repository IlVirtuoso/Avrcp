#pragma once
#include <networkit/graph/Graph.hpp>
#include <networkit/centrality/Centrality.hpp>
#include <networkit/distance/STSP.hpp>
#include <networkit/distance/SSSP.hpp>
#include <networkit/community/CommunityDetectionAlgorithm.hpp>
#include <future>
#include <iostream>

namespace NetAnalysis::GraphMeasures
{
	using namespace NetworKit;
	
	template<typename T>
	using Task = std::future<T>;

	class GraphAnalyzer
	{
	private:
		Graph& graph;


		template<class T>
		Task<T> ComputeAlgorithmAsync(Algorithm* const algo)
		{
			return std::async([algo]()
				{
					algo->run();
					return (T&)*algo;
				});
		}

	public:


		GraphAnalyzer(Graph & g): graph{g}{}


		template<class T>
		Task<T> CalculateCentralityMeasureAsync()
		{
			static_assert(std::is_convertible<T*, NetworKit::Centrality*>());
			std::promise<T>* promise = new std::promise<T>();
			Centrality* algo = (Centrality*)new T(graph);
			return ComputeAlgorithmAsync<T>(algo);
		}

		template<class T>
		Task<T> ExecuteCommunityDetectionAlgorithm()
		{
			static_assert(std::is_convertible<T*, NetworKit::CommunityDetectionAlgorithm*>::value);
			CommunityDetectionAlgorithm* algo = new T{ graph };
			return ComputeAlgorithmAsync<T>(algo);
		}

		template<class T>
		Task<T> ComputeGraphDistance(node source)
		{
			static_assert(std::is_convertible<T*, NetworKit::SSSP*>::value);
			SSSP* algo = new T{ graph,source };
			return ComputeAlgorithmAsync<T>(algo);
		}

		template<class T>
		Task<T> ComputeGraphDistance(node source, node target)
		{
			static_assert(std::is_convertible<T*, NetworKit::STSP*>::value);
			SSSP* algo = new T{ graph,source,target };
			return ComputeAlgorithmAsync<T>(algo);
		}


	};




	
	
	
}
