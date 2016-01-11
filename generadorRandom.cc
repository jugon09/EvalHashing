#include <iostream>
#include <ctime>
#include <cstdlib>
#include <set>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n < 2000)
    {
        cout << "El número es menor a 2000. Elija otro número para la próxima vez." << endl;
        return 0;
    }
    set<int> diccionario;
    ofstream diccionarioFile;
    diccionarioFile.open("diccionario.txt");
    srand(time(NULL));
    int i = 0;
    while (diccionario.size() < n) {
        int elem = rand()%n + 1;
        if (diccionario.find(elem) == diccionario.end()) {
            diccionario.insert(elem);
            diccionarioFile << elem << " ";
            ++i;
            if (i%10 == 0) diccionarioFile << "\n";
        }
    }

    diccionarioFile.close();
    ofstream palabras;
    palabras.open ("palabras.txt");
    int limite = 2*n;
    vector<int> palabrasV(diccionario.begin(),diccionario.end());
    for (int j = 0; j < limite; ++j) {
        int ll = limite / 2000; 
        int mo = j%ll;
        if (mo == 0)
            {
                palabras << palabrasV[j%n];
            }
        else palabras << (rand()%limite + 1);
        palabras << " ";
        if ((j+1)%10 == 0) palabras << "\n";
    }
    palabras.close();
}
