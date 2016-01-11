#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

unsigned int numero_comp;
unsigned int comp_ciertas;
unsigned int comp_falsas;

bool comp(int a, int b) {
    ++numero_comp;
    return a < b;
}

pair<bool,int> dicotomica(const vector<int>& ordenados, int buscado, int e, int d) {
    int contador = 1;
    if (e > d) return make_pair(false, contador);
    int mig = (e + d)/2;
    pair<bool,int> res;
    ++contador;
    if (buscado < ordenados[mig]) {
        res = dicotomica(ordenados, buscado,e,mig - 1);
        res.second += contador;
        return res;
    }
    ++contador;
    if (buscado > ordenados[mig]) {
        res = dicotomica(ordenados, buscado,mig + 1, d);
        res.second += contador;
        return res;
    }
    return make_pair(true, contador);
}

int main() {
    int n;
    vector<int> ordenados;
    numero_comp = comp_ciertas = comp_falsas = 0;
    ifstream diccionario ("diccionario.txt");
    if (diccionario.is_open()) {
        while (diccionario >> n) ordenados.push_back(n);
        diccionario.close();
        sort(ordenados.begin(),ordenados.end(),comp);
        cout << "Comparaciones_ordenar " << numero_comp << endl;
        ifstream palabras("palabras.txt");
        if (palabras.is_open()) {
            int size = ordenados.size();
            while (palabras >> n) {
                //cout << "Num " << n;
                pair<bool,int> busqueda = dicotomica(ordenados,n,0,size - 1);
                if (busqueda.first) {
                    //cout << " encontrado ";
                    comp_ciertas += busqueda.second;
                }
                else {
                    //cout << " no_encontrado ";
                    comp_falsas += busqueda.second;
                }
                //cout << busqueda.second << " comparaciones." << endl;
            }
            palabras.close();
            cout << "comparaciones ciertas " << comp_ciertas << endl;
            cout << "comparaciones falsas " << comp_falsas << endl;
        }
        else cout << "Unable to open palabras" << endl;
    }
    else cout << "Unable to open file" << endl;
}