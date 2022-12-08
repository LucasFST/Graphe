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
        delete [] tableauAltitude;
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

unsigned int Graphe::getVoisin (unsigned int indice, Direction uneDirection) const
{
    switch (uneDirection)
    {
        case Nord :
            if(voisinExiste(indice, Nord))
            {
                return getVoisinNord(indice);
            }
            break;
        
        case Est :
            if(voisinExiste(indice, Est))
            {
                return getVoisinEst(indice);
            }
            break;

        case Sud :
            if(voisinExiste(indice, Sud))
            {
                return getVoisinSud(indice);
            }
            break;

        case Ouest :
            if(voisinExiste(indice, Ouest))
            {
                return getVoisinOuest(indice);
            }
            break;
    }
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

unsigned int Graphe::getNbColonnes() const
{
    return nbColonnes;
}

unsigned int Graphe::getNbLignes() const
{
    return nbLignes;
}

void Graphe::dijkstra(unsigned int indiceDepart, unsigned int * tabPrecedent, double * tabDistances) 
{
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        tabPrecedent[i] = i;    //chaque noeud est son propre précédent au début
        tabDistances[i] = numeric_limits<unsigned int>::infinity(); //on initialise les distances par rapport au noeud de départ à +infini
    }

    //TODO Pour chaque librairie

    tabDistances[indiceDepart] = 0; //le noeud de départ est à une distance nulle de lui même
    std::priority_queue<PriorityQueue> FilePrio; 
    FilePrio.push({indiceDepart,tabDistances[indiceDepart]}); //le premier élément de la FilePrio est le noeud de départ
    
    //TODO fin boucle librairie

    while(!FilePrio.empty())    //boucle jusqu'à ce que chaque noeud ait la distance minimale du noeud de départ
    {
        PriorityQueue noeud = FilePrio.top();   //on récupère le noeud avec la distance au noeud de départ la plus petite
        FilePrio.pop(); // on le retire de FilePrio car il a déjà la distance minimale
        for(unsigned int i = 0; i < 4; i++) //on boucle pour accéder à ses éventuels voisins
        {
            if(voisinExiste(noeud.indice, static_cast<Direction>(i)))
            {
                unsigned int indiceVoisin = getVoisin(noeud.indice, static_cast<Direction>(i));
                if(indiceVoisin != indiceDepart)    //si indiceVoisin == indiceDepart on s'en moque car la distance est déjà minimale
                {
                    double distanceDepartVoisin = tabDistances[indiceVoisin];
                    double distanceDepartNoeud = tabDistances [noeud.indice];
                    double distanceDepartNoeudVoisin = distanceDepartNoeud + getDistance(noeud.indice, static_cast<Direction>(i)); 
                    if((tabPrecedent[indiceVoisin] == indiceVoisin) || (distanceDepartNoeudVoisin < distanceDepartVoisin))
                    {
                        //si le noeud d'indice indiceVoisin n'avait pas encore été découvert ou 
                        //si distanceDepartNoeudVoisin < distanceDepartVoisin on MAJ les données du noeud d'indice indiceVoisin
                        tabPrecedent[indiceVoisin] = noeud.indice;
                        tabDistances[indiceVoisin] = distanceDepartNoeudVoisin;
                        FilePrio.push({indiceVoisin,tabDistances[indiceVoisin]}); //on ajoute à FilePrio le noeud d'indice indiceVoisin
                    }
                }
            }
        }
    }
}


void Graphe::librairie(unsigned int * tabIndice, bool * tabLibrairie)
{
    string buffer;
    for(unsigned int i=0; i<nbLignes; i++)
    {
        for(unsigned int j=0; j<nbColonnes; j++)
        {
            if(buffer[0] == 'L')
            {
                tabLibrairie[i*nbColonnes+nbLignes] = true;
                buffer = buffer.erase(0,1);
                tabIndice[i*nbColonnes+nbLignes] = stoi(buffer);
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