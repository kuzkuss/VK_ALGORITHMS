#include <cassert>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void equalVectors(vector<int> lvec, vector<int> rvec)
{
    assert(lvec.size() == rvec.size());
    for (const auto &lelem: lvec) {
        auto it = rvec.begin();
        for (; it < rvec.end(); ++it) {
            if (lelem == *it) {
                break;
            }
        }
        assert(it != rvec.end());
    }
}

void testGraph(const IGraph *graph)
{
    assert(graph->GetNextVertices(0) == vector<int>());
    assert(graph->GetPrevVertices(0) == vector<int>());

    assert(graph->GetNextVertices(1) == vector<int>({3}));
    equalVectors(graph->GetNextVertices(2), vector<int>({1, 3, 4}));
    assert(graph->GetNextVertices(3) == vector<int>({4}));
    assert(graph->GetNextVertices(4) == vector<int>({5}));
    equalVectors(graph->GetNextVertices(5), vector<int>({3, 4}));

    assert(graph->GetPrevVertices(1) == vector<int>({2}));
    assert(graph->GetPrevVertices(2) == vector<int>());
    equalVectors(graph->GetPrevVertices(3), vector<int>({1, 2, 5}));
    equalVectors(graph->GetPrevVertices(4), vector<int>({2, 3, 5}));
    assert(graph->GetPrevVertices(5) == vector<int>({4}));
}

void fillGraph(IGraph *graph)
{
    graph->AddEdge(1, 3);
	graph->AddEdge(2, 1);
	graph->AddEdge(2, 3);
	graph->AddEdge(2, 4);
	graph->AddEdge(3, 4);
	graph->AddEdge(4, 5);
	graph->AddEdge(5, 3);
	graph->AddEdge(5, 4);
}

int main()
{
	IGraph* listGraph = new ListGraph(6);
    fillGraph(listGraph);

    IGraph* matrixGraph = new MatrixGraph(6);
    fillGraph(matrixGraph);

    IGraph* setGraph = new SetGraph(6);
    fillGraph(setGraph);

    IGraph* arcGraph = new ArcGraph(6);
    fillGraph(arcGraph);

    testGraph(listGraph);
    testGraph(matrixGraph);
    testGraph(setGraph);
    testGraph(arcGraph);

    IGraph* listGraphCopy = new ListGraph(*matrixGraph);
    IGraph* matrixGraphCopy = new MatrixGraph(*listGraph);
    IGraph* setGraphCopy = new SetGraph(*arcGraph);
    IGraph* arcGraphCopy = new ArcGraph(*setGraph);

    testGraph(listGraphCopy);
    testGraph(matrixGraphCopy);
    testGraph(setGraphCopy);
    testGraph(arcGraphCopy);

	delete listGraph;
    delete matrixGraph;
    delete setGraph;
    delete arcGraph;

    delete listGraphCopy;
    delete matrixGraphCopy;
    delete setGraphCopy;
    delete arcGraphCopy;

    return 0;
}

