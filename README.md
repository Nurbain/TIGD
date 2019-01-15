# Projet TIGD
--------------------------

### *Extension de l'arbre des formes aux images couleur*




### *Structure dépot*

Le dossier contenant le coeur du projet et code réalisé se trouve dans le dossier *"TreeOfShape"*.   
Ce même dossier contient la classe :  
 - **TreeOfShape** étant la classe gérant les arbres de formes classique codé suivant l'article “Calcul de l'arbre des formes en temps linéaire” donné.
 - **ColorTreeOfShape** étant la classe permettant de créer des arbres de formes sur images de couleurs suivant l'article “Extension de l'arbre des formes aux images couleur” donné.   
 
Les dossiers *"ImagesTest"* et *"Result"* contiennent respectivemement les jeux de tests utilisé et leurs résultats.


### *Documentation technique*





### *Comment utiliser le code ?*

Pour réaliser un arbre de forme sur image de couleur, le nom du fichier sous le format .ppm (concaténé à son chemin) doit être rentré dans le fichier main du projet sur la ligne **TreeOfShape tree = TreeOfShape(Chemin/Fichier.ppm);**

Les fonctions pouvant être utiles sont : 
- *test_im(nom de l’image)* permettant de calculer l’arbre et affiche le temps de calcul de celui-ci
- *tree.save_graph(destination)* enregistrant le graphe dans le fichier destination (la commande dot doit être utilisé pour le visualiser)
- *tree.removeShape(seuil)* retire les forme possédant une aire inférieure à un seuil donné
-  *tree = TreeOfShape(image)* permet de stocker et créer un arbre suivant une image donnée


### *Jeux de tests*



### *Problème & perspectives*

Le type des images (U8 en utilisant la libraire TIM) étant trop petit pour les images de couleurs fut un problème. En effet, les aires des formes peuvent être trop grande et donc sont mal stocké. 
Le problème subistant est du à l'algorithme de calcul de l'arbre des formes sur les images d'aires, en effet celui-ci trop lent pour ce type d'image ayant une grande diversité de données.

Cependant les perspectives possibles peuvent être une amélioration des arbres des formes ainsi que l'ajout d'un traitement sur ces arbres. 


--------------------------

### *Auteurs*
Quentin Wendling - CMI IRVIIJ   
Urbain Nathan - CMI IRVIIJ

Licence : **MIT**
