#pragma once
#include <networkit/graph/Graph.hpp>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
namespace NetAnalysis
{


	void DrawGraph(Agraph_t* g, GVC_t* context);
	void PlotGraph(NetworKit::Graph& graph);
	

}