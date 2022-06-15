#include "GraphVisualizer.hpp"
#include "GraphAnalyzer.hpp"
#include <networkit/io/DotGraphWriter.hpp>
namespace NetAnalysis
{


	void DrawGraph(Agraph_t* g, GVC_t* context)
	{

		gvRender(context, g, "svg", stdout);
	}

	void PlotGraph(NetworKit::Graph& graph)
	{
		NetworKit::DotGraphWriter().write(graph, "graph.dot");
		std::ifstream* stream = new std::ifstream();
		stream->open("graph.dot");
		char* str = new char[1024];
		std::string result = "";
		while (stream->readsome(str, 1024) != 0)
		{
			result += str;
			str = new char[1024];
		}
		Agraph_t* G;
		GVC_t* gvc;
		gvc = gvContext(); /* library function */
		G = agmemread(result.c_str());
		gvLayout(gvc, G, "dot"); /* library function */
		DrawGraph(G, gvc);
		gvFreeLayout(gvc, G); /* library function */
		agclose(G); /* library function */
		gvFreeContext(gvc);
	}


}