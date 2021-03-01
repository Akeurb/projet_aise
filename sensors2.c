#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// salut Thomas

void temps2(){

	time_t curtime;
	time(&curtime);
	printf("\t \t time : %s", ctime(&curtime));
}

char * uptime2(){
	char* TEMPS;
	FILE *fp = fopen("/proc/uptime", "r");
	float score[2] = {0};

	if(fp != NULL){
		fscanf(fp, "%f %f", &score[0], &score[1]);
		int heure = score[0] / 3600;
		int min = (score[0] - 3600*heure)/60;
		//printf("up since : %f \t avec temps de veille de : %f", score[0],score[1]);
		char h[10],m[10];
		sprintf(h,"%d",heure);
		sprintf(m,"%d",min);

		if(min < 10){
			TEMPS = strcat(h,":0");
			TEMPS = strcat(TEMPS,m);
			printf("\t \t \t up TEMPS %s",TEMPS);
		}
		else{
			TEMPS = strcat(h,":");
			TEMPS = strcat(TEMPS,m);
			printf("\t \t \t up TEMPS %s",TEMPS);
		}
	}
	fclose(fp);
	return TEMPS;
}


void memory2(){
	char blabla[50], blablabla[50];
	int val;
	int i = 0;
	FILE *memo = fopen("/proc/meminfo","r");

	while(i<7){
		fscanf(memo, "%s %d %s", blabla, &val, blablabla);
		if (i != 3)
			printf("%d \t %s %d %s\t \t", i, blabla, val/1000, blablabla);

		i++;

		if(i%2 == 0){
			printf("\n");
		}

		if(i ==6){
			break;
		}
	}

	fclose(memo);

	printf("\n");

	FILE *memo2 = fopen("/proc/swaps", "r");
	int v = 0;
	char mot1[50], mot2[50], mot3[50], mot4[50], mot5[50];

	while(v<2){
		fscanf(memo2, "%s %s %s %s %s", mot1, mot2, mot3, mot4, mot5);
		if(v == 1){
			printf("swap total : %s \t swap utilisé : %s \n", mot3, mot4);
		}
		v++;
	}

	fclose(memo2);
}

void processinfo2(){
		DIR *dir;
	struct dirent *sd;
	int i = 0;

	dir = opendir("/proc");

	if(dir == NULL)
	{
		printf("Error! Unable to open directory. \n");
		exit(1);
	}

	while( (sd = readdir(dir)) != NULL )
	{
		if(i>62)
			printf("\t %d \t >> %s \n", i, sd ->d_name);

		i++;
	}

	 int nb = i - 62;

	 printf("Tâches: %d total \n", nb);
	 closedir(dir);

	printf ("L'identifiant du processus est %d\n", (int) getpid ()); //affiche le PID du programme en cours interface

}
