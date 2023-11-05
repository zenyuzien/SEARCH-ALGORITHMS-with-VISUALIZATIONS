import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

with open('vis_data.txt', 'r') as file:
    lines = file.read().splitlines()


isPath = int(lines[-4])
num_nodes = list(map(int, lines[0].split()))
sg = list(map(int, lines[-1].split()))
specified_edges = list(map(int, lines[-2].split()))
color_change_order = list(map(int, lines[-3].split()))

if isPath == -2 : # -2 for alpha beta
    edges = []
    line_index = 1
    while True:
        edge_line = list(map(int, lines[line_index].split()))
        line_index += 1
        if edge_line[0] == -1:
            break
        edges.extend([(edge_line[i], edge_line[i + 1]) for i in range(0, len(edge_line), 2)])
else:
    edges = [tuple(map(int, line.split())) for line in lines[1:lines.index('-1')]]

G = nx.Graph()
if isPath == -2:
    G.add_nodes_from(num_nodes)
else:
    G.add_nodes_from(range(num_nodes[0]))
G.add_edges_from(edges)

for u, v in G.edges():
    G[u][v]['color'] = 'red'

if isPath == -2:
    node_colors = {node: 'red' for node in G.nodes}
else:    
    node_colors = ['red' for _ in range(num_nodes[0])]

fig, ax = plt.subplots()
pos = nx.spring_layout(G)

def update(frame):
    if frame == 0 :
        node_colors[ color_change_order[frame]  ] = 'green'
    elif frame == len(color_change_order):
        node_colors[ color_change_order[frame-1]  ] = 'red'
        if isPath != 0 : # 0 for BMS, no need to show path
            for i in range(0,len(specified_edges)-1):
                G[specified_edges[i]][specified_edges[i+1]]['color']='green'
                node_colors[specified_edges[i]]= 'yellow'
        node_colors[sg[0]]='green'
        node_colors[sg[1]]='green'
    elif frame > 0 :
        node_colors[ color_change_order[frame]  ] = 'green'
        node_colors[ color_change_order[frame-1]  ] = 'red'
    
        
    edge_colors = [G[u][v]['color'] for u, v in G.edges()]
    ax.clear()
    nc=[node_colors[node] for node in G.nodes]
    
    nx.draw(G, pos=pos, node_size=800,edge_color=edge_colors, node_color=nc, with_labels=True)

animation = FuncAnimation(fig, update, interval=750, frames=len(color_change_order) + 1, repeat=False)
plt.show()