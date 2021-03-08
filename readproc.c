#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <proc/readproc.h>
#include "sensors2.c"

int main(int argc, char** argv)
{
while(1){
char* Colonne1;
Colonne1 = calloc(20 , sizeof(char));
memset(Colonne1, 0, 20);

char* Colonne2;
Colonne2 = calloc(20 , sizeof(char));
memset(Colonne2, 0, 20);

char* Colonne3;
Colonne3 = calloc(20 , sizeof(char));
memset(Colonne3, 0, 20);

char* Colonne4;
Colonne4 = calloc(20 , sizeof(char));
memset(Colonne4, 0, 20);

char* Colonne5;
Colonne5 = calloc(20 , sizeof(char));
memset(Colonne5, 0, 20);

Colonne1 = "% CPU";
Colonne2 = "Etat";
Colonne3 = "TID";
Colonne4 = "PPID";
Colonne5 = "CMD";
 // fillarg used for cmdline
 // fillstat used for cmd
 PROCTAB* proc = openproc(PROC_FILLARG | PROC_FILLSTAT);

 proc_t proc_info;

 // zero out the allocated proc_info memory
 memset(&proc_info, 0, sizeof(proc_info));

 // Affichage
 printf("%-10s", Colonne1);
 printf("%-10s", Colonne2);
 printf("%-10s", Colonne3);
 printf("%-10s", Colonne4);
 printf("%-10s \n\n\n", Colonne5);
 while (readproc(proc, &proc_info) != NULL) {
  float pcpu = pcpu2(proc_info.tid);
  //printf("%-10d", UB);
  if (pcpu > 0){
    printf("%-10.3f", pcpu);
    printf("%-10c", proc_info.state);
    printf("%-10d %-10d ", proc_info.tid, proc_info.ppid);
    if (proc_info.cmdline != NULL) {
      // print full cmd line if available
      printf("%-10s \n", *proc_info.cmdline);
    } else {
      // if no cmd line use executable filename
      printf("[%-10s]\n", proc_info.cmd);
    }
  }
  else{;}
 }

 closeproc(proc);
 sleep(3);
 system("clear");
}
 return 0;
}
/*Prendre proc_info.tid en argument pour une nouvelle fonction dans cpu2.c.
Cette fonction return %cpu pour le pid proc_info.pid.*/
