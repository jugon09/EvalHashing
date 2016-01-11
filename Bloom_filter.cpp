#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

int m,k;
vector <bool> bloom;
int acierto;
int fallo;



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
  m = 200000;
  k = 100;
  int n;
  acierto = 0;
  fallo = 0;
  bloom = vector <bool> (m,false);
  ifstream diccionario("./diccionario.txt");
  if (diccionario.is_open()) {
    while (diccionario >> n) Anadir_Dato(n);
    diccionario.close();
    
  
    ifstream palabras("palabras.txt");
    if (palabras.is_open()) {
      //int size = datos.size();
      while (palabras >> n) {
	  //cout << "Num " << n << endl;
	  if (Consulta_Dato(n)) {
	    //cout << "encontrado " << endl << endl;
	    acierto++;
	  }
	  else {
	    //cout << "no_encontrado " << endl << endl;
	    fallo++;
	  }
      }
      palabras.close();
    }
    else cout << "Archivo 'palabras' no disponible" << endl;
  }
  else cout << "Archivo 'diccionario' no disponible" << endl;
  cout << "Fallos: " << fallo;
  cout << "Aciertos: " << acierto << endl;
}
  