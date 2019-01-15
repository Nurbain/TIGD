# Projet TIGD
--------------------------

## Article choisi : *"Extension de l'arbre des formes aux images couleur"*

## Articles 

### *Calcul de l'arbre des formes en temps linéaire*

Cette article décris une méthode permettant de réaliser un arbre de forme sur une image en nuance de gris. Cet article fut nécessaire pour pouvoir développer la méthode dans l'article suivant, article ayant était choisi pour ce projet. 

### *Extension de l'arbre des formes aux images couleur*




### *Structure dépot*

Le dossier contenant le coeur du projet et code réalisé se trouve dans le dossier *"TreeOfShape"*.   
Ce même dossier contient la classe :  
 - **TreeOfShape** étant la classe gérant les arbres de formes classique codé suivant l'article “Calcul de l'arbre des formes en temps linéaire” donné.
 - **ColorTreeOfShape** étant la classe permettant de créer des arbres de formes sur images de couleurs suivant l'article “Extension de l'arbre des formes aux images couleur” donné.   
 
Les dossiers *"ImagesTest"* et *"Result"* contiennent respectivement les jeux de tests utilisés et leurs résultats.


### *Documentation technique*

L’image couleur rentrée est chargée dans un objet Image de la librairie Cimg, elle est ensuite divisé en une image suivant la composante rouge, une suivant la composante vert, et une suivant la composante bleu dans la classe *“ColorTreeOfShape”*. 
Les arbres des formes (classe “TreeOfShape”), sont ensuite calculés suivant la méthode décrite plus haut. Les aires des formes sont calculées suivant la méthode présentée précédemment. 
Pour obtenir une image représentant la fusion des aires des formes des différentes composantes nous appliquons d'abord un gradient Sobel sur les images  (![Sobel sur l'image de composante Rouge](/result/GradientRouge.pgm)) par la suite la fusion des aires des formes en chaque point dans l'image est calculé suivant cette méthode :    
![methode](/ReadmeMedia/methodeAire.png)
basé sur les images gradients des différentes composantes de couleur, r pour rouge, b pour bleu et g pour vert. 

L’arbre des formes final correspond à l’arbre des formes de l’image représentant la fusion des aires des composantes.


### *Comment utiliser le code ?*

Pour réaliser un arbre de forme sur image de couleur, le nom du fichier sous le format .ppm (concaténé à son chemin) doit être rentré dans le fichier main du projet sur la ligne **colorTreeOfShape c_tree("chemin/fichier.ppm");**

Les fonctions pouvant être utiles sont : 
- __*test_im(nom de l’image)*__ permettant de calculer l’arbre et affiche le temps de calcul de celui-ci
- __*tree.save_graph(destination)*__ enregistrant le graphe dans le fichier destination (la commande dot doit être utilisé pour le visualiser)
- __*tree.removeShape(seuil)*__ retire les forme possédant une aire inférieure à un seuil donné
-  __*tree = TreeOfShape(image)*__ permet de stocker et créer un arbre suivant une image donnée


### *Résultats de jeux de tests*

Voici quelques résultats obtenus sur deux images tests. 

![Test 1](/ReadmeMedia/JeuxTest.jpg) ![Résultat 1](/ReadmeMedia/resultat1.jpg)

![Test 1](/ReadmeMedia/JeuxTest2.jpg) ![Résultat 1](/ReadmeMedia/resultat2.jpg)

### *Problème & perspectives*

Le type des images (U8 en utilisant la libraire TIM) étant trop petit pour les images de couleurs fut un problème. En effet, les aires des formes peuvent être trop grandes et donc sont mal stockées. 
Le problème subsistant est dù à l'algorithme de calcul de l'arbre des formes sur les images d'aires, en effet celui-ci trop lent pour ce type d'image ayant une grande diversité de données.

Cependant, les perspectives possibles peuvent être une amélioration des arbres des formes ainsi que l'ajout d'un traitement sur ces arbres. 


--------------------------

### *Auteurs*
Quentin Wendling - CMI IRVIIJ   
Urbain Nathan - CMI IRVIIJ

Licence : **MIT**
