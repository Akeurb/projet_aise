Notre projet est l'implémentation d'un outil de monitoring. Cette version n'utilise pas GTK et affiche sur le terminal.

Notre programme se divise en deux parties, d'un côté les capteurs (sensors2.c), de l'autre l'interface(testGTK2.c et readproc.c).
Un makefile est fourni. 
Pour accéder à notre programme il faut saisir "./readproc" dans le bash après avoir exécuté 
la commande "make".

Installer GTK: sudo apt-install libgtk-3-dev

Installer libproc: sudo apt install libprocps-dev

Pour compilier le programme: gcc -o readproc readproc.c -lprocps

Pour executer le programme: ./readproc
    ou ./tcpserver dans un terminal
    et ./tcpclient dans un autre terminal

Bonne utilisation !
