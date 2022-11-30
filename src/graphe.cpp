#include "graphe.h"
#include <iostream>
#include <cassert>

using namespace std;

Graphe::Graphe(unsigned int nombreLignes, unsigned int nombreColonnes)
{
    nbLignes = nombreLignes;
    nbColonnes = nombreColonnes;
    tableauAltitude = new float [nbLignes * nbColonnes];
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

float Graphe::getAltitude (unsigned int numeroLigne, unsigned int numeroColonne) const
{
    assert(numeroLigne < nbLignes);
    assert(numeroColonne < nbColonnes);
    return tableauAltitude [numeroLigne * nbColonnes + numeroColonne];
}

unsigned int Graphe::getIndice (unsigned int numeroLigne, unsigned int numeroColonne) const
{
    assert(numeroLigne < nbLignes);
    assert(numeroColonne < nbColonnes);
    return (numeroLigne * nbColonnes + numeroColonne);
}

unsigned int Graphe::getLigne (unsigned int indice) const
{
    assert(indice < nbLignes * nbColonnes);
    return indice/nbColonnes;
}

unsigned int Graphe::getColonne (unsigned int indice) const
{
    assert(indice < nbLignes * nbColonnes);
    return indice%nbColonnes;
}

void Graphe::affichageGraphe() const
{
    for(unsigned int i = 0; i < nbColonnes * nbLignes; i++)
    {
        if(i % nbColonnes == 0) cout<<endl;
        cout<<"  "<<tableauAltitude[i]<<"  ";
    }
}

void Graphe::setAltitude(unsigned int indice, float nouvelleAltitude)
{
    assert(indice < nbLignes * nbColonnes);
    tableauAltitude [indice] = nouvelleAltitude;
}

bool Graphe::voisinExiste (unsigned int indice, Direction uneDirection)
{
    assert (indice < nbColonnes * nbLignes);
    switch (uneDirection)
    {
        case Nord:
            if(getLigne(indice)==0) // si j'appartiens à la première ligne 
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
        
        case Est:
            if(getColonne(indice)==nbColonnes-1) // si j'appartiens à la dernière colonee (càd la plus à droite)
            {
                return false;
            }
            else
            {
                return true;
            }
        
            break;

        case Sud:
            if(getLigne(indice)==nbLignes-1) // si j'appartiens à la dernière ligne
            {
                return false;
            }
            else
            {
                return true;
            }
            break;

        case Ouest:
            if(getColonne(indice)==0) // si j'appartiens à la première colonne (càd la plus à gauche) 
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
    
        default:
            break;
    }
}

unsigned int Graphe::getVoisinNord (unsigned int indice, Direction Nord)
{
    assert(voisinExiste(indice, Nord) == true);
    return indice - nbColonnes;
}

unsigned int Graphe::getVoisinSud (unsigned int indice, Direction Sud)
{
    assert(voisinExiste(indice, Sud) == true);
    return indice + nbColonnes;
}

unsigned int Graphe::getVoisinEst (unsigned int indice, Direction Est)
{
    assert(voisinExiste(indice, Est) == true);
    return indice + 1;
}

unsigned int Graphe::getVoisinOuest (unsigned int indice, Direction Ouest)
{
    assert(voisinExiste(indice, Ouest) == true);
    return indice - 1;
}

 unsigned int Graphe::getNbVoisins (unsigned int indice)
 {
    unsigned int nombreDeVoisins = 0;
    if(voisinExiste(indice,Nord)) nombreDeVoisins++;
    if(voisinExiste(indice,Sud)) nombreDeVoisins++;
    if(voisinExiste(indice,Est)) nombreDeVoisins++;
    if(voisinExiste(indice,Ouest)) nombreDeVoisins++;
    return nombreDeVoisins;
 }

 void Graphe::file(const char * file) {
    
} 
