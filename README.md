Notre projet est l'implémentation d'un outil
de monitoring.

Notre programme se divise en deux parties
d'un côté les capteurs, de l'autre l'interface.
Un makefile est fourni. 
Pour accéder à notre programme il faut saisir
./interface dans le bash après avoir exécuté 
la commande make.

Installer GTK: sudo apt-install libgtk-3-dev
Pour compilier GTK: gcc -o testGTK testGTK.c `pkg-config --cflags --libs gtk+-3.0`

Bonne utilisation !
