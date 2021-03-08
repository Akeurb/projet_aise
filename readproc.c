#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <proc/readproc.h>
#include "sensors2.c"

int main(int argc, char** argv)
{
char* Colonne1 = malloc(20 * sizeof(char));
char* Colonne2 = malloc(20 * sizeof(char));
char* Colonne3 = malloc(20 * sizeof(char));
char* Colonne4 = malloc(20 * sizeof(char));
char* Colonne5 = malloc(20 * sizeof(char));
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
  int UB,UA,SB,SA = pcpu2(proc_info.tid);
  //printf("%-10d", UB);
  printf("%-10d", proc_info.pcpu);
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

 closeproc(proc);
 return 0;
}
/*Prendre proc_info.tid en argument pour une nouvelle fonction dans cpu2.c.
Cette fonction return %cpu pour le pid proc_info.pid.*/
