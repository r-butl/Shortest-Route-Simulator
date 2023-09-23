// Lucas Butler
// This code simulates a car on a road trip, where each node is a location that either may or
// may not have a gas station. The simulator finds the shortest path for the car to travel 
// without running out of gas

// driver.cpp

#include <iostream>
#include "Graph.h"
#include "PQueue.h"
#include "algorithm"
#include <vector>
#include <queue>

// Finds the shortest path in the graph
std::vector<int> shortestPath(Graph&, int&);

// Creates a condensed vector of only start/end and gas stations
Graph refinePath(Graph&, int);

// verify that a path passed is traversable by the car, both the graph and path need to be condensed
// 	graph
// 	path
// 	initial charge
// 	max charge
bool verifyPath(Graph&, std::vector<int>, int, int);

// Global variables for constructing and performing tests
int n, m, c, init, start, end;

	// n is number of nodes
	// m is number of edges
	// c is max charge
	// i is initial charge
	
int main(){
	
	std::cin >> n >> m >> c >> init >> start >> end;
	Graph graph(start, end);	// create the graph, setting the start and end points

	// insert all of the nodes into the graph
	for(int i = 0; i < n; i++){

		int name, gas;
		std::cin >> name >> gas;
		graph.addNode(name, gas);
	}

	// insert all of the edged into the graph
	for(int i = 0; i < m; i++){

		int u, v, dist;
		std::cin >> u >> v >> dist;
		graph.addEdge(u, v, dist);
	}

	graph.adjList();
	// creating the condensed graph
	graph = refinePath(graph, c);
	
	// Used to first verify the path and then store the shortest path	
	int totalDistance;
	std::vector<int> path = shortestPath(graph, totalDistance);

	bool v = verifyPath(graph, path, init, c);
	
	if(v){	printf("The car is able to complete the journey.\n");}
	else{	printf("Route cannot be determine.\n");}

	graph.adjList();

	// If the path has been verified, then print it
	if(v){
		printf("Total Distance: %d \nRoute: ", totalDistance);
		for(auto i : path){
			printf("%d ", i);
		}
		printf("\n");
	}

	return 0;

}

// This code will return a vector of the shortest path in terms of gas stations and start/end nodes
std::vector<int> shortestPath(Graph& graph, int& dist){
	
	// ensure that there are elements in the node vector	
	std::vector<int> path;
	if(graph.nodes.size() == 0) return path;

	graph.Dijkstras(start);	// Update the graph for shortest path
	
	dist = 0;		// Reset the total distance
	std::shared_ptr<node> current = graph.nodes[end];	// Start at the end node and go back to start
	int previous;		// Store the previous id so we can get the paths weight

	//while(current != nullptr){
	do{
		if(current->charge || current->id == graph.end || current->id == graph.start) path.insert(path.begin(), current->id); 	// insert the element at the beginning
										// only gas stations
		previous = current->id;				// prepare for weight extraction
		current = current->predecessor;			// Update the current node
		if(current) dist += current->edges[previous].weight;	// add the paths weight to the total distance

	}while(current != nullptr);

	return path;
}

// This code creates a new graph with a refined path of gas stations, start and stop nodes
// 	Pass a graph and a max charge that the paths can have
Graph refinePath(Graph& graph, int c){

	int start = graph.start;
	int end = graph.end;

	// creating the condensed graph
	Graph newGraph(start, end);
	
	// Add important nodes to new graph
	for(auto n : graph.nodes){
		// Add nodes that meet the criteria
		if(n.first == end || n.first == start || n.second->charge == true){
			newGraph.addNode(n.first, n.second->charge);
		}
	}

	// Add important edges to the graph
	for(auto n : graph.nodes){
		// only consider the necessary nodes
		if(n.first == end || n.first == start || n.second->charge == true){			
			// run dijkstras on the current node	
			graph.Dijkstras(n.first);

			for(auto f : graph.nodes){			

				// Conditions for a path to be added
				// 	1. The nodes connecting are the start, end, or a gas station
				// 	2. The nodes connected are not equal
				// 	3. The distance is not more that the max charge
				// 	4. if it is the end or start, the distance cannot be greater than the initial charge
				// 		- this prevents covers the case that we need to go out of our way to get gas	
				if((	((f.first == end && n.first == start) || (f.first == start && n.first == end) && 
								f.second->dist <= init)
					|| f.first == end
					|| f.first == start && f.second->dist <= init
					|| f.second->charge == true	) 
					&& f.first != n.first 
					&& f.second->dist <= c){

					newGraph.addEdge(n.first, f.first, f.second->dist);				
				}
			}
		}
	}
	
	return newGraph;
};


// This code verifies if a path of gas stations traversable
bool verifyPath(Graph& g, std::vector<int> path, int init, int c){

	int currGas = init;

	// ensure that all nodes in the path are nodes in the Graph
	for(auto a : path){
		if( g.nodes.find(a) == g.nodes.end()){
			return false;
		}
	}

	// enter in on the first node and traverse to the next one out of the neighbors of the current node
	// If at anypoint the next node is not in the neighbors or the gas station is out of reach, return false
	std::shared_ptr<node> current;
	std::shared_ptr<node> next;		

	// Tranfer the contents of the vector to the queue
	std::queue<int> p;
	for( auto n : path) p.push(n);
	
	// Start the loop
	current = g.nodes[p.front()];
	p.pop();

	while(p.size()){
				
		//If the current node is gas station, update the gas 
		if(current->charge == true) currGas = c;

		// Set the next target	
		next = g.nodes[p.front()];	// get the next node	
		p.pop();

		// Determine if the next value in the path is a neighbor of the current vector and within range
		if(current->edges.find(next->id) == current->edges.end()){
			// Not a neighbor
			return false;
		}
		
		// Traverse and update the gas
		currGas = currGas - current->edges[next->id].weight;
		if(currGas < 0) return false;
		current = next;
		
		// check if we have reached the end of the path		
		if(current->id == path.back()){
			return true;	
		}
	};

	return true;

};
