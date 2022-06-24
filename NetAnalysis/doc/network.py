#%% init
import networkit as nk
import networkx as nx
import matplotlib.pyplot as plt
#%% load graph

nk.graphio.EdgeListReader(",",0).read("./musae_git_edges.csv")

#%% Perform distance evaluation


