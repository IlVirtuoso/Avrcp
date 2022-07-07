#pragma once

#ifndef GRAPHANALYZER_H
#define GRAPHANALYZER_H
#include <future>
#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <networkit/centrality/Centrality.hpp>
#include <networkit/community/CommunityDetectionAlgorithm.hpp>
#include <networkit/components/ComponentDecomposition.hpp>
#include <networkit/distance/SSSP.hpp>
#include <networkit/distance/STSP.hpp>
#include <networkit/edgescores/TriangleEdgeScore.hpp>
#include <networkit/graph/Graph.hpp>
#include <networkit/io/EdgeListReader.hpp>
#include <string>
#include <vector>

namespace NetAnalysis::GraphMeasures
{

    using namespace NetworKit;

    template <typename T> using Task = std::future<T>;

    class GraphAnalyzer
    {
      private:
        Graph &graph;
        template <class T> Task<T> ComputeAlgorithmAsync(Algorithm *const algo)
        {
            return std::async([algo]() {
                algo->run();
                return (T &)algo;
            });
        }

      public:
        GraphAnalyzer() : graph{*new NetworKit::Graph()}
        {
        }

        void LoadGraph(std::string fileName)
        {
            this->graph = EdgeListReader(',', (NetworKit::node)0).read(fileName);
        }

        void PopulateFeatures(std::string filename)
        {
            std::ifstream featuresFile(filename);
            Json::Value featureValues{};
            featuresFile >> featureValues;

            auto attr = this->graph.nodeAttributes().attach<std::vector<int>>("features");
            graph.forNodes([featureValues, &attr, this](node v) {
                auto ref = featureValues[std::to_string(v)];
                std::vector<int> features{};
                for (int i = 0; i < ref.size(); i++)
                {
                    features.push_back(ref[i].asInt());
                }
                attr.set(v, features);
            });
        }

        void PopulateTargets(std::string filename)
        {
        }

        template <class T> Task<T> CalculateCentralityMeasureAsync()
        {
            static_assert(std::is_convertible<T *, NetworKit::Centrality *>());
            std::promise<T> *promise = new std::promise<T>();
            Centrality *algo = (Centrality *)new T(graph);
            return ComputeAlgorithmAsync<T>(algo);
        }

        template <class T> T ExecuteCommunityDetectionAlgorithm()
        {
            static_assert(std::is_convertible<T *, NetworKit::CommunityDetectionAlgorithm *>::value);
            T algo(graph);
            algo.run();
            return algo;
        }

        template <class T> Task<T> ComputeGraphDistance(node source)
        {
            static_assert(std::is_convertible<T *, NetworKit::SSSP *>::value);
            SSSP *algo = new T{graph, source};
            return ComputeAlgorithmAsync<T>(algo);
        }

        template <class T> Task<T> ComputeGraphDistance(node source, node target)
        {
            static_assert(std::is_convertible<T *, NetworKit::STSP *>::value);
            SSSP *algo = new T{graph, source, target};
            return ComputeAlgorithmAsync<T>(algo);
        }

        template <class T> Task<T> ComputeComponentsDecomposition()
        {
            static_assert(std::is_convertible<T *, NetworKit::ComponentDecomposition *>::value);
            ComponentDecomposition *algo = new T{graph};
            return ComputeAlgorithmAsync<T>(algo);
        }

        const Graph &GetGraph() const
        {
            return this->graph;
        }
        void SetGraph(Graph &graph)
        {
            this->graph = graph;
        }

        double Density() const
        {
            return (double)graph.numberOfNodes() / (double)graph.numberOfEdges();
        }

        std::vector<NetworKit::count> Triangles()
        {
            TriangleEdgeScore edgeScore{this->GetGraph()};
            graph.indexEdges();
            edgeScore.run();
            return edgeScore.scores();
        }
    };

} // namespace NetAnalysis::GraphMeasures

#endif // !GRAPHANALYZER_H
