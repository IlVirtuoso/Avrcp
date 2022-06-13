#pragma once
#include <networkit/graph/Graph.hpp>
#include <ogdf/basic/Graph.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/planarity/SubgraphPlanarizer.h>
#include <ogdf/planarity/PlanarSubgraphFast.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/energybased/FMMMLayout.h>
namespace NetAnalysis
{
	using namespace ogdf;
	ogdf::Graph* ConvertGraph(const NetworKit::Graph& graph)
	{
		ogdf::Graph* newGraph = new ogdf::Graph();
		std::vector<ogdf::node> createdNodes{};
		graph.forNodes([&createdNodes,newGraph](NetworKit::node v) {
			createdNodes.push_back(newGraph->newNode(v));
			});
		graph.forEdges([newGraph,&createdNodes](NetworKit::node u, NetworKit::node v) {
			newGraph->newEdge(createdNodes[u], createdNodes[v]);
			});
		return newGraph;
	}

	const std::string& EnergyLayout(Graph& graph)
	{
		return std::string{};
	}

	void EnergyLayout(const Graph* graph, std::string fileName)
	{
		GraphAttributes GA(*graph);
		for (node v : graph->nodes)
			GA.width(v) = GA.height(v) = 5.0;

		FMMMLayout fmmm;

		fmmm.useHighLevelOptions(true);
		fmmm.unitEdgeLength(15.0);
		fmmm.newInitialPlacement(true);
		fmmm.qualityVersusSpeed(FMMMOptions::QualityVsSpeed::GorgeousAndEfficient);

		fmmm.call(GA);
		GraphIO::write(GA, fileName, GraphIO::writeGML);
		GraphIO::write(GA, fileName, GraphIO::drawSVG);
	}

}