#include "priorityQueue.h"

PriorityQueue::PriorityQueue(){
	pq = new deque<Vector>();//change to dequeue
	costs = new deque<double>();
}

void PriorityQueue::push(Vector node, double priority){
	bool inserted = false;
	for (int i = pq->size() - 1; i >= 0; i--){
		if (costs->at(i)>priority){
			if (i == pq->size() - 1){
				pq->push_back(node);
				costs->push_back(priority);
				inserted = true;
			}
			else{
				pq->insert(pq->begin() + i+1,node);
				costs->insert(costs->begin() + i + 1, priority);
				inserted = true;
			}
		}
	}
	if (!inserted){
		pq->push_front(node);
		costs->push_front(priority);
	}
}

Vector PriorityQueue::pop(){
	Vector back = Vector(pq->back());
	costs->pop_back();
	pq->pop_back();
	return back;
}

void PriorityQueue::update(Vector node, double newPriority){
	//for updating node inside
	int index = find(node);
	if (index != -1){
		pq->erase(pq->begin() + index);
		costs->erase(costs->begin() + index);
		push(node, newPriority);
	}
}

int PriorityQueue::find(Vector node){
	for (int i = 0; i < pq->size(); i++){
		if (node.x == pq->at(i).x && node.y == pq->at(i).y){
			return i;
		}
	}
	return -1;
}

