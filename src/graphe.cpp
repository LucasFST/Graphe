#include "graphe.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <cassert>
#include <string>
#include <queue>
#include <limits>

using namespace std;

Graphe::Graphe(unsigned int nombreLignes, unsigned int nombreColonnes)
{
    nbLignes = nombreLignes;
    nbColonnes = nombreColonnes;
    tableauAltitude = new float [nbLignes * nbColonnes];
    //par défaut au début les altitudes de toutes les cases sont initialisées à 0
    for(unsigned int i = 0 ; i < nbLignes * nbColonnes ; i++)
    {
        tableauAltitude[i] = 0;
    }
}

Graphe::Graphe(const char * nomFichier)
{
    chargerGraphe(nomFichier);
}

Graphe::~Graphe()
{
    if(tableauAltitude != NULL)
    {
        delete tableauAltitude;
        tableauAltitude = NULL;
        nbLignes = 0;
        nbColonnes = 0;
    }
}

float Graphe::getAltitude (unsigned int indiceLigne, unsigned int indiceColonne) const
{
    assert(indiceLigne < nbLignes);
    assert(indiceColonne < nbColonnes);
    return tableauAltitude [indiceLigne * nbColonnes + indiceColonne];
}

float Graphe::getAltitude (unsigned int indice) const
{
    assert(indice < nbColonnes * nbLignes);
    return tableauAltitude [indice];
}

unsigned int Graphe::getIndice (unsigned int indiceLigne, unsigned int indiceColonne) const
{
    assert(indiceLigne < nbLignes);
    assert(indiceColonne < nbColonnes);
    return (indiceLigne * nbColonnes + indiceColonne);
}

unsigned int Graphe::getLigne (unsigned int indice) const
{
    assert(indice < nbLignes * nbColonnes);
    return indice / nbColonnes;
}

unsigned int Graphe::getColonne (unsigned int indice) const
{
    assert(indice < nbLignes * nbColonnes);
    return indice % nbColonnes;
}

void Graphe::affichageGraphe() const
{
    for(unsigned int i = 0; i < nbColonnes * nbLignes; i++)
    {
        if(i % nbColonnes == 0) cout<<endl;
        cout<<"  "<<tableauAltitude[i]<<"  ";
    }
    cout<<endl;
}

void Graphe::setAltitude(unsigned int indice, float nouvelleAltitude)
{
    assert(indice < nbLignes * nbColonnes);
    tableauAltitude [indice] = nouvelleAltitude;
}

bool Graphe::voisinExiste (unsigned int indice, Direction uneDirection) const
{
    assert (indice < nbColonnes * nbLignes);
    switch (uneDirection)
    {
        case Nord:
            if(getLigne(indice) == 0) // si j'appartiens à la première ligne alors je n'ai pas de voisin Nord
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
        
        case Est:
            if(getColonne(indice)==nbColonnes-1) // si j'appartiens à la dernière colonne (càd la plus à droite|est) alors je n'ai pas de voisin Est
            {
                return false;
            }
            else
            {
                return true;
            }
        
            break;

        case Sud:
            if(getLigne(indice)==nbLignes-1) // si j'appartiens à la dernière ligne alors je n'ai pas de voisin Sud
            {
                return false;
            }
            else
            {
                return true;
            }
            break;

        case Ouest:
            if(getColonne(indice)==0) // si j'appartiens à la première colonne (càd la plus à gauche|Ouest) alors je n'ai pas de voisin Ouest 
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
    }
}

unsigned int Graphe::getVoisinNord (unsigned int indice) const
{
    assert(voisinExiste(indice, Nord) == true);
    return indice - nbColonnes;
}

unsigned int Graphe::getVoisinSud (unsigned int indice) const
{
    assert(voisinExiste(indice, Sud) == true);
    return indice + nbColonnes;
}

unsigned int Graphe::getVoisinEst (unsigned int indice) const
{
    assert(voisinExiste(indice, Est) == true);
    return indice + 1;
}

unsigned int Graphe::getVoisinOuest (unsigned int indice) const
{
    assert(voisinExiste(indice, Ouest) == true);
    return indice - 1;
}

unsigned int Graphe::getNbVoisins (unsigned int indice) const 
{
    unsigned int nombreDeVoisins = 0;
    if(voisinExiste(indice,Nord)) nombreDeVoisins++;
    if(voisinExiste(indice,Sud)) nombreDeVoisins++;
    if(voisinExiste(indice,Est)) nombreDeVoisins++;
    if(voisinExiste(indice,Ouest)) nombreDeVoisins++;
    return nombreDeVoisins;
}

