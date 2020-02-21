#include "../shared/tigr_utilities.hpp"
#include "../shared/graph.hpp"
#include "../shared/udt_graph.hpp"
#include "../shared/globals.hpp"
#include "../shared/argument_parsing.hpp"

int main(int argc, char **argv)
{
	ArgumentParser arguments(argc, argv, true, false);

	Graph graph(arguments.input, false, arguments.printIntermediateResults);
	graph.ReadGraph();

	UDTGraph udtGraph(graph);
	udtGraph.MakeUDTGraph();
	return 0;
}