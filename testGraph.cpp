#include "graph.h"

#include <iostream>
#include <conio.h>

using namespace std;

void displayGraph(const Graph &graph)
{
	for(int i = 0; i < graph.getNumberNodes(); ++i)
	{
		cout << "Node #" << i << ": " << graph.getNodePos(i) << endl;
	}

	cout << "Adjacency Matrix" << endl;

	for(int i = 0; i < graph.getNumberNodes(); ++i)
	{
		cout << "[";

		for(int j = 0; j < graph.getNumberNodes(); ++j)
		{
			cout << (graph.edgeExist(i, j) ? 1 : 0);

			if(j != graph.getNumberNodes() - 1)
			{
				cout << " ";
			}
		}

		cout << "]" << endl;
	}
}

int main()
{
	Graph graph;

	graph.addNode(Vector(0.0, 0.0));
	graph.addNode(Vector(2.0, 1.0));
	graph.addNode(Vector(-1.0, 3.0));

	graph.addEdge(0, 1);

	displayGraph(graph);

	graph.addNode(Vector(4.0, -1.0));

	graph.addEdge(3, 1);

	displayGraph(graph);

	while(!_kbhit());
	return 0;
}