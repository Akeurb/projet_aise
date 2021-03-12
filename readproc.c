#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <proc/readproc.h>
#include "sensors2.c"

char* readGTK(char** PCPU2,char** ETAT2,char** PID2,char** PPID2,char** PMEM2,char** CMD2){
   // fillarg used for cmdline
   // fillstat used for cmd
   PROCTAB* proc = openproc(PROC_FILLARG | PROC_FILLSTAT);

   proc_t proc_info;

   // zero out the allocated proc_info memory
   memset(&proc_info, 0, sizeof(proc_info));

   int taille = 1000;
   char* PCPU = calloc(taille , sizeof(char));
   memset(PCPU, 0, taille);
   //char* PCPU2 = calloc(taille , sizeof(char));
   //memset(PCPU2, 0, taille);
   char* PCPU3 = calloc(taille , sizeof(char));
   memset(PCPU3, 0, taille);

   char* ETAT = calloc(taille , sizeof(char));
   memset(ETAT, 0, taille);
   //char* ETAT2 = calloc(taille , sizeof(char));
   //memset(ETAT2, 0, taille);
   char* ETAT3 = calloc(taille , sizeof(char));
   memset(ETAT3, 0, taille);

   char* PID = calloc(taille , sizeof(char));
   memset(PID, 0, taille);
   //char* PID2 = calloc(taille , sizeof(char));
   //memset(PID2, 0, taille);
   char* PID3 = calloc(taille , sizeof(char));
   memset(PID3, 0, taille);

   char* PPID = calloc(taille , sizeof(char));
   memset(PPID, 0, taille);
   //char* PPID2 = calloc(taille , sizeof(char));
   //memset(PPID2, 0, taille);
   char* PPID3 = calloc(taille , sizeof(char));
   memset(PPID3, 0, taille);

   char* PMEM = calloc(taille , sizeof(char));
   memset(PMEM, 0, taille);
   //char* PMEM2 = calloc(taille , sizeof(char));
   //memset(PMEM2, 0, taille);
   char* PMEM3 = calloc(taille , sizeof(char));
   memset(PMEM3, 0, taille);

   char* CMD = calloc(taille , sizeof(char));
   memset(CMD, 0, taille);
   //char* CMD2 = calloc(taille , sizeof(char));
   //memset(CMD2, 0, taille);
   char* CMD3 = calloc(taille , sizeof(char));
   memset(CMD3, 0, taille);



   printf("%% CPU");
   printf("\t\t Etat");
   printf("\t\t PID");
   printf("\t\t PPID");
   printf("\t\t %% MEM");
   printf("\t\t CMD \n\n\n");
   while (readproc(proc, &proc_info) != NULL) {

     sprintf(PCPU, "%.3f", pcpu2(proc_info.tid));
    if (atof(PCPU) > 0.01){
      PCPU3 = strdup(PCPU);
      strcat(PCPU3,"\n");
      strcat(*PCPU2,PCPU3);
      //printf("%s",PCPU2);
      printf("%s",PCPU);

      sprintf(ETAT, "%c", proc_info.state);
      ETAT3 = strdup(ETAT);
      strcat(ETAT3,"\n");
      strcat(*ETAT2,ETAT3);
      //printf("%s",ETAT2);
      printf("\t\t %s",ETAT);

      sprintf(PID, "%d", proc_info.tid);
      PID3 = strdup(PID);
      strcat(PID3,"\n");
      strcat(*PID2,PID3);
      printf("\t\t %s",PID);

      sprintf(PPID, "%d", proc_info.ppid);
      PPID3 = strdup(PPID);
      strcat(PPID3,"\n");
      strcat(*PPID2,PPID3);
      printf("\t\t %s",PPID);

      sprintf(PMEM, "%.3f", pmem2(proc_info.rss));
      PMEM3 = strdup(PMEM);
      strcat(PMEM3,"\n");
      strcat(*PMEM2,PMEM3);
      printf("\t\t %s",PMEM);

      if (proc_info.cmdline != NULL) {
        sprintf(CMD, "%s",strtok(*proc_info.cmdline, " "));
        CMD3 = strdup(CMD);
        strcat(CMD3,"\n");
        strcat(*CMD2,CMD3);
        printf("\t\t %s \n",CMD);

      }
      else {
        sprintf(CMD, "%s",proc_info.cmd);
        CMD3 = strdup(CMD);
        strcat(CMD3,"\n");
        strcat(*CMD2,CMD3);
        printf("\t\t %s \n",CMD);
      }
    }
   }
   free(PCPU);
   free(ETAT);
   free(PID);
   free(PPID);
   free(PMEM);
   free(CMD);
   free(PCPU3);
   free(ETAT3);
   free(PID3);
   free(PPID3);
   free(PMEM3);
   free(CMD3);

   closeproc(proc);
   sleep(1);
   system("clear");
   return *PCPU2,*ETAT2,*PID2,*PPID2,*PMEM2,*CMD2;
}
/*
int main(int argc, char** argv){
  while(1){
  int taille = 1000;
  char* pcpu = calloc(taille , sizeof(char));
  memset(pcpu, 0, taille);

  char* etat = calloc(taille , sizeof(char));
  memset(etat, 0, taille);

  char* pid = calloc(taille , sizeof(char));
  memset(pid, 0, taille);

  char* ppid = calloc(taille , sizeof(char));
  memset(ppid, 0, taille);

  char* pmem = calloc(taille , sizeof(char));
  memset(pmem, 0, taille);

  char* cmd = calloc(taille , sizeof(char));
  memset(cmd, 0, taille);

  pcpu,etat,pid,ppid,pmem,cmd = readGTK(&pcpu, &etat, &pid, &ppid, &pmem, &cmd );
  //printf("%s %s %s %s %s %s",pcpu,etat,pid,ppid,pmem,cmd);
  //printf("%s \n",etat);
  }
  return 0;
}
*/

/*
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

char* Colonne6;
Colonne5 = calloc(20 , sizeof(char));
memset(Colonne5, 0, 20);

Colonne1 = "% CPU";
Colonne2 = "Etat";
Colonne3 = "PID";
Colonne4 = "PPID";
Colonne5 = "% MEM";
Colonne6 = "CMD";
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
 printf("%-10s", Colonne5);
 printf("%-10s \n\n\n", Colonne6);
 while (readproc(proc, &proc_info) != NULL) {
  float pcpu = pcpu2(proc_info.tid);
  //printf("%-10d", UB);
  if (pcpu > 0.01){
    printf("%-10.3f", pcpu);
    printf("%-10c", proc_info.state);
    printf("%-10d %-10d", proc_info.tid, proc_info.ppid);
    printf("%-10.3f ", pmem2(proc_info.rss));
    if (proc_info.cmdline != NULL) {
      // print full cmd line if available
      char* ch = calloc(100,sizeof(char));
      memset(ch, 0, 100);
      ch = strtok(*proc_info.cmdline, " ");
      printf("%-10s\n",ch);
    }

    else {
      // if no cmd line use executable filename
      printf("%-10s\n", proc_info.cmd);
    }

   // mem résidente/ram * 100
  }
 }
 closeproc(proc);
 sleep(1);
 system("clear");
}
 return 0;
}
/*Prendre proc_info.tid en argument pour une nouvelle fonction dans cpu2.c.
Cette fonction return %cpu pour le pid proc_info.pid.*/
