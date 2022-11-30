#ifndef _GRAPHE_H
#define _GRAPHE_H

//! sommet (i, j)
//! indice = i x nbColonne + j
//! nord(i) = i - nbColonne
//! sud(i) = i + nbColonne
//! est(i) = i + 1
//! ouest(i) = i - 1
class Graphe
{
    public :
        
        Graphe (unsigned int nombreLignes, unsigned int nombreColonnes);
        ~Graphe ();
        float getAltitude (unsigned int numeroLigne, unsigned int numeroColonne) const;
        unsigned int getIndice (unsigned int numeroLigne, unsigned int numeroColonne) const;
        unsigned int getLigne (unsigned int indice) const;
        unsigned int getColonne (unsigned int indice) const;
        void affichageGraphe() const;
        void setAltitude(unsigned int indice, float nouvelleAltitude);
        unsigned int getVoisinNord(unsigned int indice);
        unsigned int getVoisinSud(unsigned int indice);
        unsigned int getVoisinNord(unsigned int indice);
        unsigned int getVoisinNord(unsigned int indice);

    /*
        int nord(induce) //! attention préconditions : le voisin doit exister
        int sud (indice) //! attention préconditions : le voisin doit exister
        int est (indice) //! attention préconditions : le voisin doit exister
        int ouest (indice) //! attention préconditions : le voisin doit exister
        int voisin (indice, numéroDuVoisin)
        int nbVoisin (indice)
        int voisinExiste? (indice, k)
    */

    private : 
        unsigned int nbColonnes, nbLignes; 
        float* tableauAltitude;
};









#endif