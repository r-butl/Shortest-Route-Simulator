// Graph.cpp
// Lucas Butler
// Function defintions for a graph class

#include "Graph.h"
#include "PQueue.h"
#include <limits.h>
#include <queue>
using namespace std;

// constructor
Graph::Graph(int st, int en){

	end = en;
	start = st;
};

// print nodes
void Graph::printNodes(){
	printf("\n");	
	for(auto n : nodes){
		printf("node: %d dist: %d\n", n.first, n.second->dist);
	}
	printf("\n");
}

// adds a node to the graph
void Graph::addNode(int i, bool c){

		// Create a new node		
		auto n = std::make_shared<node>(i, c);

		// Add it to the nodes vector
		nodes[n->id] = n;
}

// Take the incoming edges and assign it to the nodes	
void Graph::addEdge(int src, int dest, int weight){

		// protection from duplications
		for(auto e : nodes[src]->edges) if( e.second.weight == weight && e.second.dest == dest) return;
		for(auto e : nodes[dest]->edges) if( e.second.weight == weight && e.second.dest == src) return;
		
		// direction 1	
		edge e(dest, weight);
		nodes[src]->edges[e.dest] = e;

		// direction 2
		edge f(src, weight);
		nodes[dest]->edges[f.dest] = f;
}

// Print out the adjacency list
void Graph::adjList(){

	if(nodes.empty()) return;

	// Iterate through each node and prints its neighbors
		for(auto n : nodes){
			printf("%d: ", n.first); // print the id of the node

			// Iterate through the node's edges
			for(auto e : n.second->edges){
				printf("(%d, %d) ", e.second.dest, e.second.weight); // print the id of the destination
			}
			printf("\n");
		}
}

// Function that returns if the two id's passed are neighbors
bool Graph::isNeighbor(int n, int v){

	// Check the nodes in u to see if v exists
	if(nodes.count(n)) return false;

	if(nodes[n]->edges.size() == 0) return false; // no neighbors
	
	for(int i = 0; i < nodes[n]->edges.size(); i++){
		// compare IDs
		if(v == nodes[n]->edges[i].dest) return true;
	}

	return false;
}

// Depth first search
void Graph::DFS(){

	if(nodes.size() == 0) return;

	// Iterate through the nodes and update their contents
	for(auto n : nodes){
		// reset each of the nodes
		n.second->visited = false;
		n.second->predecessor = nullptr;
		n.second->discovered = -1;
		n.second->finished = -1;
	}

	int time = 0;

	// Visit all the nodes in the graph
	for(auto n : nodes){
		if(n.second->visited == false){
			time = DFSVisit(n.second, time);
		}
	}
}

// DFS visit
int Graph::DFSVisit(std::shared_ptr<node> s, int time){

	// Start by incrementing the time
	time = time + 1;
	s->discovered = time;
	s->visited = true;

	// Iterate through the neighbors and for ones that haven't been visited, visit
	for(auto f : s->edges){
		int n = f.second.dest;
		if(nodes[n]->visited == false){
			nodes[n]->predecessor = s;
			time = DFSVisit(nodes[n], time);
		}
	}

	// update finish times
	time = time + 1;
	s->finished = time;
	return time;
}

// BFS 
void Graph::BFS(int s){

	if(nodes.empty()) return;

	// Set up the search 
	for(auto n : nodes){
		n.second->dist = INT_MAX;
		n.second->visited = false;
		n.second->predecessor = nullptr;
	}

	// set up the algorithm
	int distance = 0;
	nodes[s]->dist = distance;
	nodes[s]->visited = true;
	
	// Queue of IDs
	std::queue<int> q;
	q.push(s);

	// run the algo
	while(q.size() > 0){

		int u = q.front();	
		q.pop();

		// iterate through the neighbors and update the ones that havent been visited
		for(auto n : nodes[u]->edges){
			// access the node from the graph and not through a neighbor
			int id = n.second.dest;	
			// Traverse to the node if it not yet has been done
			if(nodes[id]->visited == false){					
				nodes[id]->dist = nodes[u]->dist + n.second.weight;
				nodes[id]->visited = true;
				nodes[id]->predecessor = nodes[u];					
				q.push(id);
			}
		}
	}
}

// An implementation of Dijkstras algorithm
void Graph::Dijkstras(int s){

	if(nodes.find(s) == nodes.end()) return;

	// Iterate through all nodes and update distances
	for(auto n : nodes){
		n.second->dist = INT_MAX;
		n.second->predecessor = nullptr;
	}

	// Set up the source node and all of the other nodes on the PQueue
	nodes[s]->dist = 0;

	// put all elements onto a queue
	PQueue q;
	for(auto n = nodes.begin(); n != nodes.end(); n++){
		q.push(n->second);
	}

	while(q.size() != 0){

		// ensure that the queue is in the correct order
		q.reconstruct();
		std::shared_ptr<node> t = q.pop();

		// Add in predecessor
		for(auto i : t->edges){

			// If the current neighbors distance is greater than the current nodes + road distance, than update
			if(nodes[i.second.dest]->dist > t->dist + i.second.weight){
				nodes[i.second.dest]->dist = t->dist + i.second.weight;	// update the weight
				nodes[i.second.dest]->predecessor = t;	// set the predecessor
			}
		}
	}
}

