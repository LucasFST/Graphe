#include <fstream>
#include <iostream>
#include <string>
#include "graphe.h"

using namespace std;


int main() 
{
    Graphe unGraphe("./test.txt");
    unGraphe.testRegression();
    cout<<endl;
    unGraphe.affichageGraphe();
    cout<<endl;
    unGraphe.voronoiDistance();
    cout<<endl;
    unGraphe.voronoiLivraison();
    cout<<endl;
    unGraphe.sauvergarderGraphe("./testSauvegarde.txt");
    return 0;
}
