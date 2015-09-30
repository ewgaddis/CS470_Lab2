#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "team.h"
#include "geometry.h"

#include <vector>
#include <deque>

class PriorityQueue {
public:
	//vector<Vector> *pq;
	//vector<double> *costs;
	deque<Vector> *pq;
	deque<double> *costs;
	PriorityQueue();

		void push(Vector node,double priority);
		Vector pop();
		Vector at(int index);
		void update(Vector node,double newPriority);
		int find(Vector node);


private:
	
};

#endif