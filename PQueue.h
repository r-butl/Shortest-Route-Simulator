// PQueue.h
// Lucas Butler
// Class definition for the Priority Queue

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Graph.h"

#ifndef PQUEUE_H
#define PQUEUE_H

// Priority queue class
class PQueue{

	public:
	std::vector<std::shared_ptr<node>> queue;

	// basic swap function to perform the swaps
	void swap(int, int);

	// min heapify
	void min_heapify(int);

	// Constructor
	PQueue();

	// Destructor
	~PQueue(){};

	// print all of the elements in the vector
	void print();

	// lets us know if the queue is empty or not
	bool empty();
	
	// returns the size of queue
	int size();

	// Peeks at the next element in the queue
	std::shared_ptr<node> peek();

	// Adds an element to the queue
	void push(std::shared_ptr<node>);

	// returns and removes the first element in the queue
	std::shared_ptr<node> pop();

	// Reconstruct the head
	void reconstruct();

};

#endif
