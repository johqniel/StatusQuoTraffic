#  plot.py
#  BridgeModel
#
#  Created by nielo on 12.05.25.
#


import matplotlib.pyplot as plt
import networkx as nx
import math
import os
import imageio


data_folder = os.path.join("data")  # go up one level, then into "data"


def plot_graph_large_test_in_circle(filename, subgraph_size, num_subgraphs,save_path=None):
    """
    Reads a graph from an edgelist file, groups nodes into subgraphs, and plots them in a circular layout.
    The edge color indicates the ratio of flow to capacity.

    Args:
        filename (str): The name of the edgelist file.
        subgraph_size (int): The desired size of each subgraph.
    """
    try:
        # Define custom positions for nodes within a single subgroup (relative coordinates)
        # This mapping assumes a subgraph_size of 15 and maps the relative node index (0-14)
        # to its (x, y) coordinate within that subgroup's local grid.
        #
        # Diagram mapping to coordinates:
        # -------------------------
        # |   | 1 | 4 | 7 | 11|   |  (Y=1)
        # -------------------------
        # | 0 |   |   | 8 | 12| 14|  (Y=0)
        # -------------------------
        # |   | 2 | 5 | 9 | 13|   |  (Y=-1)
        # -------------------------
        # |   |   | 3 | 6 | 10|   |  (Y=-2)
        # -------------------------
        #
        # X-coordinates roughly correspond to columns:
        # Col 0: Node 0
        # Col 1: Nodes 1, 2
        # Col 2: Nodes 3, 4, 5
        # Col 3: Nodes 6, 7, 8, 9
        # Col 4: Nodes 10, 11, 12, 13
        # Col 5: Node 14
        custom_subgroup_positions = {
            0: (0.0, 0.0),   # (X, Y)
            1: (1.0, 1.0),
            2: (1.0, -1.0),
            3: (2.0, -2.0),
            4: (2.0, 1.0),
            5: (2.0, -1.0),
            6: (3.0, -2.0),
            7: (3.0, 1.0),
            8: (3.0, 0.0),
            9: (3.0, -1.0),
            10: (4.0, -2.0),
            11: (4.0, 1.0),
            12: (4.0, 0.0),
            13: (4.0, -1.0),
            14: (5.0, 0.0)
        }
        # Define custom labels
        custom_labels = ["bike","public","car","bike-public","public-bike","car-public","walk"]  # Add "walk" to match the number of expected subgraphs
        file_path = os.path.join(data_folder, filename)
        print("Passing file_path = ", file_path)
    
        if not os.path.isfile(file_path):
            print(f"Error: File not found at {file_path}")
            return
    
        # Read the graph from the edgelist file.
        G = nx.read_edgelist(file_path, nodetype=int, data=(('weight', float), ('type', str), ('flow', int), ('capacity', int)), create_using=nx.DiGraph()) # Changed a and b to flow and capacity

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
            #group_pos = nx.circular_layout(group_nodes)
        
            # Adjust the position of the group (offset) to arrange groups in a larger circle
            offset_x, offset_y = group_positions[i]
            offset_x *= 4  # Scale the offset to spread out the groups
            offset_y *= 4
        
            #group_center = group_positions[i] * 4 # compute center of group
        
            # Shift positions of nodes in each group
            for node in group_nodes:
                #print(node)
                relative_node_index = node % subgraph_size
                # Get the base position from the custom_subgroup_positions
                # Use .get() with a default to handle cases where a node's relative index
                # might not be explicitly defined in custom_subgroup_positions (e.g., if subgraph_size > 15)
                base_x, base_y = custom_subgroup_positions.get(relative_node_index, (0.0, 0.0))

                # Apply the offset to the base position and store in the main 'pos' dictionary
                pos[node] = (base_x + offset_x, base_y + offset_y)
                #pos[node] = (0,0)
                #pos[node] = (group_pos[node][0] + offset_x, group_pos[node][1] + offset_y)
            

        num_nodes = len(nodes)
        num_subgraphs = math.ceil(num_nodes / subgraph_size)

        # Create subgraphs
        subgraphs = [list(nodes)[i * subgraph_size:(i + 1) * subgraph_size] for i in range(num_subgraphs)]



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
        if save_path:
            plt.savefig(save_path)
            plt.close()
        else:
            plt.show()

    except FileNotFoundError:
        print(f"Error: File not found at {file_path}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")


def plot_all_graphs(num_graphs, subgraph_size, num_subgraphs):
    for i in range(1, num_graphs + 1):
        filename = f"graph_{i}.txt"
        save_path = os.path.join("plots", f"graph_{i}.png")
        
        # Make sure output directory exists
        os.makedirs("plots", exist_ok=True)
        
        print(f"Plotting {filename} -> {save_path}")
        plot_graph_large_test_in_circle(filename, subgraph_size, num_subgraphs, save_path)

def create_animation(num_graphs, fps=29, output_folder = "animations"):
    images = []
    for i in range(1, num_graphs + 1):
        img_path = os.path.join("plots", f"graph_{i}.png")
        images.append(imageio.imread(img_path))
    output_path = os.path.join(output_folder, 'graph_animation.mp4')
    imageio.mimsave(output_path, images, fps=fps, codec = 'libx264')
    print("Animation saved as graph_animation.mp4")

if __name__ == "__main__":
    print("Looking for files in data folder")
    num_graphs = 29  # change to how many you have
    subgraph_size = 15
    num_subgraphs = 6
    
    plot_all_graphs(num_graphs, subgraph_size, num_subgraphs)
    create_animation(num_graphs, fps=2)



