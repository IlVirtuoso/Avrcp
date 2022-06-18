#pragma once
#include <networkit/io/DotPartitionWriter.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/write.hpp>
#include <boost/iostreams/read.hpp>
#include <networkit/graph/Graph.hpp>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
namespace NetAnalysis
{


	void DrawGraph(Agraph_t* g, GVC_t* context);
	void PlotGraph(NetworKit::Graph& graph);

	void PlotGraph(const NetworKit::Partition& partition, const NetworKit::Graph& graph);


}