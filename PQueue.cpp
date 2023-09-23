// PQueue.cpp
// Lucas Butler
// Function definitions for the PQueue class

#include "PQueue.h"
#include <functional>
#include <cmath>
#include "Graph.h"

// Constructor for the pqueue class
PQueue::PQueue(){};

// Reconstruct the heap
void PQueue::reconstruct(){

	int i = queue.size() - 1;	

	// Super safe way of ensure that the pqueue is constructed correctly everytime - I take NO chances IDC how slow
	while(i > -1){
		min_heapify(i);
		i--;
	}

}

// basic swap function to perform the swaps
void PQueue::swap(int i, int x){

	// swap the objects
	std::shared_ptr<node> temp = queue[i];
	queue[i] = queue[x];
	queue[x] = temp;
};

// min heapify
void PQueue::min_heapify(int i){

	// detemine the indices of the children
	int l = (2 * i) + 1;
	int r = (2 * i) + 2;
	int m = i;

		      
		// First check the priority and if they are equal then check the order ID
	if(l < queue.size() && queue[l]->dist < queue[m]->dist)	{
		m = l;
	}
		// Same thing but for the right node
	if(r < queue.size() && queue[r]->dist < queue[m]->dist) {
		m = r;
	}

		// ensure that there is a swap necessary
	if(m != i){
		swap(i, m);	
		min_heapify(m);
	}
};

// lets us know if the queue is empty or not
bool PQueue::empty(){
	if(queue.size() == 0) return true;
	return false;
};

// returns the size of queue
int PQueue::size(){
	return queue.size();
};

// Peeks at the next element in the queue
std::shared_ptr<node> PQueue::peek(){
	if(empty()) return nullptr;
	return queue[0];

};

// Adds an element to the queue
void PQueue::push(std::shared_ptr<node> object){
	
	// Adds element to the vector
	queue.push_back(object);
	
	// Super safe way of ensure that the pqueue is constructed correctly everytime - I take NO chances IDC how slow
	reconstruct();
}; 

// returns and removes the first element in the queue
std::shared_ptr<node> PQueue::pop(){

	// If there is nothing to return than return a nullptr and avoid a seg fault
	if(empty()) return nullptr;	
	
	// Return the root of the tree	
	std::shared_ptr<node> r = queue[0];
	
	// Remove the root from the tree	
	queue[0] = queue[size() - 1];
	queue.pop_back();

	// reheapify the tree then return from the function
	min_heapify(0);

	return r;
};

