#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#define INF INT_MAX
#define Edge pair<int,int> // a donde llego y su costo
#define Graph vector<vector<Edge>> // grafo rep. en una lista de adjacencias
#define MAX 10
#define Vertex pair<int, int> // distancia(costo), ID
using namespace std;

void initMatAdj(int matAdj [MAX][MAX]){
    for(int i =0; i<MAX;i++){
        matAdj [i][i]=0;
        for(int j = i+1; j<MAX;j++){
            matAdj[i][j] = matAdj[j][i]= INT_MAX;
        }
    }
}

void leeDatos(int matAdj [MAX][MAX], Graph &G, int e){
    int u,v,w;

  for(int i=0;i<e;i++){
    cin >> u >> v>> w;
    matAdj[u-1][v-1] = matAdj[v-1][u-1]= w;
    Edge edge1(v-1,w);
    G[u-1].push_back(edge1);
    Edge edge2(u-1,w);
    G[v-1].push_back(edge2);

  }

}

void Floyd(int matAdj[MAX][MAX], int v){
    for (int k=0; k<v; k++){
        for(int i=0;i<v;i++){
            for(int j=0; j<v; j++){
                if(matAdj[i][k] != INF  && matAdj[k][j] != INF && matAdj[i][j]> matAdj[i][k]+matAdj[k][j]){
                    matAdj[i][j] = matAdj[i][k]+ matAdj[k][j];
                    //p[i][j]= k
                }
            }
        }
    }

}
