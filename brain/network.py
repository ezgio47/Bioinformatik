# Visualisierung von Gehirnnetzwerken.


import networkx as nx
import matplotlib.pyplot as plt 

# Ein einfaches Netzwerk erstellen
G = nx.Graph()

# Knoten und Kanten hinzufügen
G.add_nodes_from(["Frontal","Parietal", "Occipital", "Temporal"]) 
G.add_edges_from([("Frontal", "Parietal"), ("Frontal", "Temporal"), ("Temporal", "Occipital")])
# Frontal –– Temporal –– Occipital
#    |
# Parietal

# Das Netzwerk visualisieren
pos = nx.spring_layout(G) # Position der Knoten
nx.draw(G, pos, with_labels=True, node_size=2000, node_color='lightblue', font_size=15, font_weight='bold', edge_color='gray')
plt.title('Brain Network Visualization')
plt.show()



















