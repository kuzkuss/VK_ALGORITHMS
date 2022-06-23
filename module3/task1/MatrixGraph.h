#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
	MatrixGraph(int count);
	MatrixGraph(const IGraph& graph);

	virtual void AddEdge(int from, int to) override;
	virtual int VerticesCount() const override;
	virtual vector<int> GetNextVertices(int vertex) const override;
	virtual vector<int> GetPrevVertices(int vertex) const override;

private:
	vector<vector<int>> adjMatrix;
};

#endif // MATRIXGRAPH_H

