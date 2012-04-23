Prunelle
========

Programme d'agrégation d'éléments en fonction de liens

Ce programme reprend les idées de Christophe Terrier pour Mirabel et calculant
des liens entre zones, en général des communes ou ensemble de communes, 
et en agrégeant ces zones en fonction de la valeur d'un lien, historiquement le
taux d'actif sortants de la zone par rapport à l'ensemble des actifs occupés.

Le programme en C++ se compile avec la commande ::

    make

Il faut un fichier texte avec les flux en entrée .

Exemple ::

  01001   01001   45
  01001   01004   1
  01001   01028   0
  01001   01053   28
  01001   01074   1
  01001   01092   1
  01001   01093   89
  01001   01109   2
  01001   01146   0
  01001   01183   1
  01001   01188   0
  01001   01194   3

Ensuite, il faut le préparer avec le programme prepare_flux ::

    ./prepare_flux entree sortie

Le programme prend le fichier ainsi crée en entrée ::

    ./prunelle < sortie

La commande ::

    ./prunelle -h 

donne différentes options du programme
