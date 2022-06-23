#ifndef ARCGRAPH_H
#define ARCGRAPH_H

#include <utility>

#include "IGraph.h"

using std::pair;

class ArcGraph : public IGraph {
public:
	ArcGraph(int count);
	ArcGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual vector<int> GetNextVertices(int vertex) const override;
	virtual vector<int> GetPrevVertices(int vertex) const override;

private:
	vector<pair<int, int>> edges;
    int numVertices;
};

#endif // ARCGRAPH_H

