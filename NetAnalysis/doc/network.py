
import networkx as nx
import networkit as nk



def GenGraphFromSubset(graph: nx.graph.Graph, community: list[int]) -> nx.Graph:
        subGraph = nx.Graph()
        subGraph.add_nodes_from(community)
        for node in community:
            for target in community:
                if graph.has_edge(node,target):
                    subGraph.add_edge(node,target)
                    pass
                pass
            pass
        return subGraph

