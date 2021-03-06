// practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <stack>
using namespace std;


// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
	int V;    // No. of vertices

			  // Pointer to an array containing
			  // adjacency lists
	list<int> *adj;

	

	// A recursive function used by DFS
	void DFSUtil(int v, bool visited[], int depth);
public:
	int max_depth;
	stack<int> stk;
	stack<int> max_stk;

	Graph(int V);   // Constructor

					// function to add an edge to graph
	void addEdge(int v, int w);

	// DFS traversal of the vertices
	// reachable from v
	void DFS(int v);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
	max_depth = 0;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[], int depth)
{
	visited[v] = true;

	if (depth > max_depth)
	{
		max_depth = depth;
		while (!stk.empty())
			stk.pop();
	}
	// Recur for all the vertices adjacent
	// to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if (!visited[*i])
		{
			DFSUtil(*i, visited, depth + 1);
		}
	}

	stk.push(v);	
	visited[v] = false;
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()


void Graph::DFS(int v)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	if (max_stk.size() < max_depth)
	{
		while (!max_stk.empty())
			max_stk.pop();
		
		while (!stk.empty())
		{
			max_stk.push(stk.top());
			stk.pop();
		}
	}

	while(!stk.empty())
		stk.pop();
		
	// Call the recursive helper function
	// to print DFS traversal
	DFSUtil(v, visited, 0);

	delete[] visited;
}


int main()
{
	// Create a graph given in the above diagram
	Graph g(8);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(2, 1);
	g.addEdge(1, 4);
	g.addEdge(4, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 2);
	g.addEdge(3, 7);

	for (int i = 0; i < 8; i++)
	{
		g.DFS(i);
	}
	cout << "max depth: " << g.max_depth << endl;
	cout << "backtracked elements" << endl;
	while (!g.max_stk.empty() )
	{
		cout << g.max_stk.top() << endl;
		g.max_stk.pop();
	}
		
	return 0;
}

