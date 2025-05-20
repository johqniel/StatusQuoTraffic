#  plot.py
#  BridgeModel
#
#  Created by nielo on 12.05.25.
#


import matplotlib.pyplot as plt
import networkx as nx


# Function to read the graph and group the nodes
def plot_graph_circle_deux(filename, size_of_subgraphs):
    #G = nx.read_edgelist(filename, nodetype=int)
    #G = nx.read_edgelist(filename, nodetype=int, create_using=nx.DiGraph())
    G = nx.read_edgelist(filename, nodetype=int, data=(('weight', float), ('type', str), ('a', int), ('b', int)), create_using=nx.DiGraph())
    # directed graph :)
    
    plt.figure(figsize=(10, 10)) # i have it up here to ensure that everything i want to plot is included in the figure.

    
    # Define the transport types
    transport_types = ["bike", "public", "car", "bike public", "public bike", "car public", "walk"]

    
    # Check if the graph has nodes and edges
    if G.number_of_nodes() == 0 or G.number_of_edges() == 0:
        print("Graph is empty.")
        return

    # Generate a layout for the nodes
    pos = {}
    #nodes = list(G.nodes())
    nodes = sorted(G.nodes())[7:]  # Ensure nodes are sorted for consistent grouping

    
    # Divide the nodes into groups based on size_of_subgraphs
    num_groups = len(nodes) // size_of_subgraphs
    if len(nodes) % size_of_subgraphs != 0:
        num_groups += 1  # If nodes don't divide evenly, add an extra group

    # Circular layout for the subgroups (arranging the centers of subgroups)
    group_positions = nx.circular_layout(range(num_groups))
    
    # Assign positions to nodes within each subgroup
    for i in range(num_groups):
        # Get the nodes for the current group
        group_nodes = nodes[i*size_of_subgraphs : (i+1)*size_of_subgraphs]
        
        # Circular layout for each group (arrange nodes within the group in a circle)
        group_pos = nx.circular_layout(group_nodes)
        
        # Adjust the position of the group (offset) to arrange groups in a larger circle
        offset_x, offset_y = group_positions[i]
        offset_x *= 4  # Scale the offset to spread out the groups
        offset_y *= 4
        
        #group_center = group_positions[i] * 4 # compute center of group
        
        # Shift positions of nodes in each group
        for node in group_nodes:
            pos[node] = (group_pos[node][0] + offset_x, group_pos[node][1] + offset_y)
            
        #plt.text(0,0,"hello")
        plt.text(offset_x,offset_y, transport_types[i], fontsize=8, ha='center', va='center', fontweight='bold', color='darkgreen')

    # Draw the graph with the adjusted positions
    nx.draw(G.subgraph(nodes), pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=500, font_size=10, font_weight='bold', arrows=True, arrowsize=20, connectionstyle="arc3,rad=0.1")
    
    # Display the plot
    plt.title('Graph with Nodes Grouped and Subgroups Arranged in a Circle')
    print("plot in circles.")
    plt.show()



# Call the function with filename and size_of_subgraphs
#plot_graph_subgroups("graph.txt", 7)  # Example: Group nodes into subgraphs of size 5
#plot_graph_subgroups_circle("graph.txt", 7)  # Example: Group nodes into subgraphs of size 5
plot_graph_circle_deux("graph_map.txt", 7)  # Example: Group nodes into subgraphs of size 5


