#include <iostream>
#include <vector>
#include <cassert>
using std::vector;

const int NOT_EULER = -1;

struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to) = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
	ListGraph(int count);

	virtual void AddEdge(int from, int to) override;
	virtual std::vector<int> GetNextVertices(int vertex) const override;

private:
	vector<vector<int>> adjList;
};

ListGraph::ListGraph(int count)
{
	adjList.resize(count);
}

void ListGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < int(adjList.size()));
	assert(to >= 0 && to < int(adjList.size()));
	adjList[from].push_back(to);
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	return adjList[vertex];
}
               
int DFS(const IGraph &graph, int vertex, vector<bool> &visited){            
    visited[vertex] = true;
    int countVisited = 1;
    vector<int> adjList = graph.GetNextVertices(vertex);
    if (adjList.size() % 2 != 0) {
        return NOT_EULER;
    }
    for (const auto &next : adjList)
        if (!visited[next])
            countVisited += DFS(graph, next, visited);
    return countVisited;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    int vertices = 0;
	int edges = 0;
    assert(inputStream >> vertices >> edges);
    assert(vertices > 0 && edges > 0);

	IGraph* graph = new ListGraph(vertices);
    for (int i = 0; i < edges; ++i) {
        int from = 0;
        int to = 0;
        assert(inputStream >> from >> to);
        graph->AddEdge(from, to);
		graph->AddEdge(to, from);
    }

    vector<bool> visited(vertices, false);
	std::cout << (DFS(*graph, 0, visited) == vertices);

	delete graph;
}

int main()
{
	run(std::cin, std::cout);
    return 0;
}