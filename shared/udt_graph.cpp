#include "udt_graph.hpp"
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

UDTGraph::UDTGraph(Graph &graph)
{
    linked_list = {NULL, NULL};
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

void UDTGraph::MakeGraph()
{
    nodePointer = new uint[graph->num_nodes];
    edgeList = new uint[graph->num_edges + graph->num_nodes];

    uint *outDegreeCounter;
    uint source;
    uint end;
    uint w8;

    long long counter = 0;
    numParts = 0;
    int numZero = 0;

    for (int i = 0; i < graph->num_nodes; i++)
    {
        nodePointer[i] = counter;
        edgeList[counter] = outDegree[i];

        if (outDegree[i] == 0)
            numZero++;

        if (outDegree[i] % Part_Size == 0)
            numParts += outDegree[i] / Part_Size;
        else
            numParts += outDegree[i] / Part_Size + 1;
        // std::cout << "i = " << i << endl;
        // std::cout << "numParts = " << numParts << endl;

        counter = counter + outDegree[i] + 1;
    }

    outDegreeCounter = new uint[graph->num_nodes];
    for (int i = 0; i < graph->num_edges; i++)
    {
        outDegreeCounter[i] = 0;
    }

    for (int i = 0; i < graph->num_edges; i++)
    {
        source = graph->edges[i].source;
        end = graph->edges[i].end;

        uint location = nodePointer[source] + 1 + outDegreeCounter[source];

        edgeList[location] = end;

        outDegreeCounter[source]++;
    }

    partNodePointer = new PartPointer[numParts];
    int thisNumParts;
    long long countParts = 0;
    for (int i = 0; i < graph->num_nodes; i++)
    {
        if (outDegree[i] % Part_Size == 0)
            thisNumParts = outDegree[i] / Part_Size;
        else
            thisNumParts = outDegree[i] / Part_Size + 1;
        for (int j = 0; j < thisNumParts; j++)
        {
            partNodePointer[countParts].node = i;
            partNodePointer[countParts++].part = j;
        }
    }

    if (graph->printIntermediateResults)
    {

        std::cout << "NodePointer: " << endl;
        for (int i = 0; i < graph->num_nodes; i++)
        {
            std::cout << nodePointer[i] << " ";
        }
        std::cout << endl;

        std::cout << "edgeList: " << endl;
        for (int i = 0; i < graph->num_edges + graph->num_nodes; i++)
        {
            std::cout << edgeList[i] << " ";
        }
        std::cout << endl;

        std::cout << "outDegree: " << endl;
        for (int i = 0; i < graph->num_nodes; i++)
        {
            std::cout << outDegree[i] << " ";
        }
        std::cout << endl;

        std::cout << "inDegree: " << endl;
        for (int i = 0; i < graph->num_nodes; i++)
        {
            std::cout << inDegree[i] << " ";
        }
        std::cout << endl;

        std::cout << "outDegreeCounter: " << endl;
        for (int i = 0; i < graph->num_nodes; i++)
        {
            std::cout << outDegreeCounter[i] << " ";
        }
        std::cout << endl;

        std::cout << "partNodePointer: " << endl;
        for (int i = 0; i < numParts; i++)
        {
            std::cout << partNodePointer[i].node << " ";
        }
        std::cout << endl;

        for (int i = 0; i < numParts; i++)
        {
            std::cout << partNodePointer[i].part << " ";
        }
        std::cout << endl;
    }
}

void UDTGraph::MakeUDTGraph()
{
    ofstream udt_file;
    udt_file.open("udt_graph.txt");
    Edge e;
    unsigned int source;
    unsigned int end;
    unsigned int weight;

    // Transform graph
    for (int i = 0; i < graph->num_nodes; i++)
    {
        int np = nodePointer[i];
        int degree = edgeList[np];

        std::cout << "NodePointer: " << endl;
        for (int i = 0; i < graph->num_nodes; i++)
        {
            std::cout << nodePointer[i] << " ";
        }
        std::cout << endl;

        std::cout << "edgeList: " << endl;
        for (int i = 0; i < graph->num_edges + graph->num_nodes; i++)
        {
            std::cout << edgeList[i] << " ";
        }
        std::cout << endl;

        struct node *newNode = new node();
        // cout << "newNode mem location: " << newNode << endl;

        newNode->node_id = i;
        newNode->part_id = 0;
        newNode->degree = degree;
        if (linked_list.head == NULL)
        {
            linked_list.head = newNode;
            linked_list.current_pointer = newNode;
            // cout << "Setting head" << endl;
            // cout << "node info " << linked_list.head->node_id << "." << linked_list.head->part_id << endl;
        }
        else
        {
            linked_list.current_pointer->nextNode = newNode;
            linked_list.current_pointer = newNode;
        }

        cout << "edgeList: " << endl;
        for (int i = 0; i < graph->num_edges + graph->num_nodes; i++)
        {
            cout << edgeList[i] << " ";
        }
        cout << endl;

        queue<OutwardEdge> q;
        for (int j = np + 1; j < degree + 1; j++)
        {
            uint node_id = edgeList[j];
            // TODO: Weights
            Destination dest = {node_id, 0};
            OutwardEdge outward_edge = {1, dest};
            q.push(outward_edge);
        }

        int part_id = 1;
        while (q.size() > Part_Size)
        {
            struct node *newVirtualNode = new node();
            linked_list.current_pointer->nextNode = newVirtualNode;
            linked_list.current_pointer = newVirtualNode;

            newVirtualNode->node_id = newNode->node_id;
            newVirtualNode->part_id = part_id;
            part_id++;
            if (part_id % 10 == 0)
            {
                part_id++;
            }
            for (int k = 1; k < Part_Size; k++)
            {
                newVirtualNode->outward_edges[k] = q.front();
                q.pop();
            }
            newVirtualNode->degree = Part_Size;
            struct Destination dest = {newVirtualNode->node_id, newVirtualNode->part_id};
            cout << "nvn->node_id: " << newVirtualNode->node_id << "nvn->part_id = " << newVirtualNode->part_id << endl;
            OutwardEdge oe = {0, dest};
            q.push(oe);
        }
        int q_index = 0;
        newNode->degree = q.size();
        while (q.size() > 0)
        {
            newNode->outward_edges[q_index] = q.front();
            q.pop();
            q_index++;
        }
    }

    node *np = linked_list.head;
    while (np != NULL)
    {
        cout << "Source: " << np->node_id << "." << np->part_id << endl;
        cout << "degree = " << np->degree << endl;
        for (int i = 0; i < np->degree; i++)
        {
            OutwardEdge oe = np->outward_edges[i];
            cout << np->outward_edges[i].destination.node_id << "." << np->outward_edges[i].destination.part_id << " : " << np->outward_edges[i].weight << endl;
        }
        cout << endl;
        np = np->nextNode;
    }

    // Writes graph to file called "udt_graph.txt"
    for (int i = 0; i < graph->num_edges; i++)
    {
        e = graph->edges[i];
        source = e.source;
        end = e.end;
        weight = graph->weights[i];
        // cout << "source = " << source << endl;
        // cout << "end = " << end << endl;
        // cout << "weight = " << weight << endl;

        udt_file << source << " " << end << " " << weight << endl;

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
