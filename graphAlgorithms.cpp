#include "graphAlgorithms.h"

#include <iostream>

using namespace std;

bool isObstacleEdge(int i, int j,
					const vector<Edge> &edges,
					Graph *graph)
{
	// Only checks nodes that are corners of obstacles
	if(i < 2 || j < 2)
	{
		return false;
	}

	// If there is an edge from node i to j, then
	// this is an obstacle edge.
	if(edges.at(i - 2).e1 == graph->getNodePos(j))
	{
		return true;
	}

	// If there is an edge from node j to i, then
	// this is an obstacle edge.
	if(edges.at(j - 2).e1 == graph->getNodePos(i))
	{
		return true;
	}

	// There is no edge from node i to j and vice versa.
	return false;
}

bool areCornersOfSameObstacle(int i, int j,
							  const vector<obstacle_t> &obstacles)
{
	// Ignores the start and goal nodes since they are not
	// corners of an obstacle
	if(i == 0 || i == 1 || j == 0 || j == 1)
	{
		return false;
	}

	// Gets corner indices
	int c0 = i - 2;
	int c1 = j - 2;

	// Used to determine the range of corners that belong
	// to the obstacle
	int cornersStart = 0;
	int cornersEnd   = 0;

	vector<obstacle_t>::const_iterator itObstacle = obstacles.begin();
	while(itObstacle != obstacles.end())
	{
		cornersEnd += (*itObstacle).numCorners;

		// If nodes i and j are within the range of corners
		// of this obstacle, then they belong to the same
		// obstacle.
		if(c0 >= cornersStart && c0 < cornersEnd &&
		   c1 >= cornersStart && c1 < cornersEnd)
		{
			return true;
		}

		cornersStart = cornersEnd;

		++itObstacle;
	}

	// The nodes i and j do not belong to the same obstacle.
	return false;
}

bool isVisibleFrom(int i, int j,
				   const vector<Edge> &edges,
				   Graph *graph)
{
	// Gets the positions of the line segment from node i to j.
	Vector u0(graph->getNodePos(i));
	Vector u1(graph->getNodePos(j));

	// Checks each obstacle edge.
	vector<Edge>::const_iterator itEdge = edges.begin();
	while(itEdge != edges.end())
	{
		// Gets the positions of the line segment from
		// one corner to the other adjacent corner.
		Vector v0((*itEdge).e0);
		Vector v1((*itEdge).e1);

		// Ignores the obstacle edge if any of the positions
		// of its corners are the positions of either node
		// i or j.
		if(u0 == v0 || u0 == v1 || u1 == v0 || u1 == v1)
		{
			++itEdge;
			continue;
		}

		// If there is an intersection of the line from node
		// i to j and the obstacle edge line, then nodes i
		// and j cannot see eachother.
		if(doLinesIntersect(u0, u1, v0, v1))
		{
			return false;
		}

		++itEdge;
	}

	// Nodes i and j see eachother.
	return true;
}

void createVisibilityGraph(const Vector &start,
						   const Vector &goal,
						   const vector<obstacle_t> &obstacles,
						   Graph *graph)
{
	// Clears the nodes and edges in the graph.
	graph->clear();

	// Adds the start and goal nodes first
	graph->addNode(start);
	graph->addNode(goal);

	// Contains a list of obstacle edges
	vector<Edge> obstacleEdges;

	// Goes through each obstacle.
	vector<obstacle_t>::const_iterator itObstacle = obstacles.begin();
	while(itObstacle != obstacles.end())
	{
		const obstacle_t *obstacle = &(*itObstacle);

		// Goes through each corner of the obstacle.
		for(int c = 0; c < obstacle->numCorners; ++c)
		{
			// Adds the corner as a node into the graph.
			graph->addNode(Vector(obstacle->o_corner[c][0],
								  obstacle->o_corner[c][1]));

			// Adds the obstacle edge from this corner to the
			// next corner.
			int e0 = c;
			int e1 = (c + 1 == obstacle->numCorners ? 0 : c + 1);

			obstacleEdges.push_back(Edge(Vector(obstacle->o_corner[e0][0],
												obstacle->o_corner[e0][1]),
										 Vector(obstacle->o_corner[e1][0],
												obstacle->o_corner[e1][1])));
		}
		
		++itObstacle;
	}

	// Brute-force visibility check.
	for(int i = 0; i < graph->getNumberNodes(); ++i)
	{
		for(int j = i + 1; j < graph->getNumberNodes(); ++j)
		{
			// If the edge from node i to j is an obstacle
			// edge, then adds its into the graph
			if(isObstacleEdge(i, j, obstacleEdges, graph))
			{
				graph->addEdge(i, j);
			}
			else if(!areCornersOfSameObstacle(i, j, obstacles) &&
					isVisibleFrom(i, j, obstacleEdges, graph))
			{
				// If nodes i and j are not corners of the
				// same obstacle and they can see eachother,
				// then adds the edge from node i to j into
				// the graph.
				graph->addEdge(i, j);
			}
		}
	}
}

DFSearch::DFSearch(const Graph &g) : GraphSearch(g)
{
	frontier.push(0);
}

bool DFSearch::search(int iterations)
{
	while(!frontier.empty() && iterations > 0)
	{
		int curNode = frontier.top();
		frontier.pop();

		if(isVisited(curNode))
		{
			continue;
		}

		setVisited(curNode);

		vector<int> nodes;
		graph->getNodesTo(curNode, &nodes);

		vector<int>::iterator itNode = nodes.begin();
		while(itNode != nodes.end())
		{
			if(!isVisited(*itNode))
			{
				frontier.push(*itNode);
				setParent(*itNode, curNode);
			}

			++itNode;
		}

		--iterations;
	}

	return false;
}

void DFSearch::getFrontier(std::vector<int> *nodes) const
{
	nodes->clear();

	stack<int> s(frontier);

	while(!s.empty())
	{
		nodes->push_back(s.top());
		s.pop();
	}
}