#include <fstream>
#include <iostream>
#include <string>
#include "graphe.h"

using namespace std;


int main() 
{
    Graphe unGraphe("./test.txt");
    unGraphe.affichageGraphe();
    unGraphe.voronoiDistance();
    cout<<endl<<endl;
    unGraphe.voronoiLivraison();
    unGraphe.sauvergarderGraphe("./testSauvegarde.txt");
    return 0;
}
