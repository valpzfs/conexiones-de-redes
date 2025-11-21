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
#include <sstream>
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
    Colonia(string nombre, int x, int y, bool central){
		this->nombre = nombre;
		this->x = x;
        this->y = y;
        this->central= central;
	}
};

void initMatAdj(int matAdj [MAX][MAX]){
    for(int i =0; i<MAX;i++){
        matAdj [i][i]=0;
        for(int j = i+1; j<MAX;j++){
            matAdj[i][j] = matAdj[j][i]= INT_MAX;
        }
    }
}
void leeDatos(int matAdj[MAX][MAX], Graph &G, int edges,unordered_map<string, int> index){
    string col1, col2;
    int c1,c2;
    int cost;
    for(int i=0;i<edges; i++){
        cin>>col1>>col2>>cost;
        int c1 = index[col1];
        int c2 = index[col2];
        matAdj[c1][c2]= matAdj[c2][c1]=cost;
        Edge edge1(c2,cost);
        G[c1].push_back(edge1);
        Edge edge2(c1,cost);
        G[c2].push_back(edge2);
    }
}
int main(){
    int n,m ,q, k; //n = cantidad de colonias, m = número de conexiones entre colonias, k = las conexiones con el nuevo cableado, q = futuras nuevas colonias que se desean conectar.
    cin >> n >> m >> q >> k;
    vector<Colonia> colonias(n);
    unordered_map<string, int> index;
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
    Graph G(m);
    int matAdj[MAX][MAX];
    initMatAdj(matAdj);
    leeDatos(matAdj, G, m, index);
    return 0;
}