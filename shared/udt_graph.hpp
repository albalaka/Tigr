#ifndef UDT_GRAPH_HPP
#define UDT_GRAPH_HPP

#include "graph.hpp"
#include "globals.hpp"

struct node
{
    long long node_id;
    long long part_id;
    int degree;
    OutwardEdge outward_edges[Part_Size];
    node *nextNode = NULL;
};

struct LinkedList
{
    node *head;
    node *current_pointer;
};

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
    struct LinkedList linked_list;

    UDTGraph(Graph &graph);

    void MakeGraph();
    void MakeUGraph();
    void MakeUDTGraph();
    void PrintUDTGraph();
};

#endif //	UDT_GRAPH_HPP
