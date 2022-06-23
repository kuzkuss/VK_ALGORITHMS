#include <cassert>

#include "ArcGraph.h"

ArcGraph::ArcGraph(int count) : numVertices(count) { }

ArcGraph::ArcGraph(const IGraph& graph)
{
	numVertices = graph.VerticesCount();
	for(int i = 0; i < numVertices; ++i) {
        for (const auto &elem: graph.GetNextVertices(i)) {
            edges.push_back(pair<int, int>(i, elem));
        }
	}
}

void ArcGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < numVertices);
	assert(to >= 0 && to < numVertices);
	edges.push_back(pair<int, int>(from, to));
}

int ArcGraph::VerticesCount() const
{
	return numVertices;
}

vector<int> ArcGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < numVertices);
    vector<int> nextVertices;
    for (const auto &elem: edges) {
        if (elem.first == vertex) {
            nextVertices.push_back(elem.second);
        }
    }
	return nextVertices;
}

vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < numVertices);
	vector<int> prevVerticies;
	for (const auto &elem: edges) {
        if (elem.second == vertex) {
            prevVerticies.push_back(elem.first);
        }
    }
	return prevVerticies;
}

