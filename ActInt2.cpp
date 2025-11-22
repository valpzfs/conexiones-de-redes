// E2. Actividad Integradora 2
// 21 de noviembre del 2025
/*
    EQUIPO:
    Amparo Alcaraz Tonella A01253885
    Valeria López Flores A00838648
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#define Edge pair<int,int> // a donde llego y su costo
#define Graph vector<vector<Edge>>
#define MAX 400
using namespace std;

struct Colonia{
    string nombre;
    int x;
    int y; 
    bool central;
    Colonia(){
        nombre = "";
        x=0;
        y=0;
        central = false;
    }
    Colonia(string nombre, int x, int y, bool central){
		this->nombre = nombre;
		this->x = x;
        this->y = y;
        this->central= central;
	}
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

vector<pair<int, pair<int, int>>> prepData4Kruskal(Graph G, pair<int, bool> matAdj[MAX][MAX]){
    vector<pair<int, pair<int, int>>> edges;
    for(int i=0; i<G.size(); i++){
        for(int j =0;j<G[i].size(); j++){
            if(matAdj[i][G[i][j].first].second){ //si ya tiene el cableado nuevo costo 0
                cout<<matAdj[i][G[i][j].first].second<<endl;
                
                edges.push_back({0, {i, G[i][j].first}});
            }else{
                edges.push_back({G[i][j].second, {i, G[i][j].first}}); //en edges first = costo, second = conexión
            }
        }
    }
    //cout<<"--------"<<endl;
    // Print para checar conexiones
    // va indexCD1 -- costo --> indexCD2
    // for (auto it:edges){
	// 	cout<< " " << it.second.first << " --"<<it.first <<"--> " << it.second.second << " "<<endl;
	// }
    return edges;
}

void kruskalMST(int V, Graph G, pair<int, bool> matAdj[MAX][MAX]){
    vector<pair<int, pair<int, int>>> edges=prepData4Kruskal(G, matAdj);
    vector<pair<int, int>> selectedEdges;
	sort(edges.begin(), edges.end());
	DisjointSets ds(V);
	for(auto it:edges){
		int p1 = ds.find(it.second.first);
		int p2 = ds.find(it.second.second);
		if(p1 != p2){
			//costMSTKruskal += it.first;
			selectedEdges.push_back(it.second);
			ds.merge(it.second.first, it.second.second);
		}
	}
    //Print de los caminos seleccionados
    for (auto it:selectedEdges){
		cout << "(" << it.first+1 << ", " << it.second+1 << ") ";
	}
}



void initMatAdj(pair<int, bool> matAdj[MAX][MAX]){
    for(int i =0; i<MAX;i++){
        matAdj [i][i]=pair(0,0);
        for(int j = i+1; j<MAX;j++){
            matAdj[i][j] = matAdj[j][i]= pair(INT_MAX, false);
        }
    }
}
void leeDatos(pair<int,bool> matAdj[MAX][MAX], Graph &G, int edges,unordered_map<string, int> index){
    string col1, col2;
    int c1,c2;
    int cost;
    for(int i=0;i<edges; i++){
        cin>>col1>>col2>>cost;
        int c1 = index[col1];
        int c2 = index[col2];
        matAdj[c1][c2]= matAdj[c2][c1]=pair(cost,0);
        Edge edge1(c2,cost);
        G[c1].push_back(edge1);
        Edge edge2(c1,cost);
        G[c2].push_back(edge2);
    }
}

int main(){
    int n,m,k,q; //n = cantidad de colonias, m = número de conexiones entre colonias, k = las conexiones con el nuevo cableado, q = futuras nuevas colonias que se desean conectar.
    cin >> n >> m >> k >> q;
    vector<Colonia> colonias(n);
    unordered_map<string, int> index;
    // Nombre colonia, coordenadas x y, bool central
    for(int i=0; i<n;i++){
        string nom;
        int x, y;
        bool c;
        cin>>nom>>x>>y>>c;
        colonias[i].nombre=nom;
        colonias[i].x=x;
        colonias[i].y=y;
        colonias[i].central=c;
        index[nom]=i;
    }

    //conexiones entre colonias y su costo
    Graph G(n);
    pair<int, bool> matAdj[MAX][MAX];
    initMatAdj(matAdj);
    leeDatos(matAdj, G, m, index);
    
    
    //conexiones con cableado nuevo 
    for(int i=0;i<k;i++){
        string col1,col2;
        cin>>col1>>col2;
        matAdj[index[col1]][index[col2]].second = true;
    }

    //nuevas colonias
    vector<Colonia> newColonias(q);
    for(int i=0; i<q; i++){
        string nombre;
        int x,y;
        cin >> nombre >> x>> y;
        newColonias[i] =(Colonia(nombre,x,y,false)); // no habia necesidad de declarar una variable para el bool de central ya que no es algo que nos sea util jajaja
    }

    //Cableo optimo con kruskal
    kruskalMST(n,G,matAdj);

    return 0;
}