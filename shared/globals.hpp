#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <stdio.h>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <chrono>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

typedef unsigned int uint;

const unsigned int Part_Size = 2000;

const unsigned int DIST_INFINITY = std::numeric_limits<unsigned int>::max() - 1;

struct Edge
{
    unsigned int source;
    unsigned int end;
};

struct Destination
{
    long long node_id;
    // long long part_id;
};

struct OutwardEdge
{
    unsigned int weight;
    struct Destination destination;
};

struct PartPointer
{
    unsigned int node;
    unsigned int part;
};

#endif //	GLOBALS_HPP
