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
#include <cmath>
#define Edge pair<int,int> // a donde llego y su costo
#define Graph vector<vector<Edge>>
#define MAX 30
#define MAX_INT INT_MAX
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

// ----------- KRUSKAL -----------------
struct DisjointSets{ //Disjoint Sets (Union-Find)
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

void kruskalMST(Graph G, pair<int, bool> matAdj[MAX][MAX], unordered_map<int, string> index){
    vector<pair<int, pair<int, int>>> edges=prepData4Kruskal(G, matAdj);
    vector<pair<int, int>> selectedEdges;
    int costMSTKruskal;
	sort(edges.begin(), edges.end());
	DisjointSets ds(G.size());
	for(auto it:edges){
		int p1 = ds.find(it.second.first);
		int p2 = ds.find(it.second.second);
		if(p1 != p2){
			costMSTKruskal += it.first;
			selectedEdges.push_back(it.second);
			ds.merge(it.second.first, it.second.second);
		}
	}
    
    //Print de los caminos seleccionados a ponerles cableado nuevo
    for (auto it:selectedEdges){
        if(!matAdj[it.first][it.second].second){
            cout<< index[it.first]<<" - "<< index[it.second]<<" "<<matAdj[it.first][it.second].first<<endl;
        }
    }
    cout<<"Costo total: "<<costMSTKruskal<<endl;
}


double dist(Colonia &p1, Colonia &p2){
    return sqrt(((p1.x-p2.x)*(p1.x-p2.x))+((p1.y-p2.y)*(p1.y-p2.y)));
}

double bruteForce(vector<Colonia> conectadas, vector<Colonia> desconectadas,  int ini, int fin, vector<string> &cercanas ){
    double min_aux;
    for (int i=0;i<desconectadas.size();i++){
        min_aux = MAX_INT;
        for(int j=ini; j<fin;j++){
            if(dist(desconectadas[i], conectadas[j])<min_aux){
                min_aux = min(min_aux, dist(desconectadas[i], conectadas[j]));
                cercanas[0]=desconectadas[i].nombre;
                cercanas[1]=conectadas[j].nombre;
            }
        }
        cout<<cercanas[0]<<" debe conectarse con "<<cercanas[1]<<endl;
    }
    return min_aux;
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

// ---- FLOYD WARSHALL (Punto 3)-----
void printPath(int start, int end, int camino[MAX][MAX], unordered_map<int,string> index) {
    vector<int> pasos;
    int inicioInicial = start;
    int finFinal = end;
    while (camino[inicioInicial][finFinal] != -1) {
        int intermedio = camino[inicioInicial][finFinal];
        pasos.push_back(intermedio);
        finFinal = intermedio;
    }

    for (int i=0;i<pasos.size();i++) {
        int nodo = pasos[i];
        cout << " - " << index[nodo];
    }
}

// Matriz de los caminos necesaria para que Floyd tenga un record de las rutas.
void caminosMat (pair<int,bool> matAdj[MAX][MAX], int v, int camino[MAX][MAX]){
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < v; j++) {
            camino[i][j] = -1; 
        }
    }
}

// Floyd modificado para guardar los caminos
void FloydWarshall(pair<int,bool> matAdj[MAX][MAX], int v, int camino[MAX][MAX]){
    // se le llama a la matriz de caminos que va a ir guardando los nodos intermedios que representan el camino más corto
    caminosMat(matAdj, v, camino);

    for (int k = 0; k < v; k++) {
        for(int i = 0; i < v; i++) {
            for(int j = 0; j < v; j++) {
                if(matAdj[i][k].first != MAX_INT && matAdj[k][j].first != MAX_INT && matAdj[i][j].first > matAdj[i][k].first + matAdj[k][j].first){
                    matAdj[i][j].first = matAdj[i][k].first + matAdj[k][j].first;
                    camino[i][j] = k;
                }
            }
        }
    }
}

void RutasCentrales(pair<int,bool> matAdj[MAX][MAX], vector<Colonia> &colonias, unordered_map<int, string> index2, int camino[MAX][MAX]) {
    vector<int> centrales;
    for(int i = 0; i < colonias.size(); i++) {
        if(colonias[i].central == true) {
            centrales.push_back(i);
        }
    }
    for(int i = 0; i < centrales.size(); i++) {
        for(int j = i + 1; j < centrales.size(); j++) {
            cout << index2[centrales[i]];
            printPath(centrales[i], centrales[j], camino, index2);
            cout << " - " << index2[centrales[j]];
            cout << " (" << matAdj[centrales[i]][centrales[j]].first << ")" << endl;
        }
    }
}

int main(){
    int n,m,k,q; //n = cantidad de colonias, m = número de conexiones entre colonias, k = las conexiones con el nuevo cableado, q = futuras nuevas colonias que se desean conectar.
    cin >> n >> m >> k >> q;
    vector<Colonia> colonias(n);
    unordered_map<string, int> index1;
    unordered_map<int, string> index2;
    int camino[MAX][MAX];
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
        index1[nom]=i;
        index2[i]=nom;
    }

    //conexiones entre colonias y su costo
    Graph G(n);
    pair<int, bool> matAdj[MAX][MAX];
    initMatAdj(matAdj);
    leeDatos(matAdj, G, m, index1);
    
    //conexiones con cableado nuevo 
    for(int i=0;i<k;i++){
        string col1,col2;
        cin>>col1>>col2;
        matAdj[index1[col1]][index1[col2]].second = true;
    }

    //nuevas colonias
    vector<Colonia> newColonias(q);
    for(int i=0; i<q; i++){
        string nombre;
        int x,y;
        cin >> nombre >> x>> y;
        newColonias[i] =(Colonia(nombre,x,y,false)); // no habia necesidad de declarar una variable para el bool de central ya que no es algo que nos sea util jajaja
        index1[nombre]=colonias.size()+i;
        index2[colonias.size()+i]=nombre;
    }

    // FORMATO DE SALIDA

    //Cableo optimo con kruskal
    cout<<"-------------------\n1 - Cableado óptimo de nueva conexión."<<endl;
    kruskalMST(G,matAdj, index2);
    cout<<"-------------------\n2 - La ruta óptima."<<endl;
    //Ruta optima para ir entre centrales
    cout<<"-------------------\n3 - Caminos más cortos entre centrales."<<endl;
    FloydWarshall(matAdj, n, camino);
    RutasCentrales(matAdj, colonias, index2, camino);
    cout<<"-------------------\n4 - Conexión de nuevas colonias."<<endl;
    vector<string> cercanas(2);
    bruteForce(colonias, newColonias,0, colonias.size(),cercanas);
    cout<<"-------------------"<<endl;
    return 0;
}