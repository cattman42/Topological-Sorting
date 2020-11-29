#include <string>
#include <list>
#include <map>
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
using namespace std;
#define INFINITY 100000

// This version of bfs uses a pointer representation.
// Each vertex contains within it a list of pointers
// to the other vertices the vertex is connected to.
template <typename T> class vertex
{
public:
	T key;
	enum color { white, gray, black };
	color c;
	int d;
	int f;
	vertex<T>* p;
	int in_degree = 0;
	std::list<vertex<T>*> edges;

	vertex() {}
	vertex(const T& v) { key = v; c = white; d = INFINITY; p = NULL; }
};

template <typename T> class graph
{
public:
	graph(const std::string& fileName);
	~graph();
	void topologicalSort();
	std::list<vertex<T>*> sort;
private:
	// Since the edges are stored in the vertices, we only need
	// a list of vertices in the graph. For convenience, this is
	// stored as a map.
	std::map<T, vertex<T>*> V;
	std::stack<vertex<T>*> q;
};

template <typename T>
graph<T>::graph(const std::string& filename)
{
	std::ifstream in;
	in.open(filename.c_str());

	int vertex_count = 0;
	in >> vertex_count;
	for (int n = 0; n < vertex_count; n++) {
		T key;
		in >> key;
		V[key] = new vertex<T>(key);
	}

	int edge_count = 0;
	in >> edge_count;
	for (int n = 0; n < edge_count; n++) {
		T first, second;
		in >> first >> second;
		V[first]->edges.push_back(V[second]);
	}
}

template <typename T>
graph<T>::~graph() {
	auto itr = V.begin();
	while (itr != V.end()) {
		delete itr->second;
		itr++;
	}
}

template <typename T>
void graph<T>::topologicalSort() {

	for (int u = 0; u < V.size(); u++) {
		auto itr = V.begin();
		while (itr != V.end()) {
			itr->second->in_degree = itr->second->in_degree + 1;
			itr++;
		}
	}

	auto itr = V.begin();
	while (itr != V.end()) {
		if (itr->second->in_degree == 0)
			q.push(itr->second);
	}

	int cnt = 0;

	//Topologoically ordered vertices
	vector<vertex<T>*> ordered;
	while (!q.empty()) {
		vertex<T>* u = q.top();
		q.pop();
		ordered.push_back(u);

		auto itr = V.begin();
		for (itr; itr != V.end(); itr++)
		{
			if (itr->second->in_degree == 0)
				q.push(itr->second);
		}
		cnt++;
	}
	for (int i = 0; i < ordered.size(); i++)
		cout << ordered[i] << " ";
	cout << endl;
}

