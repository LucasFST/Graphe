#ifndef _GRAPHE_H
#define _GRAPHE_H

//! sommet (i, j)
//! indice = i x nbColonne + j
//! nord(i) = i - nbColonne
//! sud(i) = i + nbColonne
//! est(i) = i + 1
//! ouest(i) = i - 1

enum Direction { Nord = 0, Est = 1, Sud = 2, Ouest = 3};
class Graphe
{
    public :
        
        Graphe (unsigned int nombreLignes, unsigned int nombreColonnes);
        //Graphe (unfichier)
        ~Graphe ();
        float getAltitude (unsigned int numeroLigne, unsigned int numeroColonne) const;
        unsigned int getIndice (unsigned int numeroLigne, unsigned int numeroColonne) const;
        unsigned int getLigne (unsigned int indice) const;
        unsigned int getColonne (unsigned int indice) const;
        void affichageGraphe () const;
        void setAltitude (unsigned int indice, float nouvelleAltitude);
        bool voisinExiste (unsigned int indice, Direction uneDirection);
        unsigned int getVoisinNord (unsigned int indice, Direction Nord);
        unsigned int getVoisinSud (unsigned int indice, Direction Sud);
        unsigned int getVoisinEst (unsigned int indice, Direction Est);
        unsigned int getVoisinOuest (unsigned int indice, Direction Ouest);
        unsigned int getNbVoisins (unsigned int indice);

    private : 
        unsigned int nbColonnes, nbLignes; 
        float* tableauAltitude;
        //fonction lire le fichier
};









#endif