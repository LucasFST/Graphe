# Projet de LIFAPC

## Membres
 - Faustmann Lucas
 - Brun Matis

Cahier des charges :
    - Le but de ce projet était, à partir d'un graphe et à l'aide de l'algorithme de Dijkstra et du diagramme de Voronoï, de déterminer pour chaque noeud la livraison optimale, c'est-à-dire d'emprunter le chemin le moins coûteux en terme de distances et de taux kilométriques vis-à-vis des différentes librairies.

Fichiers textes : 
    - Les fichiers textes sont ceux qui stockent les graphes.
    - Sur la première ligne se trouvent les dimensions du graphe Largeur (= nombre de colonnes) et Hauteur (= nombre de lignes).
    - Puis le graphe est modélisé par les altitudes des Largeur*Hauteur sommets listés ligne par ligne du haut vers le bas et de gauche vers la droite.
    - Si le noeud comporte un 'L' au début alors c'est une librairie, le nombre suivant le 'L' est alors son altitude et le nombre après le / représente le coût kilométrique de la livraison.
    - Attention, les noeuds du fichier texte doivent être succédés par un espace, hormis ceux en fin de ligne.

Voici un exemple de fichier texte adéquat :

4 3
L1/2 2 2 6
5 L9/3 8 15
8 9 L20/4 14

## Arborescence :

GrapheLIFAPC/
	├─ bin/
	│  ├─ contient l'exécutable du projet
	├─ data/
	│  ├─ contient les fichiers .txt à manipuler
	├─ obj/
	│  ├─ contient les fichiers objets du projet 
    ├─ src/
	│  ├─ graphe.cpp
    │  ├─ graphe.h
    │  ├─ main.cpp
    ├─ Makefile
	├─ README.md


## Compilation du programme :
 - commande : make

## Execution du programme :
 - commande : ./bin/exe

## Suppression es éxécutables dans /bin et les .o dans /obj) : 

    commande : make clean 