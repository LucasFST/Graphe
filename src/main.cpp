#include <fstream>
#include <iostream>
#include <string>
#include "graphe.h"

using namespace std;


int main() 
{
    Graphe unGraphe("./data/test.txt");
    unGraphe.testRegression();
    cout<<endl;
    unGraphe.affichageGraphe();
    cout<<endl;
    unGraphe.voronoiDistance();
    cout<<endl;
    unGraphe.voronoiLivraison();
    cout<<endl;
    unGraphe.sauvergarderGraphe("./data/testSauvegarde.txt");
    return 0;
}
