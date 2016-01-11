#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

int m,k;
vector <bool> bloom;



unsigned int hash0(int key) {
  key = ~key + (key << 15);
  key = key ^ ((unsigned int) key >> 12);
  key = key + (key << 2);
  key = key ^ ((unsigned int) key >> 4);
  key = key * 2057;
  key = key ^ ((unsigned int) key >> 16);
  int k = key;
  unsigned int r = k < 0? -k : k;
  return r;

}

//Multiplicación de Knuth
unsigned int hash1(int i) {
  int v = 2654435761;
  int p = pow(2,32);
  int r = v / p;
  unsigned int rr = i*r;
  return rr;
}


vector<unsigned int> K_Hash(int i) {
  vector <unsigned int> hashes = vector <unsigned int>(k);

  hashes[0] = hash0(i);

  hashes[1] = hash1(i);

  for (unsigned int i = 2; i < k; i++) {
    hashes[i] = hashes[0] + i * hashes[1]; 
  }
  return hashes;
  
}

void Anadir_Dato(int i) {
  cout << "Debug 1" << endl;
  vector <unsigned int> v = K_Hash(i);
  
  for (int i = 0; i < k; ++i) {
     bloom[v[i]%m] = true;
  }
}

bool Consulta_Dato(int i) {
  vector <unsigned int> v = K_Hash(i);
  for (int i = 0; i < k; ++i) {
    if (not bloom[v[i]%m]) return false;
  }
  return true;
}

int main() {
  m = 1000;
  k = 5;
  int n;
  bloom = vector <bool> (m,false);
  vector<int> datos = vector<int> ();
  ifstream diccionario("./diccionario.txt");
  if (diccionario.is_open()) {
    while (diccionario >> n) datos.push_back(n);
    diccionario.close();
    
    for(int i = 0; i < n; ++i) {
      Anadir_Dato(datos[i]);
    }
  
    ifstream palabras("palabras.txt");
    if (palabras.is_open()) {
      //int size = datos.size();
      while (palabras >> n) {
	  cout << "Num " << n << endl;
	  if (Consulta_Dato(n)) {
	    cout << "encontrado " << endl << endl;
	  }
	  else {
	    cout << "no_encontrado " << endl << endl;
	  }
      }
      palabras.close();
    }
    else cout << "Archivo 'palabras' no disponible" << endl;
  }
  else cout << "Archivo 'diccionario' no disponible" << endl;
}
  