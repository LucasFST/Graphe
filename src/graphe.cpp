<<<<<<< HEAD
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



=======
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
>>>>>>> refs/remotes/origin/main
