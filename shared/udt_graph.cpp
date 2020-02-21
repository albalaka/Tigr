#include "udt_graph.hpp"
#include <iostream>
#include <fstream>
using namespace std;

UDTGraph::UDTGraph(Graph &graph)
{
    if (graph.hasZeroID == false)
    {
        for (int i = 0; i < graph.num_edges; i++)
        {
            graph.edges[i].source = graph.edges[i].source - 1;
            graph.edges[i].end = graph.edges[i].end - 1;
        }
    }

    this->graph = &graph;
    inDegree = new uint[graph.num_nodes];
    outDegree = new uint[graph.num_nodes];

    for (int i = 0; i < graph.num_nodes; i++)
    {
        outDegree[i] = 0;
        inDegree[i] = 0;
    }

    for (int i = 0; i < graph.num_edges; i++)
    {
        outDegree[graph.edges[i].source]++;
        inDegree[graph.edges[i].end]++;
    }
}

void UDTGraph::MakeUDTGraph()
{
    ofstream udt_file;
    udt_file.open("udt_graph.txt");
    // udt_file << "Writing this to a file.\n";
    Edge e;
    unsigned int source;
    unsigned int end;

    cout << "in make udtgraph" << endl;

    for (int i = 0; i < graph->num_edges; i++)
    {
        e = graph->edges[i];
        source = e.source;
        end = e.end;
        cout << "source = " << endl;
        cout << "end = " << endl;
        // if (outDegree[i] == 0)
        // 	numZero++;

        // if (outDegree[i] % Part_Size == 0)
        // 	numParts += outDegree[i] / Part_Size;
        // else
        // 	numParts += outDegree[i] / Part_Size + 1;

        // counter = counter + outDegree[i] * 2 + 1;
    }
    udt_file.close();
}
