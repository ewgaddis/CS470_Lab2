#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "graph.h"
#include "geometry.h"
#include "team.h"

#include <vector>

void createVisibilityGraph(const Vector &start,
						   const Vector &goal,
						   const std::vector<obstacle_t> &obstacles,
						   Graph *graph);

#endif