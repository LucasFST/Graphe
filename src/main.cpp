#include <fstream>
#include <iostream>
#include <string>
#include "graphe.h"

using namespace std;

// struct bidon {
//     bidon(int a) : i(a) {}
//     int i;
// };

// void machin (const bidon& b) {
//     cout<<b.i<<endl;
// }

// void fct(const string& lecture, const string& ecriture) {
    
//     ifstream fichier(lecture);
//     //input file stream pour lire
    
//     ofstream resultat(ecriture);
//     //output file stream pour ecrire

//     cout<<"truc"<<endl;

//     int L, C;
//     fichier >> L >> C;
//     resultat<<"le graphe a "<< L << " lignes et "<< C <<" colonnes"<<endl;

// }

int main() {

    //machin (100);

    // fct("test.txt","resultat.txt");
    // int i,j;
    // string s;

    // cin>>i>>j;
    // cout<<i<<", "<<j<<endl;

    // cin>>s;
    // cout<<s;

    // (x,y,h1) (a,b,h2)
    // distance : sqrt (a-x)² + (b-y)² + (h1-h2)²

    Graphe unGraphe("./test.txt");
    unGraphe.affichageGraphe();
    unsigned int tailleTab = unGraphe.getNbColonnes() * unGraphe.getNbLignes();
    unsigned int * tabPrecedent = new unsigned int[tailleTab];
    double * tabDistances = new double[tailleTab];
    unGraphe.dijkstra(3,tabPrecedent, tabDistances);
    for(unsigned int i = 0; i < tailleTab ; i++)
    {
        cout<<"indice "<<i<< " : "<<"distance = "<<tabDistances[i]<<"  et precédent = "<<tabPrecedent[i]<<endl;
    }
    delete []tabDistances;
    delete []tabPrecedent;

    return 0;
}