#include <iostream>
#include <vector>
#include "kruskal.h"
#include "floyd.h"
#include "tsp.h"
using namespace std;


struct Colonia {
    string nombre;
    int x, y;
    bool esCentral;
};

struct Conexion {
    string colonia1, colonia2;
    int costo;
};

struct ConexionCableado {
    string colonia1, colonia2;
};

struct NuevaColonia {
    string nombre;
    int x, y;
};

int main() {
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    
    vector<Colonia> colonias(n);
    for (int i = 0; i < n; i++) {
        int central;
        cin >> colonias[i].nombre >> colonias[i].x >> colonias[i].y >> central;
        colonias[i].esCentral = (central == 1);
    }

    vector<Conexion> conexiones(m);
    for (int i = 0; i < m; i++) {
        cin >> conexiones[i].colonia1 >> conexiones[i].colonia2 >> conexiones[i].costo;
    }
    vector<ConexionCableado> cableadoNuevo(k);
    for (int i = 0; i < k; i++) {
        cin >> cableadoNuevo[i].colonia1 >> cableadoNuevo[i].colonia2;
    }
    vector<NuevaColonia> nuevasColonias(q);
    for (int i = 0; i < q; i++) {
        cin >> nuevasColonias[i].nombre >> nuevasColonias[i].x >> nuevasColonias[i].y;
    }
    cout << "=== COLONIAS EXISTENTES ===" << endl;
    for (const auto& c : colonias) {
        cout << c.nombre << " (" << c.x << ", " << c.y << ") "
             << (c.esCentral ? "CENTRAL" : "NO CENTRAL") << endl;
    }
    cout << "\n=== CONEXIONES ===" << endl;
    for (const auto& c : conexiones) {
        cout << c.colonia1 << " <-> " << c.colonia2 << " : $" << c.costo << endl;
    }
    cout << "\n=== NUEVO CABLEADO ===" << endl;
    for (const auto& c : cableadoNuevo) {
        cout << c.colonia1 << " <-> " << c.colonia2 << endl;
    }
    cout << "\n=== NUEVAS COLONIAS ===" << endl;
    for (const auto& c : nuevasColonias) {
        cout << c.nombre << " (" << c.x << ", " << c.y << ")" << endl;
    }
    
    return 0;
}
