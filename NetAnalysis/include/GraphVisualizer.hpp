#include <networkit/graph/Graph.hpp>
#include <ogdf/basic/Graph.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/planarity/SubgraphPlanarizer.h>
#include <ogdf/planarity/PlanarSubgraphFast.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
namespace NetAnalysis
{
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

}