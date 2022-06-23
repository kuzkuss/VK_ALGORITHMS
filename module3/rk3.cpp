#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <utility>
using std::vector;
using std::set;
using std::pair;

struct IGraph {
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to, int weight) = 0;

	virtual int VerticesCount() const = 0;

	virtual vector<pair<int, int>> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
	ListGraph(int count);

	virtual void AddEdge(int from, int to, int weight) override;
	virtual int VerticesCount() const override;
	virtual vector<pair<int, int>> GetNextVertices(int vertex) const override;

private:
	vector<vector<pair<int, int>>> adjList;
};

ListGraph::ListGraph(int count)
{
	adjList.resize(count);
}

void ListGraph::AddEdge(int from, int to, int weight)
{
	assert(from >= 0 && from < int(adjList.size()));
	assert(to >= 0 && to < int(adjList.size()));
	adjList[from].push_back(pair<int, int>(weight, to));
}

int ListGraph::VerticesCount() const
{
	return adjList.size();
}

vector<pair<int, int>> ListGraph::GetNextVertices(int vertex) const
{
	assert(vertex >= 0 && vertex < int(adjList.size()));
	return adjList[vertex];
}

int algDijkstra(const IGraph& graph, int from, int to, int k)
{
    vector<int> pi(graph.VerticesCount(), -1);
	vector<int> distances(graph.VerticesCount(), -1);
    distances[from] = 0;
    set<pair<int, int>> priorityQueue;
    priorityQueue.insert(pair<int, int>(0, from));
    while(!priorityQueue.empty()) {
        auto cur = *priorityQueue.begin();
        if (cur.second == to) {
            break;
        }
        priorityQueue.erase(cur);
        for(auto &elem : graph.GetNextVertices(cur.second)) {
            if (distances[elem.second] == -1) {
                pi[elem.second] = cur.second;
                distances[elem.second] = cur.first + elem.first;
                priorityQueue.insert(pair<int, int>(cur.first + elem.first, elem.second));
            } else if(distances[elem.second] > cur.first + elem.first) {
                pi[elem.second] = cur.second;
                priorityQueue.erase(pair<int, int>(distances[elem.second], elem.second));
                distances[elem.second] = cur.first + elem.first;
                priorityQueue.insert(pair<int, int>(cur.first + elem.first, elem.second));
            }
        }
    }

    int count = 0;
    int cur = to;
    while (cur != from && count < k) {
        cur = pi[cur];
        ++count;
    }

    if (cur != from) {
        return -1;
    }

	return priorityQueue.begin()->first;
}

void run(std::istream &inputStream, std::ostream &outputStream) {
    size_t vertices = 0;
	size_t edges = 0;
    size_t k = 0;
    assert(inputStream >> vertices >> edges >> k);
    assert(vertices > 0 && edges > 0);

    int from = 0;
	int to = 0;
	assert(inputStream >> from >> to);

	IGraph* graph = new ListGraph(vertices);
    for (size_t i = 0; i < edges; ++i) {
        int from = 0;
        int to = 0;
        int weight = 0;
        assert(inputStream >> from >> to >> weight);
        assert(weight >= 0);
        graph->AddEdge(from - 1, to - 1, weight);
    }

	std::cout << algDijkstra(*graph, from - 1, to - 1, k);

	delete graph;
}

int main()
{
	run(std::cin, std::cout);
    return 0;
}