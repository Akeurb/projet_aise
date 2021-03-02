#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// salut Thomas

char * date2(char* DATE){
	//printf("DATE = %s\n",DATE); ????????
	time_t curtime;
	time(&curtime);
	printf("\t \t time : %s", ctime(&curtime));
	DATE = strcat(ctime(&curtime),"UP Time : ");
	return DATE;
}

char * uptime2(char* TEMPS){
	//printf("TEMPS = %s\n",TEMPS); ????????????
	FILE *fp = fopen("/proc/uptime", "r");
	float score[2] = {0};

	if(fp != NULL){
		fscanf(fp, "%f %f", &score[0], &score[1]);
		int heure = score[0] / 3600;
		int min = (score[0] - 3600*heure)/60;
		//printf("up since : %f \t avec temps de veille de : %f", score[0],score[1]);
		char h[50],m[50];
		sprintf(h,"%d",heure);
		sprintf(m,"%d",min);

		if(min < 10){
			TEMPS = strcat(h,"h0");
			TEMPS = strcat(TEMPS,m);
			TEMPS = strcat(TEMPS,"min");
			printf("\t \t \t up Temps %s \n",TEMPS);
		}
		else{
			TEMPS = strcat(h,"h");
			TEMPS = strcat(TEMPS,m);
			TEMPS = strcat(TEMPS,"min");
			printf("\t \t \t up Temps %s \n",TEMPS);
		}
	}
	fclose(fp);
	return TEMPS;
}

char * memory2(char* MEM,char* MEM2){
	char blabla[50], blablabla[50];
	int val;
	int i = 0;
	FILE *memo = fopen("/proc/meminfo","r");
	printf("MEM = %s\n",MEM);
	printf("MEM2 = %s\n",MEM2);
	char val_c[50];
	while(i<7){
		fscanf(memo, "%s %d %s", blabla, &val, blablabla);
		if (i != 3){
			//printf("%s %d %s \n", blabla, val/1000, blablabla);
			sprintf(val_c,"%d",val/1000);
			MEM = strcat(MEM2,blabla);
			MEM = strcat(MEM,"\t");
			MEM = strcat(MEM,val_c);
			MEM = strcat(MEM,"\t");
			MEM = strcat(MEM,blablabla);
			MEM = strcat(MEM,"\n");
			strcpy(MEM2,MEM);
		}
		i++;

		if(i ==6){
			break;
		}
	}

	fclose(memo);
	//printf("%s",MEM);
	return MEM;
}


char * swap2(char* SWAP){
	printf("SWAP %s \n",SWAP);
	FILE *memo2 = fopen("/proc/swaps", "r");
	int v = 0;
	char mot1[50], mot2[50], mot3[50], mot4[50], mot5[50];

	while(v<2){
		fscanf(memo2, "%s %s %s %s %s", mot1, mot2, mot3, mot4, mot5);
		if(v == 1){
			printf("Swap total : %s \nSwap utilisé : %s \n", mot3, mot4);
			char A[] = "Swap total : ";
			SWAP = strcat(A,mot3);
			SWAP = strcat(SWAP,"\n");
			SWAP = strcat(SWAP,"Swap utilisé : ");
			SWAP = strcat(SWAP,mot4);
			SWAP = strcat(SWAP,"\n");
		}
		v++;
	}
	fclose(memo2);
	return SWAP;
}


char * processinfo2(char* PROC){
	char PROC2[10000];
	char n[50];
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
		if(i>62&&i<65){
			sprintf(n,"%d",i);
			PROC = strcat(PROC2,n);
			PROC = strcat(PROC," >> ");
			PROC = strcat(PROC,sd ->d_name);
			PROC = strcat(PROC,"\n");
			printf("%d >> %s \n", i, sd ->d_name);
		}
		i++;
	}

	int nb = i - 62;

	printf("Tâches: %d total \n", nb);
	closedir(dir);

	printf ("L'identifiant du processus est %d\n", (int) getpid ()); //affiche le PID du programme en cours interface
	return PROC;
}
