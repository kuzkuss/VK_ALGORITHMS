#include <cassert>

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int count)
{
	adjMatrix.resize(count);
    for (int i = 0; i < count; ++i) {
        adjMatrix[i].resize(count, 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph& graph)
{
    int count = graph.VerticesCount();
	adjMatrix.resize(count);
	for(int i = 0; i < count; ++i) {
        adjMatrix[i].resize(count, 0);
        for (const auto &elem: graph.GetNextVertices(i)) {
            adjMatrix[i][elem] = 1;
        }
	}
}

void MatrixGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < int(adjMatrix.size()));
	assert(to >= 0 && to < int(adjMatrix.size()));
	adjMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const
{
	return adjMatrix.size();
}

vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjMatrix.size()));
    vector<int> nextVertices;
    for (unsigned int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[vertex][i] > 0) {
            nextVertices.push_back(i);
        }
    }
	return nextVertices;
}

vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjMatrix.size()));
	vector<int> prevVerticies;
	for (unsigned int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[i][vertex] > 0) {
            prevVerticies.push_back(i);
        }
    }
	return prevVerticies;
}