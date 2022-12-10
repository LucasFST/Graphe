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
    tableauAltitude = new int [nbLignes * nbColonnes];
    tableauLibrairieOuNon = new bool [nbLignes * nbColonnes];
    //par défaut au début les altitudes de toutes les cases sont initialisées à 0 et les bool à false
    for(unsigned int i = 0 ; i < nbLignes * nbColonnes ; i++)
    {
        tableauAltitude[i] = 0;
        tableauLibrairieOuNon[i] = false;
    }
}

Graphe::Graphe(const char * nomFichier)
{
    chargerGrapheAvecLibrairie(nomFichier);
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
    if(tableauLibrairieOuNon != NULL)
    {
        delete [] tableauLibrairieOuNon;
        tableauLibrairieOuNon = NULL;
        nbLignes = 0;
        nbColonnes = 0;
    }
}

int Graphe::getAltitude (unsigned int indiceLigne, unsigned int indiceColonne) const
{
    assert(indiceLigne < nbLignes);
    assert(indiceColonne < nbColonnes);
    return tableauAltitude [indiceLigne * nbColonnes + indiceColonne];
}

int Graphe::getAltitude (unsigned int indice) const
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

unsigned int Graphe::getIndiceLigne (unsigned int indice) const
{
    assert(indice < nbLignes * nbColonnes);
    return indice / nbColonnes;
}

unsigned int Graphe::getIndiceColonne (unsigned int indice) const
{
    assert(indice < nbLignes * nbColonnes);
    return indice % nbColonnes;
}

void Graphe::affichageGraphe() const
{
    for(unsigned int i = 0; i < nbColonnes * nbLignes; i++)
    {
        if(i % nbColonnes == 0) cout<<endl;
        if(tableauLibrairieOuNon[i]) 
        {
            cout<<"  "<<"L"<<tableauAltitude[i]<<"  ";
        }
        else
        {
            cout<<"  "<<tableauAltitude[i]<<"  ";
        }
    }
    cout<<endl;
}

void Graphe::setAltitude(unsigned int indice, int nouvelleAltitude)
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
            if(getIndiceLigne(indice) == 0) // si j'appartiens à la première ligne alors je n'ai pas de voisin Nord
            {
                return false;
            }
            else
            {
                return true;
            }
            break;
        
        case Est:
            if(getIndiceColonne(indice)==nbColonnes-1) // si j'appartiens à la dernière colonne (càd la plus à droite|est) alors je n'ai pas de voisin Est
            {
                return false;
            }
            else
            {
                return true;
            }
        
            break;

        case Sud:
            if(getIndiceLigne(indice)==nbLignes-1) // si j'appartiens à la dernière ligne alors je n'ai pas de voisin Sud
            {
                return false;
            }
            else
            {
                return true;
            }
            break;

        case Ouest:
            if(getIndiceColonne(indice)==0) // si j'appartiens à la première colonne (càd la plus à gauche|Ouest) alors je n'ai pas de voisin Ouest 
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
            assert( (voisinExiste(indice, Nord)) );
            return getVoisinNord(indice);
            break;
        
        case Est :
            assert( (voisinExiste(indice, Est)) );
            return getVoisinEst(indice);
            break;

        case Sud :
            assert( (voisinExiste(indice, Sud)) );
            return getVoisinSud(indice);
            break;

        case Ouest :
            assert( (voisinExiste(indice, Ouest)) );
            return getVoisinOuest(indice);
            break;
    }
}

bool Graphe::getLibrairieOuNon(unsigned int indice) const
{
    assert(indice < nbColonnes * nbLignes);
    return tableauLibrairieOuNon[indice];
}

void Graphe::setLibrairieOuNon (unsigned int indice, bool librairieOuNon)
{
    assert(indice < nbLignes * nbColonnes);
    tableauLibrairieOuNon [indice] = librairieOuNon;
}

