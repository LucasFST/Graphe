#include <fstream>
#include <iostream>
#include <string>
#include "graphe.h"

using namespace std;


int main() 
{
    Graphe unGraphe("./test.txt");
    unGraphe.affichageGraphe();
    unsigned int tailleTab = unGraphe.getNbColonnes() * unGraphe.getNbLignes();
    //unsigned int * tabPrecedent = new unsigned int[tailleTab];
    // double * tabDistances = new double[tailleTab];
    // unGraphe.dijkstra(3,tabPrecedent, tabDistances);
    // for(unsigned int i = 0; i < tailleTab ; i++)
    // {
    //     cout<<"indice "<<i<< " : "<<"distance = "<<tabDistances[i]<<"  et precédent = "<<tabPrecedent[i]<<endl;
    // }
    // delete []tabDistances;
    // delete []tabPrecedent;
    for(unsigned int i = 0; i < tailleTab ; i++)
    {
        cout<<"indice "<<i<<" : altitude = "<<unGraphe.getAltitude(i)<<" et librairie : "<<unGraphe.getLibrairieOuNon(i)<<endl;
    }


    return 0;
}