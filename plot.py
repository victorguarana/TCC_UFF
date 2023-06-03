import csv
import matplotlib.pyplot as plt
import networkx as nx

G = nx.DiGraph()
G2 = nx.DiGraph()
H = nx.path_graph(10)

with open('result.csv') as csv_file:
  csv_reader = csv.reader(csv_file, delimiter=';')
  for row in csv_reader:
    vehicle = row[0]
    origin = row[1]
    origin_x = float(row[2])
    origin_y = float(row[3])
    destiny = row[4]
    destiny_x = float(row[5])
    destiny_y = float(row[6])

    if vehicle == 'D':
      G2.add_node(origin, pos=(origin_x,origin_y))
      G2.add_node(destiny, pos=(destiny_x,destiny_y), node_color="red")
      G2.add_edge(origin, destiny)
    if vehicle == 'C':
      G.add_node(origin, pos=(origin_x,origin_y))
      G.add_node(destiny, pos=(destiny_x,destiny_y))
      G.add_edge(origin, destiny)
      

    # G.add_edges_from([(origin, destiny)], bold=True, color="red")

pos=nx.get_node_attributes(G,'pos')
pos2=nx.get_node_attributes(G2,'pos')

nx.draw(G2, pos2, with_labels=True, node_color="red")
nx.draw(G, pos, with_labels=True)
plt.show()
