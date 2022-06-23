#include <cassert>

#include "SetGraph.h"

SetGraph::SetGraph(int count)
{
	adjList.resize(count);
}

SetGraph::SetGraph(const IGraph& graph)
{
	adjList.resize(graph.VerticesCount());
	for(int i = 0; i < graph.VerticesCount(); ++i) {
        auto nextVertices = graph.GetNextVertices(i);
		adjList[i] = unordered_set<int>(nextVertices.begin(), nextVertices.end());
	}
}

void SetGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < int(adjList.size()));
	assert(to >= 0 && to < int(adjList.size()));
	adjList[from].insert(to);
}

int SetGraph::VerticesCount() const
{
	return adjList.size();
}

vector<int> SetGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	return vector<int>(adjList[vertex].begin(), adjList[vertex].end());
}

vector<int> SetGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	vector<int> prevVerticies;
	for(unsigned int from = 0; from < adjList.size(); ++from)
        if (adjList[from].find(vertex) != adjList[from].end())
            prevVerticies.push_back(from);
	return prevVerticies;
}

