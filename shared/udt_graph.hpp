#ifndef UDT_GRAPH_HPP
#define UDT_GRAPH_HPP

#include "graph.hpp"
#include "globals.hpp"

class UDTGraph
{
private:
public:
    Graph *graph;
    uint *edgeList;
    uint *nodePointer;
    uint *inDegree;
    uint *outDegree;
    long long numParts;
    PartPointer *partNodePointer;

    UDTGraph(Graph &graph);

    void MakeGraph();
    void MakeUDTGraph();
};

#endif //	UDT_GRAPH_HPP
