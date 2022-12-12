#include "graphe.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <cassert>
#include <string>
#include <queue>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

Graphe::Graphe(unsigned int nombreLignes, unsigned int nombreColonnes)
{
    nbLignes = nombreLignes;
    nbColonnes = nombreColonnes;
    tableauAltitude = new int [nbLignes * nbColonnes];
    tableauLibrairieOuNon = new std::pair <bool,double> [nbLignes * nbColonnes];
    //par défaut au début les altitudes de toutes les cases sont initialisées à 0 et le tableau des librairies à (false,infinity)
    for(unsigned int i = 0 ; i < nbLignes * nbColonnes ; i++)
    {
        tableauAltitude[i] = 0;
        tableauLibrairieOuNon[i] = std::make_pair(false,numeric_limits<double>::infinity());
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
    }
    if(tableauLibrairieOuNon != NULL)
    {
        delete [] tableauLibrairieOuNon;
        tableauLibrairieOuNon = NULL;
    }
    nbLignes = 0;
    nbColonnes = 0;
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
    cout<<"Affichage du graphe en dur : "<<endl;
    for(unsigned int i = 0; i < nbColonnes * nbLignes; i++)
    {
        if(i % nbColonnes == 0) cout<<endl;
        if(tableauLibrairieOuNon[i].first) 
        {
            cout<<setw(5)<<"L"<<tableauAltitude[i]; //setw() définit la largeur de champ à utiliser pour les opérations de sortie.
        }
        else
        {
            cout<<setw(6)<<tableauAltitude[i];
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

void Graphe::ajouterLibrairie (unsigned int indice, double tauxKilometrique)
{
    assert (indice < nbColonnes * nbLignes);
    tableauLibrairieOuNon[indice].first = true;
    tableauLibrairieOuNon[indice].second = tauxKilometrique;
}

void Graphe::supprimerLibrairie (unsigned int indice)
{
    assert (indice < nbColonnes * nbLignes);
    tableauLibrairieOuNon[indice].first = false;
    tableauLibrairieOuNon[indice].second = numeric_limits<double>::infinity();
}

void Graphe::modifierTauxKilometriqueLibrairie (unsigned int indice, double newTauxkilometrique)
{
    assert(indice < nbColonnes * nbLignes);
    assert (tableauLibrairieOuNon[indice].first); //on verifie que le noeud d'indice 'indice' est bien une librairie
    tableauLibrairieOuNon[indice].second = newTauxkilometrique;
}

double Graphe::getTauxKilometriqueLibrairie (unsigned int indice) const
{
    assert(indice < nbColonnes * nbLignes);
    assert (tableauLibrairieOuNon[indice].first); //on verifie que le noeud d'indice 'indice' est bien une librairie
    return tableauLibrairieOuNon[indice].second;
}

bool Graphe::estUneLibrairieOuNon (unsigned int indice) const
{
    assert(indice < nbColonnes * nbLignes);
    return tableauLibrairieOuNon[indice].first;
}

void Graphe::chargerGrapheAvecLibrairie(const char * nomFichier)
{
    ifstream fichier(nomFichier);
    string buffer;
    if(fichier.is_open())
    {
        while(!fichier.eof())   //tant qu'on est pas arrivé à la fin du fichier
        {
            fichier >> nbColonnes >> nbLignes;
            tableauAltitude = new int [nbLignes * nbColonnes];
            tableauLibrairieOuNon = new std::pair <bool,double> [nbLignes * nbColonnes];
            for (unsigned int i = 0; i < nbColonnes * nbLignes; i++) 
            {
                fichier >> buffer;
                if(buffer[0] == 'L')    //si le premier caractère récupéré est L il s'agit d'une librairie
                {
                    tableauLibrairieOuNon[i].first = true;
                    buffer = buffer.erase(0,1); //on enlève L de la string
                    string temp;
                    stringstream input_stringstream(buffer);
                    getline(input_stringstream, temp,'/'); //on récupère les caractères jusqu'au /
                    tableauAltitude[i] = stoi(temp); //comme ça correspond à l'altitude on remplit le tableau d'altitude
                    getline(input_stringstream, temp); //on finit de récupérer les dernier caractères, càd ceux après le /
                    tableauLibrairieOuNon[i].second = stod(temp); //comme ça correspond au taux kilométrique on remplit le tableau de librairies
                }
                else
                {
                    tableauLibrairieOuNon[i].first = false;
                    tableauLibrairieOuNon[i].second = numeric_limits<double>::infinity();
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
            if(i % nbColonnes == nbColonnes - 1) // si on arrive en fin de ligne il ne faut pas mettre d'espace après le noeud
            {
                if(tableauLibrairieOuNon[i].first) //si la case d'indice i est une librairie
                {
                    fichier<<"L"<<tableauAltitude[i]<<"/"<<tableauLibrairieOuNon[i].second;
                }
                else
                {
                    fichier<<tableauAltitude[i];
                }
            }
            else
            {
                if(tableauLibrairieOuNon[i].first) //si la case d'indice i est une librairie
                {
                    fichier<<"L"<<tableauAltitude[i]<<"/"<<tableauLibrairieOuNon[i].second<<" ";
                }
                else
                {
                    fichier<<tableauAltitude[i]<<" ";
                }
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

void Graphe::dijkstraDistance(unsigned int * tabPrecedent, double * tabDistances) const
{
    std::priority_queue<PriorityQueueDistance> FilePrio; 
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        if(tableauLibrairieOuNon[i].first)
        {
            tabDistances[i] = 0;
            FilePrio.push({i,tabDistances[i]}); //on ajoute à FilePrio le noeud si celui ci correspond à une librairie
        }
        else
        {
            tabDistances[i] = numeric_limits<double>::infinity(); //on initialise les distances par rapport aux librairies à +infini
        }
        tabPrecedent[i] = i;    //chaque noeud est son propre précédent au début
    }

    while(!FilePrio.empty())    //boucle jusqu'à ce que chaque noeud ait la distance minimale de sa plus proche librairie
    {
        PriorityQueueDistance noeud = FilePrio.top();   //on récupère le ou l'un des noeuds avec la distance la plus petite
        FilePrio.pop(); // on le retire de FilePrio car il a déjà la distance minimale

        for(unsigned int i = 0; i < 4; i++) //on boucle pour accéder à ses éventuels voisins
        {
            if(voisinExiste(noeud.indice, static_cast<Direction>(i)))
            {
                unsigned int indiceVoisin = getVoisin(noeud.indice, static_cast<Direction>(i));
                if( !tableauLibrairieOuNon[indiceVoisin].first )    //si le noeud d'indice voisin n'est pas une librairie 
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

void Graphe::voronoiDistance () const
{

    unsigned int * tabPrecedent = new unsigned int[getNbColonnes() * getNbLignes()];
    double * tabDistances = new double [getNbColonnes() * getNbLignes()];

    dijkstraDistance(tabPrecedent, tabDistances);

    //Pour chaque noeud, on remonte au précédent de son précédent ... jusqu'à ce qu'on arrive à une librairie 
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        transformerIndicePrecedentEnIndiceLibrairie(tabPrecedent,i);
    }

    //! il y a 256 nuances de couleurs (de 0 à 255)
    //! donc pour avoir une couleur par librairie, on choisit la couleur égale à l'indice de la librairie % 256

    cout<<"Diagramme de Voronoi pour la distance : "<<endl;

    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
         if(i % nbColonnes == 0) cout<<endl;
         if(tabDistances[i] == 0)    //si la distance stokée est 0, c'est qu'il s'agit d'une librairie
         {
            cout <<"\033[48;5;"<<tabPrecedent[i]%256<<"m "<<setw(8)<<"LIBRARY"<<" \033[0m";
         }
         else //sinon il s'agit d'un noeud normal
         {
            cout << "\033[48;5;"<<tabPrecedent[i]%256<<"m "<< setw(8) << tabDistances[i] <<" \033[0m";
         }
    }
    cout<<endl;
    delete []tabPrecedent;
    delete []tabDistances;
}

unsigned int Graphe::transformerIndicePrecedentEnIndiceLibrairie (unsigned int * tableau, unsigned int indice) const
{
    if(tableau[indice] != indice)   //si le précédent du noeud n'est pas lui même (ce n'est pas une librairie)
    {
        //on appel récursivement la fonction pour la case dont l'indice est son précédent et le résultat retourné est
        //maintenant le précédent de son précédent ... donc enfaite l'indice de la librairie dont il est le plus proche

        unsigned int newIndice = transformerIndicePrecedentEnIndiceLibrairie(tableau, tableau [ tableau [indice] ]); 
        tableau[indice] = newIndice; 
        return newIndice;
    }
    else //si le précédent du noeud est lui-même (c'est une librairie)
    {
        return indice;
    }
}


void Graphe::testRegression() const
{
    //* Test avec le constructeur sans fichier txt
    Graphe unGraphe(3,5);

    //* Tests dimensions graphe
    assert(unGraphe.getNbColonnes()==5);
    assert(unGraphe.getNbLignes()==3);

    //* Tests indice
    unsigned int unIndice = unGraphe.getIndice(2,4); //le sommet sur la troisième ligne et sur la cinquième colonne  
    assert(unIndice == 14); //unIndice = 2 * 5 + 4 (indiceLigne * nbColonnes + indiceColonne)
    assert(unGraphe.getIndiceLigne(unIndice) == 2);
    assert(unGraphe.getIndiceColonne(unIndice) == 4);

    //* Tests altitude
    assert(unGraphe.getAltitude(unIndice) == 0); //par défaut les altitudes sont à 0
    unGraphe.setAltitude(unIndice, 23); //on la modifie à 23
    assert(unGraphe.getAltitude(unIndice) == 23);
    assert(unGraphe.getAltitude(2,4) == 23);

    //* Tests voisin
    assert(unGraphe.getNbVoisins(unIndice) == 2); //car le noeud d'indice unIndice est celui en bas à droite
    assert(unGraphe.getVoisinNord(unIndice) == 9); //9 = 14 - 5
    assert(unGraphe.getVoisinOuest(unIndice) == 13); //13 = 14 - 1
    assert(unGraphe.voisinExiste(unIndice, Ouest) == true);
    assert(unGraphe.voisinExiste(unIndice, Sud) == false);
    assert(unGraphe.voisinExiste(unIndice, Est) == false);
    assert(unGraphe.voisinExiste(unIndice, Nord) == true);
    assert(unGraphe.getVoisin(unIndice, Nord) == unGraphe.getVoisinNord(unIndice));
    assert(unGraphe.getVoisin(unIndice, Ouest) == unGraphe.getVoisinOuest(unIndice));
    
    //* Tests Distance
    assert(unGraphe.getDistance(unIndice, Nord) == sqrt(1 + (23 * 23)));
    unGraphe.setAltitude(9, 22); //on passe l'altitude du voisin Nord (d'indice 9) de 0 à 22
    assert(unGraphe.getDistance(unIndice, Nord) == sqrt(2));

    //* Tests des librairies
    assert (unGraphe.tableauLibrairieOuNon[unIndice].first == false); //ce n'est pas une librairie
    assert (!unGraphe.estUneLibrairieOuNon(unIndice));
    unGraphe.ajouterLibrairie(unIndice, 1.5);
    assert (unGraphe.tableauLibrairieOuNon[unIndice].first == true); //c'est maintenant une librairie
    assert (unGraphe.estUneLibrairieOuNon(unIndice));
    assert (unGraphe.tableauLibrairieOuNon[unIndice].second == 1.5);
    assert (unGraphe.tableauLibrairieOuNon[unIndice].second == unGraphe.getTauxKilometriqueLibrairie(unIndice));
    unGraphe.modifierTauxKilometriqueLibrairie(unIndice, 2.3);
    assert (unGraphe.tableauLibrairieOuNon[unIndice].second == unGraphe.getTauxKilometriqueLibrairie(unIndice));
    assert (unGraphe.tableauLibrairieOuNon[unIndice].second == 2.3);
    unGraphe.supprimerLibrairie(unIndice);
    assert (unGraphe.tableauLibrairieOuNon[unIndice].first == false); //c'est n'est plus une librairie

    cout<<endl<<"Tous les tests des fonctions et procédures ont été passés avec succès"<<endl;

}


void Graphe::dijkstraLivraison(unsigned int * tabPrecedent, std::pair <double,double> * tabPrixDistances) const //<double,double> pour <prix,distance>
{
    std::priority_queue<PriorityQueueLivraison> FilePrio; 
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        if(tableauLibrairieOuNon[i].first)
        {
            tabPrixDistances[i].first = tableauLibrairieOuNon[i].second;    //on récupère le taux kilométrique
            tabPrixDistances[i].second = 0; 
            //on ajoute à FilePrio le noeud car celui ci correspond à une librairie
            FilePrio.push({i,tabPrixDistances[i].second, tabPrixDistances[i].first }); 
        }
        else
        {
            //on initialise les prix et les distances par rapport aux librairies à +infini
            tabPrixDistances[i].first = numeric_limits<double>::infinity();
            tabPrixDistances[i].second = numeric_limits<double>::infinity(); 
        }
        tabPrecedent[i] = i;    //chaque noeud est son propre précédent au début
    }

    while(!FilePrio.empty())    //boucle jusqu'à ce que chaque noeud ait le choix optimal de librairie (livraison la moins chère)
    {
        PriorityQueueLivraison noeud = FilePrio.top();   //on récupère le ou l'un des noeuds avec la livraison optimale
        FilePrio.pop(); // on le retire de FilePrio car il a déjà la lvraison optimale

        for(unsigned int i = 0; i < 4; i++) //on boucle pour accéder à ses éventuels voisins
        {
            if(voisinExiste(noeud.indice, static_cast<Direction>(i)))
            {
                unsigned int indiceVoisin = getVoisin(noeud.indice, static_cast<Direction>(i));
                if( !tableauLibrairieOuNon[indiceVoisin].first )    //si le noeud d'indice voisin n'est pas une librairie 
                {
                    //le prix de la livraison = tauxKilométrique * distance
                    double prixLivraisonDepartVoisin = tabPrixDistances[indiceVoisin].first * tabPrixDistances[indiceVoisin].second;
                    double prixLivraisonDepartNoeud = noeud.distance * noeud.tauxKilometrique;
                    double prixLivraisonDepartNoeudVoisin = prixLivraisonDepartNoeud + 
                    (getDistance(noeud.indice, static_cast<Direction>(i)) * noeud.tauxKilometrique); 
                    
                    if((tabPrecedent[indiceVoisin] == indiceVoisin) || (prixLivraisonDepartNoeudVoisin < prixLivraisonDepartVoisin))
                    {
                        //si le noeud d'indice indiceVoisin n'avait pas encore été découvert ou 
                        //si prixLivraisonDepartNoeudVoisin < prixLivraisonDepartVoisin on MAJ les données du noeud d'indice indiceVoisin
                        tabPrecedent[indiceVoisin] = noeud.indice;
                        tabPrixDistances[indiceVoisin].first = noeud.tauxKilometrique;
                        tabPrixDistances[indiceVoisin].second = ( noeud.distance + getDistance(noeud.indice, static_cast<Direction>(i)));
                        //on ajoute à FilePrio le noeud d'indice indiceVoisin
                        FilePrio.push({indiceVoisin,tabPrixDistances[indiceVoisin].second, tabPrixDistances[indiceVoisin].first}); 
                    }
                }
            }
        }
    }
}

void Graphe::voronoiLivraison () const
{

    unsigned int * tabPrecedent = new unsigned int[getNbColonnes() * getNbLignes()];
    std::pair<double,double> * tabPrixDistances = new std::pair<double,double> [getNbColonnes() * getNbLignes()];

    dijkstraLivraison(tabPrecedent, tabPrixDistances);

    //Pour chaque noeud, on remonte au précédent de son précédent ... jusqu'à ce qu'on arrive à une librairie 
    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
        transformerIndicePrecedentEnIndiceLibrairie(tabPrecedent,i);
    }
    
    //! il y a 256 nuances de couleurs (de 0 à 255)
    //! donc pour avoir une couleur par librairie, on choisit la couleur égale à l'indice de la librairie % 256

    cout<<"Diagramme de Voronoi pour le coût de la livraison : "<<endl;

    for(unsigned int i = 0; i < nbColonnes * nbLignes ; i++) 
    {
         if(i % nbColonnes == 0) cout<<endl;
         if(tabPrixDistances[i].second == 0)    //si la distance stokée est 0, c'est qu'il s'agit d'une librairie
         {
            cout <<"\033[48;5;"<<tabPrecedent[i]%256<<"m "<<setw(8)<<"LIBRARY"<<" \033[0m";
         }
         else //sinon il s'agit d'un noeud normal
         {
            cout << "\033[48;5;"<<tabPrecedent[i]%256<<"m ";
            cout<<setw(8) << tabPrixDistances[i].first * tabPrixDistances[i].second  <<" \033[0m";
         }
    }
    cout<<endl;
    delete []tabPrixDistances;
    delete []tabPrecedent;
}