ReadMe

Le projet CY-Trucks est un devoir à réaliser par groupe de 3 étudiants, qui doit permettre d'évaluer les capacités des étudiants à créér un code qui gère des fichiers à l'aide de différents outils (le language C, Shell, Gnuplot).
Le but de ce travail est de fournir un programme qui générerait des graphiques  résumant le contenu d'un fichier, bien trop grand pour être traité par les humains en se basant sur l'analyse de son contenu.
Le fichier en question regroupe les informations logistiques d’une société nationale de transport routier.

Différents traîtements sont exigés :
- le traitement -d1, qui donnerait un histogramme horizontal présentant le nombre de trajets en fonction du conducteur
- le traitement -d2, qui donnerait un histogramme horizontal présentant la distance totale parcourue en fonction du conducteur
- le traitement -l, qui donnerait un histogramme vertical présentant la distance la plus grande en fonction du conducteur (associé à son identifiant de trajet)
- le traitement -t, qui donnerait un histogramme regroupé présentant le nombre de trajets en fonction de la ville ainsi que le nombre de fois que la ville était le départ du trajet
- le traitement -s, qui donnerait un graphique qui fusionne trois courbes qui présentent les distances (min,max,moyenne) pour chaque étape en fonction du trajet

Dans notre devoir un traîtement suplémentaire est présenté :
- le traîtement -ch , qui permet d'avoir toutes les informations d'un conducteur
- le traitement -id , qui permet d'avoir toutes les information d'un trajet

Pour compiler notre programme veuillez saisir le chemin du fichier data.csv puis la commande voulu entre -d1 -d2 -l -t -s -id -ch. 
vous pouvez également saisir l'options -h pour recevoir de l'aide. 

Information supplémentaire le Dossier data se créera automatiquement s'il n'existe pas et mettra le fichier data dans le dossier (Car nous n'arrivons pas à créer un dossier vide sur Github)

Ce programme a été réalisé par Guesdon Axel, Hagard Loric et Tsybulskaya Anastasia, étudiants de préing 2, groupe 1 de CY-tech.
