#pragma once
#ifndef GRAPHANALYZER_H
#define GRAPHANALYZER_H


#include <networkit/graph/Graph.hpp>
#include <networkit/centrality/Centrality.hpp>
#include <networkit/distance/STSP.hpp>
#include <networkit/distance/SSSP.hpp>
#include <networkit/components/ComponentDecomposition.hpp>
#include <networkit/community/CommunityDetectionAlgorithm.hpp>
#include <networkit/io/EdgeListReader.hpp>
#include <networkit/edgescores/TriangleEdgeScore.hpp>
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


		GraphAnalyzer() : graph{ *new NetworKit::Graph() }
		{

		}

		void LoadGraph(std::string fileName)
		{
			this->graph = EdgeListReader(',', (NetworKit::node)0).read(fileName);
		}

		template<class T>
		Task<T> CalculateCentralityMeasureAsync()
		{
			static_assert(std::is_convertible<T*, NetworKit::Centrality*>());
			std::promise<T>* promise = new std::promise<T>();
			Centrality* algo = (Centrality*)new T(graph);
			return ComputeAlgorithmAsync<T>(algo);
		}

		template<class T>
		T ExecuteCommunityDetectionAlgorithm()
		{
			static_assert(std::is_convertible<T*, NetworKit::CommunityDetectionAlgorithm*>::value);
			T algo(graph);
			algo.run();
			return algo;
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

		template<class T>
		Task<T> ComputeComponentsDecomposition()
		{
			static_assert(std::is_convertible<T*, NetworKit::ComponentDecomposition*>::value);
			ComponentDecomposition* algo = new T{ graph };
			return ComputeAlgorithmAsync<T>(algo);
		}


		const Graph& GetGraph() const { return this->graph; }
		void SetGraph(Graph& graph) { this->graph = graph; }

		double Density() const
		{
			return graph.numberOfNodes() / graph.numberOfEdges();
		}

		std::vector<NetworKit::count> Triangles()
		{

			TriangleEdgeScore edgeScore{ this->GetGraph() };
			graph.indexEdges();
			edgeScore.run();
			return edgeScore.scores();

		}

	};


}



#endif // !GRAPHANALYZER_H
