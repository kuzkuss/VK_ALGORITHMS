#include <cassert>

#include "ListGraph.h"

ListGraph::ListGraph(int count)
{
	adjList.resize(count);
}

ListGraph::ListGraph(const IGraph& graph)
{
	adjList.resize(graph.VerticesCount());
	for(int i = 0; i < graph.VerticesCount(); ++i) {
		adjList[i] = graph.GetNextVertices(i);
	}
}

void ListGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < int(adjList.size()));
	assert(to >= 0 && to < int(adjList.size()));
	adjList[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
	return adjList.size();
}

vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	return adjList[vertex];
}

vector<int> ListGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	vector<int> prevVerticies;
	for(unsigned int from = 0; from < adjList.size(); ++from)
		for(unsigned int i = 0; i < adjList[from].size(); ++i)
			if(adjList[from][i] == vertex)
				prevVerticies.push_back(from);
	return prevVerticies;
}

