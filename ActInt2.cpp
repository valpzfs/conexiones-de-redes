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
#include <string>
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
    //Complejidad O(log n)
	int find(int u){ 
		if (u != parent[u]){
			parent[u] = find(parent[u]);
		}
		return parent[u];
	}
    //Complejidad O(log n)
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


//Complejidad O(log n)
vector<pair<int, pair<int, int>>> prepData4Kruskal(int n, pair<int, bool> matAdj[MAX][MAX]){
    vector<pair<int, pair<int, int>>> edges;
    for(int i=0; i<n; i++){
        for(int j=i+1;j<n; j++){
            if(matAdj[i][j].second && !(matAdj[i][j].first==MAX_INT)){ //si ya tiene el cableado nuevo costo 0
                edges.push_back({0, {i, j}});
            }else{
                edges.push_back({matAdj[i][j].first, {i, j}}); //en edges first = costo, second = conexión
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

//Complejidad O(n)
void kruskalMST(int n, pair<int, bool> matAdj[MAX][MAX], unordered_map<int, string> index, string& outputText){
    outputText += "-------------------\n1 - Cableado óptimo de nueva conexión.\n";
    vector<pair<int, pair<int, int>>> edges=prepData4Kruskal(n, matAdj);
    vector<pair<int, int>> selectedEdges;
    int costMSTKruskal;
	sort(edges.begin(), edges.end());
	DisjointSets ds(n);
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
            outputText += index[it.first]+ " - " + index[it.second] + " " + to_string(matAdj[it.first][it.second].first) + "\n";
        }
    }
    outputText += "Costo total: " + to_string(costMSTKruskal) + "\n";
}


// ---- DISTANCIA EUCLIDIANA ---
//Complejidad O(1)
double dist(Colonia &p1, Colonia &p2){
    return sqrt(((p1.x-p2.x)*(p1.x-p2.x))+((p1.y-p2.y)*(p1.y-p2.y)));
}

//Complejidad O(n * m)
double bruteForce(vector<Colonia> conectadas, vector<Colonia> desconectadas,  int ini, int fin, vector<string> &cercanas, string& outputText){
    outputText += "-------------------\n4 - Conexión de nuevas colonias.\n";
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
        outputText += cercanas[0] + " debe conectarse con " + cercanas[1]+ "\n";
        
    }
    outputText += "-------------------";
    return min_aux;
}

//Complejidad O(n^2)
void initMatAdj(pair<int, bool> matAdj[MAX][MAX]){
    for(int i =0; i<MAX;i++){
        matAdj [i][i]=pair(0,0);
        for(int j = i+1; j<MAX;j++){
            matAdj[i][j] = matAdj[j][i]= pair(INT_MAX, false);
        }
    }
}

//Complejidad O(n)
void leeDatos(pair<int,bool> matAdj[MAX][MAX], int edges,unordered_map<string, int> index){
    string col1, col2;
    int c1,c2;
    int cost;
    for(int i=0;i<edges; i++){
        cin>>col1>>col2>>cost;
        int c1 = index[col1];
        int c2 = index[col2];
        matAdj[c1][c2]= matAdj[c2][c1]=pair(cost,0);
    }
}

// ---- FLOYD WARSHALL -----
//Complejidad O(n) 
void printPath(int start, int end, int camino[MAX][MAX], unordered_map<int,string> index, string& outputText) {
    vector<int> pasos;
    while (camino[start][end] != -1) {
        int intermedio = camino[start][end];
        pasos.push_back(intermedio);
        end = intermedio;
    }

    for (int i=pasos.size()-1;i>=0;i--) {
        outputText += index[pasos[i]] + " - ";
    }
}

//Complejidad O(n^2)
// matriz de los caminos para que Floyd tenga como un record de las rutas.
void caminosMat (int v, int camino[MAX][MAX]){
    for(int i= 0; i< v; i++) {
        for(int j= 0; j<v; j++) {
            camino[i][j] = -1; 
        }
    }
}

//Complejidad O(n^3)
// Floyd modificado para guardar los caminos
void FloydWarshall(pair<int,bool> matAdj[MAX][MAX], int v, int camino[MAX][MAX], string& outputText){
    // se le llama a la matriz de caminos que va a ir guardando los nodos intermedios que representan el camino mas corto
    caminosMat(v, camino);

    for (int k=0; k<v; k++) {
        for(int i=0; i<v; i++) {
            for(int j=0; j<v; j++) {
                if(matAdj[i][k].first != MAX_INT && matAdj[k][j].first != MAX_INT && matAdj[i][j].first > matAdj[i][k].first + matAdj[k][j].first){
                    matAdj[i][j].first = matAdj[i][k].first + matAdj[k][j].first;
                    camino[i][j] = k;
                }
            }
        }
    }
}

//Complejidaad O(n^2)
void RutasCentrales(pair<int,bool> matAdj[MAX][MAX], vector<Colonia> &colonias, unordered_map<int, string> index2, int camino[MAX][MAX], string& outputText) {
    outputText += "-------------------\n3 - Caminos más cortos entre centrales.\n"; 
    vector<int> centrales;
    for(int i=0; i<colonias.size(); i++) {
        if(colonias[i].central == true) {
            centrales.push_back(i);
        }
    }

    if(centrales.size()<2){
        outputText += "No hay suficientes colonias centrales para hacer caminos\n";
        return;
    }

    for(int i=0; i<centrales.size(); i++) {
        for(int j = i + 1; j < centrales.size(); j++) {
            outputText += index2[centrales[i]]+" - ";
            printPath(centrales[i], centrales[j], camino, index2, outputText);
            outputText += index2[centrales[j]]; //imprime ultima
            outputText += " (" + to_string(matAdj[centrales[i]][centrales[j]].first) + ")" + "\n";
        }
    }
}


// ---- TRAVELLING SALESMAN PROBLEM  -----
//Complejidad O(n)
//print de la mejor ruta del TSP con los detalles del camino 
void printTSP(vector<int>& mejorRuta, vector<int>& nocentrales, pair<int,bool> matAdj[MAX][MAX], unordered_map<int,string> index2, int camino[MAX][MAX], int minCost, string& outputText) {
    outputText += index2[nocentrales[0]];
    //recorrer la mejor ruta
    for (int i=1; i<mejorRuta.size(); i++) {
        outputText += " - ";
        //print de los nodos intermedios del segmento
        printPath(nocentrales[mejorRuta[i-1]], nocentrales[mejorRuta[i]], camino, index2, outputText);
        outputText += index2[nocentrales[mejorRuta[i]]];
    }
    //regreso a la colonia inicial
    outputText += " - ";
    printPath(nocentrales[mejorRuta.back()], nocentrales[0], camino, index2, outputText);
    outputText += index2[nocentrales[0]];
   
    outputText += "\nLa Ruta Óptima tiene un costo total de: " + to_string(minCost) + "\n";
}

//Complejidad O(n!)
//RUTAACTUAL Y RUTAOPTIMA SE DECLARAN EN TRAVELTIME
void branchNBound(pair<int, bool> matAdj[MAX][MAX], const vector<int>& nocentrales, int currPos, int count, int cost, int& minCost, vector<bool>& visited, vector<int>& rutaactual, vector<int>& rutaoptima) {
   int totalCosto;
    if (count == nocentrales.size()){
        if (matAdj[nocentrales[currPos]][nocentrales[0]].first != MAX_INT)
            // la cambie para calcular el costo total que incluya el regreso a la colonia inicial
            totalCosto =  cost + matAdj[nocentrales[currPos]][nocentrales[0]].first;
           // ahora si se encuentra una ruta que sea mejor, se actualiza el minimo y guarda la ruta
            if (totalCosto < minCost){
                minCost = totalCosto;
                rutaoptima = rutaactual;
            }
        return;
    }

    for (int i=0; i<nocentrales.size(); i++) {
        if (!visited[i]) {
            int temp = matAdj[nocentrales[currPos]][nocentrales[i]].first;
            if (temp != MAX_INT && cost + temp < minCost) {
                visited[i] = true;
                //se marca a uan colonia como visitada y se agega a la ruta act.
                rutaactual.push_back(i);
                branchNBound(matAdj, nocentrales, i, count + 1, cost + temp, minCost, visited, rutaactual, rutaoptima);
                // backtrack para probar otras rutas
                rutaactual.pop_back();
                visited[i] = false;
            }
        }
    }
}

//Complejidad O(n)
int travelTime(pair<int,bool> matAdj[MAX][MAX], vector<Colonia> colonias, int n, unordered_map<int,string> index2, int camino[MAX][MAX], string& outputText) {
    outputText += "-------------------\n2 - La ruta óptima.\n";
    vector<int> nocentrales;
    // hice estos nuevos vectores para ir guardando las rutas
    vector<int> rutaactual;
    vector<int> rutaoptima;
    for (int i = 0; i < n; i++) {
        if (!colonias[i].central) {
            nocentrales.push_back(i);
        }
    }
    

    if (nocentrales.size()<2) {
        outputText += "No hay suficientes colonias no centrales para hacer una ruta\n";
        return 0;
    }
    vector<bool> visited(nocentrales.size(), false);
    visited[0] = true;
    rutaactual.push_back(0); //por aca agrega el origen a la rutaact

    int minCost = MAX_INT;

    branchNBound(matAdj, nocentrales,0,1,0,minCost,visited, rutaactual, rutaoptima);
    if (minCost == MAX_INT) {
        outputText += "No hay ruta óptima posible\n";
        return -1; // No hay ruta posible
    }
    //print de la ruta optima
    printTSP(rutaoptima, nocentrales, matAdj, index2, camino, minCost, outputText);
    return minCost;
}

int main(){
    int n,m,k,q; //n = cantidad de colonias, m = número de conexiones entre colonias, k = las conexiones con el nuevo cableado, q = futuras nuevas colonias que se desean conectar.
    cin >> n >> m >> k >> q;
    vector<Colonia> colonias(n);
    unordered_map<string,int> index1;
    unordered_map<int,string> index2;
    int camino[MAX][MAX];
    string outputText = "";
    //Nombre colonia, coordenadas x y, bool central
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
    pair<int, bool> matAdj[MAX][MAX];
    initMatAdj(matAdj);
    leeDatos(matAdj, m, index1);
    
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
    kruskalMST(n,matAdj, index2,outputText);

    //TSP con branch and bound
    FloydWarshall(matAdj, n, camino, outputText);
    travelTime(matAdj,colonias,n,index2,camino,outputText);
    
    //Ruta optima para ir entre centrales
    RutasCentrales(matAdj, colonias, index2, camino, outputText);

    // distancia entre nuevas conexiones
    vector<string> cercanas(2);
    bruteForce(colonias, newColonias,0, colonias.size(),cercanas, outputText);

    ofstream outputFile("checking2.txt");
    if (outputFile.is_open()) {
        outputFile << outputText;
        cout<<outputText<<endl;

        outputFile.close();
        cout << "Se escribio en el achivo de output";
    } else {
        cout<< "No se pudo escribir en el achivo de output";
    }
    return 0;
}