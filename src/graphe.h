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

        //! les indices de lignes et de colonnes sont entre 0 et nbColonnes|nbLignes - 1
        
        Graphe (unsigned int nombreLignes, unsigned int nombreColonnes);
        Graphe (const char*);
        ~Graphe ();
        int getAltitude (unsigned int indiceLigne, unsigned int indiceColonne) const;
        int getAltitude (unsigned int indice) const;
        unsigned int getIndice (unsigned int indiceLigne, unsigned int indiceColonne) const;
        unsigned int getLigne (unsigned int indice) const;
        unsigned int getColonne (unsigned int indice) const;
        void affichageGraphe () const;
        void setAltitude (unsigned int indice, int nouvelleAltitude);
        bool voisinExiste (unsigned int indice, Direction uneDirection) const;
        unsigned int getVoisinNord (unsigned int indice) const;
        unsigned int getVoisinSud (unsigned int indice) const;
        unsigned int getVoisinEst (unsigned int indice) const;
        unsigned int getVoisinOuest (unsigned int indice) const;
        unsigned int getNbVoisins (unsigned int indice) const;

        void testRegression() const;

        //TODO fonction lire le fichier
        void file(const char * file);

    private : 
        unsigned int nbColonnes, nbLignes; 
        int* tableauAltitude;
        
        
};









#endif