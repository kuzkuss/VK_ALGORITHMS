#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "IGraph.h"

class ListGraph : public IGraph {
public:
	ListGraph(int count);
	ListGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual vector<int> GetNextVertices(int vertex) const override;
	virtual vector<int> GetPrevVertices(int vertex) const override;

private:
	vector<vector<int>> adjList;
};

#endif // LISTGRAPH_H