void Graphe::chargerGrapheAvecLibrairie(const char * nomFichier)
{
    ifstream fichier(nomFichier);
    string buffer;
    if(fichier.is_open())
    {
        while(!fichier.eof())
        {
            fichier >> nbColonnes >> nbLignes;
            tableauAltitude = new int [nbLignes * nbColonnes];
            tableauLibrairieOuNon = new bool [nbLignes * nbColonnes];
            for (unsigned int i = 0; i < nbColonnes * nbLignes; i++) 
            {
                fichier >> buffer;
                if(buffer[0] == 'L')
                {
                    tableauLibrairieOuNon[i] = true;
                    buffer = buffer.erase(0,1);
                    tableauAltitude[i] = stoi(buffer);
                }
                else
                {
                    tableauLibrairieOuNon[i] = false;
                    tableauAltitude[i] = stoi(buffer);
                }  
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
            if( (i > 0) && (i % nbColonnes == 0) ) 
            {
                fichier << endl;
            }
            if(tableauLibrairieOuNon[i]) 
            {
                fichier<<"L"<<tableauAltitude[i]<<" ";
            }
            else
            {
                fichier<<tableauAltitude[i]<<" ";
            }
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

void Graphe::dijkstra(unsigned int indiceDepart, unsigned int * tabPrecedent, double * tabDistances) const
{
    assert(indiceDepart < nbColonnes * nbLignes);

    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        tabPrecedent[i] = i;    //chaque noeud est son propre précédent au début
        tabDistances[i] = numeric_limits<unsigned int>::infinity(); //on initialise les distances par rapport au noeud de départ à +infini
    }

    tabDistances[indiceDepart] = 0; //le noeud de départ est à une distance nulle de lui même

    std::priority_queue<PriorityQueue> FilePrio; 
    FilePrio.push({indiceDepart,tabDistances[indiceDepart]}); //le premier élément de la FilePrio est le noeud de départ

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

double Graphe::getDistance(unsigned int indice, Direction uneDirection) const
{
    assert(indice < nbColonnes * nbLignes);
    unsigned int voisin;
    double diffAltitude;
    switch(uneDirection)
    {
        case Sud:

            assert( (voisinExiste(indice, uneDirection)) );
            voisin = getVoisinSud(indice);
            diffAltitude = getAltitude(indice) - getAltitude(voisin);
            return ( sqrt (1 + diffAltitude * diffAltitude ));
            break;
        
        case Nord:
            assert( (voisinExiste(indice, uneDirection)) );
            voisin = getVoisinNord(indice);
            diffAltitude = getAltitude(indice) - getAltitude(voisin);
            return ( sqrt (1 + diffAltitude * diffAltitude ));
            break;
        
        case Est:
            assert( (voisinExiste(indice, uneDirection)) );
            voisin = getVoisinEst(indice);
            diffAltitude = getAltitude(indice) - getAltitude(voisin);
            return ( sqrt (1 + diffAltitude * diffAltitude ));
            break;

        case Ouest:
            assert( (voisinExiste(indice, uneDirection)) );
            voisin = getVoisinOuest(indice);
            diffAltitude = getAltitude(indice) - getAltitude(voisin);
            return ( sqrt (1 + diffAltitude * diffAltitude ));
            break;
    }
}

void Graphe::dijkstra(unsigned int * tabPrecedent, double * tabDistances) const
{
    std::priority_queue<PriorityQueue> FilePrio; 
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        if(tableauLibrairieOuNon[i])
        {
            tabDistances[i] = 0;
            FilePrio.push({i,tabDistances[i]}); //on ajoute à FilePrio le noeud si celui ci correspond à une librairie
        }
        else
        {
            tabDistances[i] = numeric_limits<unsigned int>::infinity(); //on initialise les distances par rapport aux librairies à +infini
        }
        tabPrecedent[i] = i;    //chaque noeud est son propre précédent au début
    }

    while(!FilePrio.empty())    //boucle jusqu'à ce que chaque noeud ait la distance minimale de sa plus proche librairie
    {
        PriorityQueue noeud = FilePrio.top();   //on récupère le ou l'un des noeuds avec la distance la plus petite
        FilePrio.pop(); // on le retire de FilePrio car il a déjà la distance minimale

        for(unsigned int i = 0; i < 4; i++) //on boucle pour accéder à ses éventuels voisins
        {
            if(voisinExiste(noeud.indice, static_cast<Direction>(i)))
            {
                unsigned int indiceVoisin = getVoisin(noeud.indice, static_cast<Direction>(i));
                if( !getLibrairieOuNon(indiceVoisin) )    //si le noeud d'indice voisin n'est pas une librairie 
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

void Graphe::voronoi (unsigned int * tabPrecedentVersIndiceLibrairie, double * tabDistance) const
{
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        transformerIndicePrecedentEnIndiceLibrairie(tabPrecedentVersIndiceLibrairie,i);
    }
    
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
         if(i % nbColonnes == 0) cout<<endl;
         if(tabDistance[i] == 0)
         {
            cout <<"\033[48;5;"<<tabPrecedentVersIndiceLibrairie[i]%257<<"m "<< "   L   "<<" \033[0m";
         }
         else
         {
            cout << "\033[48;5;"<<tabPrecedentVersIndiceLibrairie[i]%257<<"m "<< tabDistance[i]<<" \033[0m";
         }
    }
}


unsigned int Graphe::transformerIndicePrecedentEnIndiceLibrairie (unsigned int * tableau, unsigned int indice) const
{
    if(tableau[indice] != indice)
    {
        unsigned int newIndice = transformerIndicePrecedentEnIndiceLibrairie(tableau, tableau [ tableau [indice] ]);
        tableau[indice] = newIndice;
        return newIndice;
    }
    else
    {
        return indice;
    }
}


void Graphe::testRegression() const
{
    Graphe unGraphe(3,5);
    unGraphe.affichageGraphe();
    unsigned int unIndice = unGraphe.getIndice(2,4); //le sommet sur la troisième ligne et sur la cinquième colonne  
    assert(unIndice == 14);
    assert(unGraphe.getIndiceLigne(unIndice) == 2);
    assert(unGraphe.getIndiceColonne(unIndice) == 4);
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