#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	DIR *dir;
	struct dirent *sd;
	int x = 0; //compteur nombre d'éléments fscanf

	dir = opendir("/proc");


	if (dir == NULL){
		printf("Error! Unable to open directory. \n");
		exit(1);
	}
	sd = readdir(dir);
	sd = readdir(dir);
	while (( sd != NULL)){
		printf("ouais\n");
		sd = readdir(dir);
		printf("ouais 2\n ");
		printf("%s\n",sd->d_name);
		if (atoi(sd->d_name)==0){
			printf("Pas un PID \n");
		}

		else if (getpid() == atoi(sd->d_name)){
			printf("Mon PID = %d\n",atoi(sd->d_name));
			break;
		}
		else{
			printf("ouais\n");
			char* paths = malloc(100*sizeof(char));
			strcat(paths, "/proc/");
			strcat(paths, sd->d_name);
			strcat(paths, "/stat");
			FILE *f = fopen(paths, "r");
			free(paths);

			if (!f)
			{
				printf("!f \n");
			}

			else{
			for(x=0;x<15;x++){
				char* info = malloc(100*sizeof(char));
				fscanf(f, "%s", info);
				if (x==13 || x==14){
				printf("%d >>>>>>>>> %s \n", x, info);
				printf("NOM FICHIER %s\n",sd->d_name);
				}
				free(info);
			}
		}
			fclose(f);
			printf("PID %s\n",sd->d_name);
		}
	}
	return 0;
}
/* creer une fonction qui fait ce qu'on vient de faire mais pour
un argument PID qui provient de test2.c (proc_info.tid)) et return le %cpu*/
