#include "graph.h"
#include <iostream>

int main() {
	graph<std::string> G("graph1.txt");
	G.topologicalSort();
	return 0;
}
