#include <iostream>
#include <cmath>
#include <vector>
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
  unsigned int v = 2654435761;
  unsigned int p = pow(2,32);
  unsigned int r = v / p;
  r = i*r;
  
  return r;
}


vector<unsigned int> K_Hash(int i) {
  vector <unsigned int> hashes = vector <unsigned int>(k);
  hashes[0] = hash0(i);
  hashes[1] = hash1(i);
  for (int i = 2; i < k; i++) {
    hashes[i] = hash0 + i*hash1; 
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
  m = 1000;
  k = 5;
  bloom = vector <bool> (m,false);
  
  
}