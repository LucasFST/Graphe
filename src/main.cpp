#include <fstream>
#include <iostream>
#include <string>
#include "graphe.h"

using namespace std;


int main() 
{
    Graphe unGraphe("./test2.txt");
    unGraphe.affichageGraphe();
    unsigned int tailleTab = unGraphe.getNbColonnes() * unGraphe.getNbLignes();
    unsigned int * tabPrecedent = new unsigned int[tailleTab];
    double * tabDistances = new double[tailleTab];
    unGraphe.dijkstra(tabPrecedent, tabDistances);
    // for(unsigned int i = 0; i < tailleTab ; i++)
    // {
    //     cout<<"indice "<<i<< " : "<<"distance = "<<tabDistances[i]<<"  et precédent = "<<tabPrecedent[i]<<endl;
    // }
    unGraphe.voronoi(tabPrecedent, tabDistances);
    delete []tabDistances;
    delete []tabPrecedent;
    return 0;
}