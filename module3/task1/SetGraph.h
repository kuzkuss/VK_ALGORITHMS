#ifndef SETGRAPH_H
#define SETGRAPH_H

#include <unordered_set>

#include "IGraph.h"

using std::unordered_set;

class SetGraph : public IGraph {
public:
	SetGraph(int count);
	SetGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual vector<int> GetNextVertices(int vertex) const override;
	virtual vector<int> GetPrevVertices(int vertex) const override;

private:
	vector<unordered_set<int>> adjList;
};

#endif // SETGRAPH_H

