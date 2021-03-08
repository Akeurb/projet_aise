#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// Wesh bien ou quoi aka sa dit quoi?

int pcpu2(int PID){

	DIR *dir;
	char* tab_PID;
	char* paths;
	struct dirent *sd;
	tab_PID = calloc(100,sizeof(char));
	memset(tab_PID, 0, 100);
	int utime_after, utime_before, stime_after, stime_before, time_totel_after, time_total_before;

	sprintf(tab_PID,"%d",PID);
	//printf("PID %s \n",tab_PID);
	paths = calloc(100,sizeof(char));
	memset(paths, 0, 100);
	//paths = "";
	printf("ICIIIIIIIIIIIIIII %s \n",paths);
	strcat(paths, "/proc/");
	strcat(paths, tab_PID);
	strcat(paths, "/stat");
	FILE *f = fopen(paths, "r");
	printf("PATHS %s \n",paths);

	if (getpid() == PID){
		printf("Mon PID = %d\n",PID);
	}

	else if (!f)
	{
		printf("!f \n");
	}

	else {
		for(int x=0; x<15; x++){
			char* info = calloc(100,sizeof(char));
			memset(info, 0, 100);
			fscanf(f, "%s", info);
			if (x == 13){
				utime_before = atoi(info);
				printf("%d >>>>>>>>> Utime_Before = %s \n", x, info);
				free(info);

				usleep(100000);

				FILE *f2 = fopen(paths, "r");
				if (!f2)
				{
					printf("!f2 \n");
				}
				for (int x2=0; x2<14; x2++){
					char* info2 = calloc(100,sizeof(char));
					memset(info2, 0, 100);
					fscanf(f2, "%s", info2);
					if (x2 == 13){
						fscanf(f2, "%s", info2);
						utime_after = atoi(info2);
						printf("%d >>>>>>>>> Utime_After = %s \n\n", x2, info2);
						free(info2);
						fclose(f2);
					}
					else{;}
				}
			}

			if (x==14){
				stime_before = atoi(info);
				printf("%d >>>>>>>>> Stime_Before = %s \n", x, info);
				free(info);

				usleep(100000);

				FILE *f3 = fopen(paths, "r");
				if (!f3)
				{
					printf("!f3 \n");
				}
				for (int x3=0; x3<15; x3++){
					char* info3 = calloc(100,sizeof(char));
					memset(info3, 0, 100);
					fscanf(f3, "%s", info3);
					if (x3 == 14){
						fscanf(f3, "%s", info3);
						stime_after = atoi(info3);
						printf("%d >>>>>>>>> Stime_After = %s \n", x3, info3);
						free(info3);
						fclose(f3);
					}
					else{;}
				}
			}
		}
		free(paths);
		fclose(f);
	}
	return utime_before, utime_after, stime_before, stime_after;
}
/*
int main(int argc, char** argv){
	int UB,UA,SB,SA = pcpu2(getpid());
	printf("\nUB %d \n",UB);
	printf("UA %d \n",UA);
	printf("SB %d \n",SB);
	printf("SA %d \n",SA);
	return 0;
}
*/
/*
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

		if(i == 6){
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
*/
