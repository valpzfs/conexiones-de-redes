#include <iostream>
#include <vector>
#include <algorithm>
#define INF INT_MAX
using namespace std;


struct Graph{
	// V = vertex, E = Edges
	int V, E, costMSTKruskal;
	vector<pair<int, pair<int, int>>> edges;	
	vector<pair<int, int>> selectedEdgesK;		

	Graph(int V, int E){
		this->V = V;
		this->E = E;
		costMSTKruskal = 0;
	}
	// u = salida del arco
	// v = llegada del arco
	// w = costo del arco
	void addEdge(int u, int v, int w){
		edges.push_back({w, {u, v}}); // first = costo, second = conexión
	}
	void load();
	void print();
	void kruskalMST();
	void printEdgesK();
};

//Disjoint Sets (Union-Find)
struct DisjointSets{
	int *parent, *rank;
	int n;
	DisjointSets(int n){
		this->n = n;
		parent = new int[n+1];
		rank = new int[n+1];
		for (int i=0; i<=n; i++){
			rank[i] = 0;
			parent[i] = i;
		}
	}
	// Para encontrar el parent de 'u'
	int find(int u){
		if (u != parent[u]){
			parent[u] = find(parent[u]);
		}
		return parent[u];
	}
	void merge(int x, int y){
		x = find(x);
		y = find(y);
		if (rank[x] > rank[y]){
			parent[y] = x;
		}
		else{
			parent[x] = y;
		}
		if (rank[x] == rank[y]){
			rank[y]++;
		}
	}
};

void Graph::load(){
	int a, b, c;
	for (int i=0; i<E; i++){
		cin >> a >> b >> c;
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
}

void Graph::kruskalMST(){
	sort(edges.begin(), edges.end());
	DisjointSets ds(V);
	for(auto it:edges){
		int p1 = ds.find(it.second.first);
		int p2 = ds.find(it.second.second);
		if(p1 != p2){
			costMSTKruskal += it.first;
			selectedEdgesK.push_back(it.second);
			ds.merge(it.second.first, it.second.second);
		}
	}
	
}

void Graph::printEdgesK(){
	cout << "Selected Edges Kruskal: ";
	for (auto it:selectedEdgesK){
		cout << "(" << it.first << ", " << it.second << ") ";
	}
	cout << endl;
}
