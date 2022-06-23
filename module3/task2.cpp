#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <utility>
using std::vector;
using std::queue;
using std::pair;

const int VISITED = -2;
const int NOT_VISITED = -1;

struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
	ListGraph(int count);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
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

int ListGraph::VerticesCount() const
{
	return adjList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	return adjList[vertex];
}

int BFS(const IGraph& graph, int from, int to)
{
	vector<pair<int, int>> visited(graph.VerticesCount(), pair<int, int>(NOT_VISITED, 0));
	queue<int> bfsQueue;
	bfsQueue.push(from);
    visited[from] = pair<int, int>(0, 1);
	while(bfsQueue.size() > 0) {
		int current = bfsQueue.front();
		if (current == to) {
			break;
		}
		bfsQueue.pop();
		vector<int> adjList = graph.GetNextVertices(current);
		for(unsigned int i = 0; i < adjList.size(); ++i) {
			if(visited[adjList[i]].first == NOT_VISITED) {
				bfsQueue.push(adjList[i]);
				visited[adjList[i]].first = visited[current].first + 1;
				visited[adjList[i]].second = visited[current].second;
			} else if (visited[adjList[i]].first >= 0) {
				if (visited[adjList[i]].first == visited[current].first + 1) {
					visited[adjList[i]].second += visited[current].second;
				} else if (visited[adjList[i]].first > visited[current].first + 1) {
					visited[adjList[i]].first = visited[current].first + 1;
					visited[adjList[i]].second += visited[current].second;
				}
			}
		}
		visited[current].first = VISITED;
	}
	return visited[to].second;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    size_t vertices = 0;
	size_t edges = 0;
    assert(inputStream >> vertices >> edges);
    assert(vertices > 0 && edges > 0);

	IGraph* graph = new ListGraph(vertices);
    for (size_t i = 0; i < edges; ++i) {
        int from = 0;
        int to = 0;
        assert(inputStream >> from >> to);
        graph->AddEdge(from, to);
		graph->AddEdge(to, from);
    }

	int u = 0;
	int w = 0;
	assert(inputStream >> u >> w);

	std::cout << BFS(*graph, u, w);

	delete graph;
}

int main()
{
	run(std::cin, std::cout);
    return 0;
}