#ifndef _GRAPHE_H
#define _GRAPHE_H

//! sommet (i, j)
//! indice = i x nbColonne + j
//! nord(i) = i - nbColonne
//! sud(i) = i + nbCcolonne
//! est(i) = i + 1
//! ouest(i) = i - 1

enum Direction { Nord = 0, Est = 1, Sud = 2, Ouest = 3};
class Graphe
{
    public :

        //! les indices de lignes et de colonnes sont entre 0 et nbColonnes|nbLignes - 1
        
        Graphe (unsigned int nombreLignes, unsigned int nombreColonnes);
        Graphe (const char*);
        ~Graphe ();
        float getAltitude (unsigned int indiceLigne, unsigned int indiceColonne) const;
        float getAltitude (unsigned int indice) const;
        unsigned int getIndice (unsigned int indiceLigne, unsigned int indiceColonne) const;
        unsigned int getLigne (unsigned int indice) const;
        unsigned int getColonne (unsigned int indice) const;
        void affichageGraphe () const;
        void setAltitude (unsigned int indice, float nouvelleAltitude);
        bool voisinExiste (unsigned int indice, Direction uneDirection) const;
        unsigned int getVoisinNord (unsigned int indice) const;
        unsigned int getVoisinSud (unsigned int indice) const;
        unsigned int getVoisinEst (unsigned int indice) const;
        unsigned int getVoisinOuest (unsigned int indice) const;
        unsigned int getNbVoisins (unsigned int indice) const;
        unsigned getVoisin (unsigned int indice, Direction uneDirection) const;
        double getDistance(unsigned int indice, Direction uneDirection) const;
        unsigned int getNbColonnes() const;
        unsigned int getNbLignes() const;

        void testRegression() const;

        
        void chargerGraphe (const char * nomFichier);
        void sauvergarderGraphe (const char * nomFichier) const;

        void dijkstra(unsigned int indiceDepart, unsigned int * tabPrecedent, double * tabDistances);

        void librairie(unsigned int * tabIndice, bool * tabLibrairie);

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
        float* tableauAltitude;
        
        
};









#endif