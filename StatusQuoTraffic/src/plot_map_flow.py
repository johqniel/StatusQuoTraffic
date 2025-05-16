#  plot.py
#  BridgeModel
#
#  Created by nielo on 12.05.25.
#


import matplotlib.pyplot as plt
import networkx as nx
import math


def plot_graph_circle_deux(filename, subgraph_size, num_subgraphs):
    """
    Reads a graph from an edgelist file, groups nodes into subgraphs, and plots them in a circular layout.
    The edge color indicates the ratio of flow to capacity.

    Args:
        filename (str): The name of the edgelist file.
        subgraph_size (int): The desired size of each subgraph.
    """
    try:
        # Define custom labels
        custom_labels = ["bike","public","car","bike-public","public-bike","car-public","walk"]  # Add "walk" to match the number of expected subgraphs

    
        # Read the graph from the edgelist file.
        G = nx.read_edgelist(filename, nodetype=int, data=(('weight', float), ('type', str), ('flow', int), ('capacity', int)), create_using=nx.DiGraph()) # Changed a and b to flow and capacity

        # Check if the graph is empty
        if not G.nodes:
            print("Error: The graph is empty.  Check the input file.")
            return

            # Generate a layout for the nodes
        pos = {}
    
        #nodes = list(G.nodes())
        nodes = sorted(G.nodes())[subgraph_size : subgraph_size * (num_subgraphs + 1)]  # Ensure nodes are sorted for consistent grouping

    
        # Divide the nodes into groups based on size_of_subgraphs
        num_groups = len(nodes) // subgraph_size
        if len(nodes) % subgraph_size != 0:
            num_groups += 1  # If nodes don't divide evenly, add an extra group

        # Circular layout for the subgroups (arranging the centers of subgroups)
        group_positions = nx.circular_layout(range(num_groups))
    
        # Assign positions to nodes within each subgroup
        for i in range(num_groups):
            # Get the nodes for the current group
            group_nodes = nodes[i*subgraph_size : (i+1)*subgraph_size]
        
            # Circular layout for each group (arrange nodes within the group in a circle)
            group_pos = nx.circular_layout(group_nodes)
        
            # Adjust the position of the group (offset) to arrange groups in a larger circle
            offset_x, offset_y = group_positions[i]
            offset_x *= 4  # Scale the offset to spread out the groups
            offset_y *= 4
        
            #group_center = group_positions[i] * 4 # compute center of group
        
            # Shift positions of nodes in each group
            for node in group_nodes:
                #print(node)

                pos[node] = (group_pos[node][0] + offset_x, group_pos[node][1] + offset_y)
            

        num_nodes = len(nodes)
        num_subgraphs = math.ceil(num_nodes / subgraph_size)

        # Create subgraphs
        subgraphs = [list(nodes)[i * subgraph_size:(i + 1) * subgraph_size] for i in range(num_subgraphs)]

        # Create a circular layout for the subgraphs
        #pos = nx.circular_layout(G)

        # Create figure and axes
        fig, ax = plt.subplots(figsize=(12, 8))

        # Plot each subgraph
        for i, subgraph_nodes in enumerate(subgraphs):
            H = G.subgraph(subgraph_nodes)

            # --- Plotting the nodes and labels ---
            # Use custom labels, default to 'Subgraph {i+1}' if index is out of bounds
            label = custom_labels[i] if i < len(custom_labels) else f'Subgraph {i+1}'
            nx.draw_networkx_nodes(H, pos, node_color=f'C{i}', label=label) # Changed this line
            nx.draw_networkx_labels(H, pos, font_size=8)


        # Get edge colors based on flow/capacity ratio
        edge_colors = []
        for u, v, data in G.subgraph(nodes).edges(data=True):
            flow = data.get('flow', 0)
            capacity = data.get('capacity', 1)
            ratio = flow / capacity if capacity > 0 else 0
            normalized_ratio = max(0, ratio)
            edge_colors.append(normalized_ratio)

        # Use a color map
        edge_cmap = plt.colormaps['plasma_r']

        # --- Plotting the edges ---
        nx.draw_networkx_edges(G.subgraph(nodes), pos, edge_color=edge_cmap(edge_colors), edge_cmap=edge_cmap,  arrowsize=20)
        
        # Add a colorbar
        sm = plt.cm.ScalarMappable(cmap=edge_cmap, norm=plt.Normalize(vmin=0, vmax=1))
        fig.colorbar(sm, label='Flow/Capacity Ratio', ax=ax)

        plt.title(f"Graph with Subgraphs of Size {subgraph_size} and Edge Colors Indicating Flow/Capacity Ratio")
        plt.legend()
        plt.show()

    except FileNotFoundError:
        print(f"Error: File not found at {filename}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

# Call the function with filename and size_of_subgraphs
#plot_graph_subgroups("graph.txt", 7)  # Example: Group nodes into subgraphs of size 5
#plot_graph_subgroups_circle("graph.txt", 7)  # Example: Group nodes into subgraphs of size 5
plot_graph_circle_deux("graph_whole.txt", 7, 6)  # Example: Group nodes into subgraphs of size 5


