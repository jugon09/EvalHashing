#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int m,k;
vector <bool> bloom;

public vector<int> K_Hash(int i) {
  vector <int> hashes = new vector <int>(k);
  hashes[0] =
  hashes[1] =
  int hash0 = rand() % hashes[0];
  int hash1 = rand() % hashes[1];
  for (int i = 2; i < k; i++) {
    hashes[i] = hash0 + i*hash1; 
  }
  return hashes;  
}

public void Añadir_Dato(int i) {
  vector <int> v = K_Hash(i);
  for (int i = 0; i < k; ++i) {
     bloom[v[i]%m] = true;
  }
}

public void Consulta_Dato(int i) {
  vector <int> v = K_Hash(i);
  for (int i = 0; i < k; ++i) {
    if (not bloom[v[i]%m]) return false;
  }
  return true;
}

int main() {
  m = 1000;
  k = 5;
  bloom = new vector <bool> (m,false);
}