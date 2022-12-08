#ifndef _GRAPHE_H
#define _GRAPHE_H

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
        bool getLibrairieOuNon (unsigned int indice) const;
        void setLibrairieOuNon (unsigned int indice, bool librairieOuNon);

        //* Distance entre deux noeuds
        double getDistance(unsigned int indice, Direction uneDirection) const;

        //* Gestion des dimensions du graphe
        unsigned int getNbColonnes () const;
        unsigned int getNbLignes () const;

        //* Algo de Dijkstra
        void dijkstra (unsigned int indiceDepart, unsigned int * tabPrecedent, double * tabDistances) const;
        void dijkstra (unsigned int * tabPrecedent, double * tabDistances) const;

        //* Procédure de Voronoi
        void voronoi (unsigned int * tabPrecedent, double * tabDistance) const;
        
        //* Sauvegarder le graphe dans un fichier txt
        void sauvergarderGraphe (const char * nomFichier) const;
        
        //* Procédure avec divers tests des fonctions
        void testRegression() const;

    private : 
        struct PriorityQueue 
        {
            unsigned int indice;
            double distance;

            bool operator < (const PriorityQueue &pq) const
            {
                return (distance < pq.distance);
            }
        };
        
        unsigned int nbColonnes, nbLignes; 
        int* tableauAltitude;
        bool* tableauLibrairieOuNon;
        void chargerGrapheAvecLibrairie (const char * nomFichier);
        unsigned int transformerIndicePrecedentEnIndiceLibrairie (unsigned int * tableau, unsigned int indice) const;
};

#endif