#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <math.h>
#include <list>

using namespace std;

int comp_true = 0;
int comp_false = 0;
int perfect = 0;
vector<list<int> > hash_table;

int findNextPower(int n)
{
    int p = ceil(log2(n));
    int l = pow(2,p+1);
    cout << "m is " << l+2 << endl;
    return l+2;

}

unsigned int hash(int key, int size) {
    key = ~key + (key << 15); // key = (key << 15) - key - 1;
    key = key ^ ((unsigned int) key >> 12);
    key = key + (key << 2);
    key = key ^ ((unsigned int) key >> 4);
    key = key * 2057; // key = (key + (key << 3)) + (key << 11);
    key = key ^ ((unsigned int) key >> 16);
    int k = key%size;
    //cout << "Original key: "<< k << endl;
    unsigned int r = k < 0? -k : k;
    //cout << "Resultant key: "<< r << endl;
    return r;
}

void insertData(vector<int>& v)
{
    int m = findNextPower(v.size());
    hash_table = vector<list<int> > (m);

    int i;
    for ( i = 0; i < v.size(); i++)
	{
		unsigned int id = hash(v[i], m);
        hash_table[id].push_back(v[i]);
		cout << v[i] << " -> " << id << endl;
	}
	
}

pair<bool,int> search(int i)
{
	int h = hash(i, hash_table.size());
	
    if (h > hash_table.size() or h < 0)
    {
        //++comp_false;
        return make_pair(false,-1);
        
    } 
	else
    {
        for (list<int>::iterator b = hash_table[h].begin(); b != hash_table[h].end(); ++b)
        {
            if (*b == i)
            {
                if (b == hash_table[h].begin()) ++perfect;
                ++comp_true;
                return make_pair(true, i);
            }
            else
            {
                ++comp_false;
            }
        }

      return make_pair(false,-1);  
    } 
}

int main (int argc, char ** argv)
{
	int n;
	vector<int> datos = vector<int> ();
	ifstream diccionario("./diccionario.txt");
	if (diccionario.is_open()) {
		while (diccionario >> n) datos.push_back(n);
        diccionario.close();
        
        insertData(datos);

        ifstream palabras("palabras.txt");
        if (palabras.is_open()) {
            //int size = datos.size();
            while (palabras >> n) {
                cout << "Num " << n << endl;
                pair<bool,int> busqueda = search(n);
                if (busqueda.first) {
                    cout << "encontrado " << endl << endl;
                }
                else {
                    cout << "no_encontrado " << endl << endl;
                }
            
            }
            palabras.close();

            cout << endl << "Comparaciones fallidas (por colisión): " << comp_false << endl;
            cout << endl << "Encontrado a la primera: " << perfect << endl;
        }
        else cout << "Archivo 'palabras' no disponible" << endl;
	
	}
	else cout << "Archivo 'diccionario' no disponible" << endl;

}
