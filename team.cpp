#include "team.h"

#include "gnuplotter.h"
#include "potentialFields.h"
#include "graph.h"
#include "graphAlgorithms.h"
#include "dumbAgent.h"
#include "pdAgent.h"

#include <vector>

using namespace std;

BZRC *team;
DumbAgent *dumb1;
DumbAgent *dumb2;
DumbAgent *dumb3;
PDAgent *pd1;
vector <PDAgent*> agents;

void world_init(BZRC *my_team)
{
	team = my_team;
	//dumb1 = new DumbAgent(team, 0);
	//dumb2 = new DumbAgent(team, 1);
	//dumb3 = new DumbAgent(team, 2);
	//pd1 = new PDAgent(team, 0);
	/*agents = vector<PDAgent*>();
	for (int i = 0; i < 3; i++)
	{
		agents.push_back(new PDAgent(team, i));
		//agents.at(i) = new PDAgent(team, i);
	}*/

}

void robot_pre_update()
{
}

bool robot_update()
{
	//dumb1->Update();
	//dumb2->Update();
	//dumb3->Update();
	//pd1->Update();
	/*for (int i = 0; i < agents.size(); i++)
	{
		string color;
		if (i % 3 == 0){
			color = "red";
		}
		else if (i % 3 == 1)
			color = "blue";
		if (i % 3 == 2)
			color = "purple";

		agents.at(i)->Update(color);
	}*/
	vector<tank_t> tanks;
	team->get_mytanks(&tanks);

	vector<flag_t> flags;
	team->get_flags(&flags);

	vector<obstacle_t> obstacles;
	team->get_obstacles(&obstacles);

	Graph graph;
	
	createVisibilityGraph(Vector(tanks.at(0).pos[0], tanks.at(0).pos[1]),
						  Vector(flags.at(0).pos[0], flags.at(0).pos[1]),
						  obstacles, &graph);

	GraphSearch *search = new BFSearch(graph);
	search->search(100);

	GNUPlotter plotter;

	plotter.createFile("./Data/dfs.gpi", "Depth-First Search");

	plotter.drawGraph(graph);
	plotter.drawGraphSearch(graph, search);

	plotter.finishFile();

	delete search;

	return false;
}

void robot_post_update()
{
}