
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#define MAX 10
#define INF INT_MAX
#define Edge pair<int,int> // a donde llego y su costo
#define Graph vector<vector<Edge>>
#define Vertex pair <int,int> //distancia o costo, ID
using namespace std;

//complejidad O(n^2) siendo n el numero de nodos en el grafo
void initMatAdj(int matAdj [MAX][MAX]){
    for (int i= 0; i< MAX; i++){
        matAdj[i][i]=0;
        for(int j=i+1;j< MAX; j++){
            matAdj[i][j]=matAdj[j][i]=INT_MAX;
        }
    }
}
//complejidad O(n) siendo n el num de aristas en el grafo
void leeDatos(int matAdj[MAX][MAX], Graph &G, int edges){
    char cuarto1,cuarto2;
    int c1,c2;
    int d;
    for(int i=0;i<edges; i++){
        cin>>cuarto1>>cuarto2>>d;
        c1= cuarto1-'A';
        c2= cuarto2-'A';
        matAdj[c1][c2]= matAdj[c2][c1]=d;
        Edge edge1(c2,d);
        G[c1].push_back(edge1);
        Edge edge2(c1,d);
        G[c2].push_back(edge2);
    }
}

//Complejidad O(n)
void branchNBound(int matAdj[MAX][MAX], int n, int currPos, int count, int cost,  int& minCost, vector<bool>& visited) {
    if (count == n && matAdj[currPos][0] != INF) {
        minCost = min(minCost, cost + matAdj[currPos][0]);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i] && matAdj[currPos][i] != INF) {
            int nextCost = cost + matAdj[currPos][i];
            if (nextCost >= minCost) continue;
            visited[i] = true;
            branchNBound(matAdj, n, i, count + 1, nextCost, minCost, visited);
            visited[i] = false;
        }
    }
}
//Complejidad O(n)
int travelTime(int matAdj[MAX][MAX], int n, int& minCost) {
    vector<bool> visited(n, false);
    visited[0] = true;
    minCost = INF;
    branchNBound(matAdj, n, 0, 1, 0, minCost, visited);
    return (minCost == INF) ? -1 : minCost;
}

int main(){
    int n; //nodos
    int m;//aristas
    int matAdj[MAX][MAX];  
    initMatAdj(matAdj);
    int minCost = INF;
    cin>>n>>m;
    Graph G(n);
    leeDatos(matAdj,G,m);
    int t=travelTime(matAdj,n,minCost);
    if(t<0){
       cout<< "INF"<<endl;  
    }else{
        cout<<t<<endl;
    }
    return 0;
}