void Graphe::chargerGraphe(const char * file) 
{ 
    ifstream fichier(file);
    if(fichier.is_open())
    {
        while(!fichier.eof())
        {
            fichier >> nbColonnes >> nbLignes;
            tableauAltitude = new float [nbLignes * nbColonnes];
            for (unsigned int i = 0; i < nbColonnes * nbLignes; i++) 
            {
                fichier >> tableauAltitude[i] ;
            }
        }
        fichier.close();
    }
    else
    {
        cout<<"Impossible d'ouvrir le fichier ! "<<endl;
    }
}

void Graphe::sauvergarderGraphe (const char * nomFichier) const
{
    ofstream fichier(nomFichier);
    if(fichier.is_open()) 
    {
        fichier << nbColonnes << " " << nbLignes << endl;
        for (unsigned int i = 0; i < nbColonnes * nbLignes; i++) 
        {
            if (i % nbColonnes == 0) 
            {
                fichier << endl;
            }
            fichier << tableauAltitude[i] << " ";
        }
        fichier.close();
    }
    else 
    {
        cout << "Impossible de sauvegarder le graphe !" << endl;
    }
}

void Graphe::dijkstra(const Graphe &g, unsigned int depart, unsigned int * precedent, double * distances) 
{
    unsigned int n;
    for(n = 0; n < g.nbColonnes*g.nbLignes ; n++) 
    {
        precedent[n] = n;
        distances[n] = numeric_limits<unsigned int>::infinity();
    }
    precedent[n] = n;
    distances[n] = 0;
    std::priority_queue<PriorityQueue> F; 
    F.push(depart,distances[depart]);
    while(! F.empty())
    {
        // n = noeud de F distance mini(sommet de file de priorité)
        F.pop(n); // retirer n de F
        for(unsigned int v=0;v<n;v++)
        {
            int dv = distances[v];
            int dn = distances[n];
            int dnv = dn;
            if((precedent[v] = v) || (dnv<dv))
            {
                distances[v] = dnv;
                precedent[v] = n;
                F.push(v,dnv);
            }
        }
    }
}


void Graphe::testRegression() const
{
    Graphe unGraphe(3,5);
    unGraphe.affichageGraphe();
    unsigned int unIndice = unGraphe.getIndice(2,4); //le sommet sur la troisième ligne et sur la cinquième colonne  
    assert(unIndice == 14);
    assert(unGraphe.getLigne(unIndice) == 2);
    assert(unGraphe.getColonne(unIndice) == 4);
    assert(unGraphe.getAltitude(unIndice) == 0);
    unGraphe.setAltitude(unIndice, 23);
    unGraphe.affichageGraphe();
    assert(unGraphe.getAltitude(unIndice) == 23);
    assert(unGraphe.getAltitude(2,4) == 23);
    assert(unGraphe.getNbVoisins(unIndice) == 2);
    assert(unGraphe.getVoisinNord(unIndice) == 9); //9 = 14 - 5
    unsigned int indiceVoisinNord = unGraphe.getVoisinNord(unIndice);
    unGraphe.setAltitude(indiceVoisinNord, 13);
    assert(unGraphe.getAltitude(indiceVoisinNord) == 13);
    unGraphe.affichageGraphe();
    assert(unGraphe.getVoisinOuest(unIndice) == 13);
    assert(unGraphe.voisinExiste(unIndice, Ouest) == true);
    assert(unGraphe.voisinExiste(unIndice, Sud) == false);
    cout<<endl<<"tests passés avec succès"<<endl<<endl;

}

//! on doit utiliser une file a priorité pour Dijkstra
//! on a besoin d'un tableau de précédent et un tableau de distances


double Graphe::getDistance(unsigned int indice, Direction uneDirection) const
{
    switch(uneDirection)
    {
        case Sud:
            if(voisinExiste(indice, uneDirection))
            {
                unsigned int voisin = getVoisinSud(indice);
                double diffAltitude = getAltitude(indice) - getAltitude(voisin);
                return ( sqrt (1 + diffAltitude * diffAltitude ));
            }
            return -1;
            break;
        
        case Nord:
            if(voisinExiste(indice, uneDirection))
            {
                unsigned int voisin = getVoisinNord(indice);
                double diffAltitude = getAltitude(indice) - getAltitude(voisin);
                return ( sqrt (1 + diffAltitude * diffAltitude ));
            }
            return -1;
            break;
        
        case Est:
            if(voisinExiste(indice, uneDirection))
            {
                unsigned int voisin = getVoisinEst(indice);
                double diffAltitude = getAltitude(indice) - getAltitude(voisin);
                return ( sqrt (1 + diffAltitude * diffAltitude ));
            }
            return -1;
            break;

        case Ouest:
            if(voisinExiste(indice, uneDirection))
            {
                unsigned int voisin = getVoisinOuest(indice);
                double diffAltitude = getAltitude(indice) - getAltitude(voisin);
                return ( sqrt (1 + diffAltitude * diffAltitude ));
            }
            return -1;
            break;
    }
}