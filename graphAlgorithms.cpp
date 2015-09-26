#include "graphAlgorithms.h"

using namespace std;

bool isObstacleEdge(int i, int j,
					const vector<Edge> &edges,
					Graph *graph)
{
	if(i < 2 || j < 2)
	{
		return false;
	}

	if(edges.at(i - 2).e1 == graph->getNodePos(j))
	{
		return true;
	}

	if(edges.at(j - 2).e1 == graph->getNodePos(i))
	{
		return true;
	}

	return false;
}

bool isVisibleFrom(int i, int j,
				   const vector<Edge> &edges,
				   Graph *graph)
{
	Vector u0(graph->getNodePos(i));
	Vector u1(graph->getNodePos(j));

	vector<Edge>::const_iterator itEdge = edges.begin();
	while(itEdge != edges.end())
	{
		Vector v0((*itEdge).e0);
		Vector v1((*itEdge).e1);

		++itEdge;
	}

	return false;
}

void createVisibilityGraph(const Vector &start,
						   const Vector &goal,
						   const vector<obstacle_t> &obstacles,
						   Graph *graph)
{
	graph->clear();

	graph->addNode(start);
	graph->addNode(goal);

	vector<Edge> obstacleEdges;

	vector<obstacle_t>::const_iterator itObstacle = obstacles.begin();
	while(itObstacle != obstacles.end())
	{
		const obstacle_t *obstacle = &(*itObstacle);

		for(int c = 0; c < obstacle->numCorners; ++c)
		{
			graph->addNode(Vector(obstacle->o_corner[c][0],
								  obstacle->o_corner[c][1]));

			int e0 = c;
			int e1 = (c + 1 == obstacle->numCorners ? 0 : c + 1);

			obstacleEdges.push_back(Edge(Vector(obstacle->o_corner[e0][0],
												obstacle->o_corner[e0][1]),
										 Vector(obstacle->o_corner[e1][0],
												obstacle->o_corner[e1][1])));
		}
		
		++itObstacle;
	}

	// Brute-force
	for(int i = 0; i < graph->getNumberNodes(); ++i)
	{
		for(int j = i + 1; j < graph->getNumberNodes(); ++j)
		{
			if(isObstacleEdge(i, j, obstacleEdges, graph))
			{
				graph->addEdge(i, j);
			}

			if(isVisibleFrom(i, j, obstacleEdges, graph))
			{
				graph->addEdge(i, j);
			}
		}
	}
}