#ifndef _GRAPHE_H
#define _GRAPHE_H
#include <iostream>

enum Direction { Nord = 0, Est = 1, Sud = 2, Ouest = 3};
class Graphe
{
    public :

        //! les indices de lignes et de colonnes sont entre 0 et nbColonnes|nbLignes - 1
        
        //* Constructeurs et destructeur
        Graphe (unsigned int nombreLignes, unsigned int nombreColonnes);
        Graphe (const char*);
        ~Graphe ();

        //* Gestion de l'altitutde
        int getAltitude (unsigned int indiceLigne, unsigned int indiceColonne) const;
        int getAltitude (unsigned int indice) const;
        void setAltitude (unsigned int indice, int nouvelleAltitude);

        //* Gestion des indices
        unsigned int getIndice (unsigned int indiceLigne, unsigned int indiceColonne) const;
        unsigned int getIndiceLigne (unsigned int indice) const;
        unsigned int getIndiceColonne (unsigned int indice) const;
        
        //* Gestion des voisins
        bool voisinExiste (unsigned int indice, Direction uneDirection) const;
        unsigned int getVoisinNord (unsigned int indice) const;
        unsigned int getVoisinSud (unsigned int indice) const;
        unsigned int getVoisinEst (unsigned int indice) const;
        unsigned int getVoisinOuest (unsigned int indice) const;
        unsigned int getNbVoisins (unsigned int indice) const;
        unsigned getVoisin (unsigned int indice, Direction uneDirection) const;
        
        //* Affichage
        void affichageGraphe () const;
        
        //* Gestion des librairies (bool)
        // bool getLibrairieOuNon (unsigned int indice) const;
        // double getPrixLivraisonLibrairie (unsigned int indice) const;
        // void setLibrairieOuNon (unsigned int indice, bool librairieOuNon);
        // void setPrixLivraisonLibrairie (unsigned int indice, double tauxKilometrique);

        //* Distance entre deux noeuds
        double getDistance(unsigned int indice, Direction uneDirection) const;

        //* Gestion des dimensions du graphe
        unsigned int getNbColonnes () const;
        unsigned int getNbLignes () const;

        //* Procédure de Voronoi
        void voronoiDistance () const;
        void voronoiLivraison () const;
        
        //* Sauvegarder le graphe dans un fichier txt
        // void sauvergarderGraphe (const char * nomFichier) const;
        
        //* Procédure avec divers tests des fonctions
        //void testRegression() const;

    private : 
        struct PriorityQueueDistance 
        {
            unsigned int indice;
            double distance;

            bool operator < (const PriorityQueueDistance&pq) const
            {
                return (distance < pq.distance);
            }
        };

        struct PriorityQueueLivraison
        {
            unsigned int indice;
            double distance;
            double tauxKilometrique;

            bool operator < (const PriorityQueueLivraison &pq) const
            {
                return ( (distance * tauxKilometrique) < (pq.distance * pq.tauxKilometrique) );
            }
        };
        
        unsigned int nbColonnes, nbLignes; 
        int* tableauAltitude;
        std::pair <bool,double> * tableauLibrairieOuNon;

        //* Pour charger un graphe depuis un fichier txt
        void chargerGrapheAvecLibrairie (const char * nomFichier);

        //* Pour retrouver la librairie à partir du noeud précédent
        unsigned int transformerIndicePrecedentEnIndiceLibrairie (unsigned int * tableau, unsigned int indice) const;

        //* Algo de Dijkstra
        void dijkstraDistance (unsigned int * tabPrecedent, double * tabDistances) const;
        void dijkstraLivraison (unsigned int * tabPrecedent, std::pair <double,double> * tabPrixDistances) const;
};

#endif