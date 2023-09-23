// Graph.h
// Lucas Butler
// Class defintion for a graph

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <map>

// Basic edge class
struct edge{
	
	int dest;
	int weight;

	// default constructor	
	edge(){
	dest = -1;
	weight = -1;
	}

	// better one
	edge(int d, int w): dest(d), weight(w) {}
};


// Basic node class
class node{

	public:
	int id;					
	bool visited;			
	bool discovered;		
	int finished;
	int dist;
	bool charge;
	std::shared_ptr<node> predecessor;

	std::map<int, edge> edges;

	node(int i, bool c): id(i), charge(c) {}
};


// Graph class
class Graph{

	public:
	std::map<int, std::shared_ptr<node>> nodes;	// nodes stored by id	
	Graph(int, int);							// constructor 

	// For car control
	int start;
	int end;

	// Adds a node to the graph
	void addNode(int i, bool c);

	// Take the incoming edges and assign it to the nodes	
	void addEdge(int src, int dest, int weight);

	// Print out the adjacentcy list
	void adjList();

	// DFS
	void DFS();
	int DFSVisit(std::shared_ptr<node> , int);

	// BFS
	void BFS(int);

	// isNeighbor
	bool isNeighbor(int, int);

	// Implementation of Dijkstras Algo
	void Dijkstras(int s);

	// Print all of the nodes in the graph
	void printNodes();

	// Reshape the graph
	void reshape();

	// finds all the nodes in range, returns the IDs	
	std::vector<int> nodesInRange(int, int);
};

#endif
