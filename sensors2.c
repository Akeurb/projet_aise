#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// Bah trkl mais go installer warzone par contre

float pcpu2(int PID){

	DIR *dir;
	char* tab_PID;
	char* paths;
	struct dirent *sd;
	tab_PID = calloc(100,sizeof(char));
	memset(tab_PID, 0, 100);
	int utime, stime, cutime, cstime, starttime, total_time;
	float seconds, cpu_usage;
	long int Hz;
	sprintf(tab_PID,"%d",PID);
	//printf("PID %s \n",tab_PID);
	paths = calloc(100,sizeof(char));
	memset(paths, 0, 100);
	strcat(paths, "/proc/");
	strcat(paths, tab_PID);
	strcat(paths, "/stat");
	FILE *f = fopen(paths, "r");
	//printf("PATHS %s \n",paths);

	if (getpid() == PID){
		printf("Mon PID = %d\n",PID);
	}

	else if (!f)
	{
		printf("!f \n");
	}

	else {

		for(int x=0; x<24; x++){
			char* info = calloc(100,sizeof(char));
			memset(info, 0, 100);
			fscanf(f, "%s", info);
			if (x == 13){
				utime = atoi(info);
				//printf("%d >>>>>>>>> Utime = %s \n", x, info);
				free(info);
			}

			else if (x==14){
				stime = atoi(info);
				//printf("%d >>>>>>>>> Stime = %s \n", x, info);
				free(info);
			}

			else if (x==15){
				cutime = atoi(info);
				//printf("%d >>>>>>>>> Cutime = %s \n", x, info);
				free(info);
			}

			else if (x==16){
				cstime = atoi(info);
				//printf("%d >>>>>>>>> Cstime = %s \n", x, info);
				free(info);
			}

			else if (x==23){
				starttime = atoi(info);
				//printf("%d >>>>>>>>> Starttime = %s \n", x, info);
				free(info);
				total_time = utime + stime + cutime + cstime;
				FILE *fp = fopen("/proc/uptime", "r");
				float uptime[2] = {0};
				if(fp != NULL){
					fscanf(fp, "%f %f", &uptime[0], &uptime[1]);}
				Hz = sysconf(_SC_CLK_TCK);
				seconds = uptime[0] - (starttime / Hz);
				fclose(fp);
				cpu_usage = 100 * ((total_time / Hz) / seconds);
			}
		}
		free(paths);
		free(tab_PID);
		fclose(f);
	}
	return cpu_usage;
}

float pmem2(long rss2){
	double v2 = 0;
	double pmem = 0;
	char v1[50],v3[50];

	FILE *f = fopen("/proc/meminfo", "r");
	fscanf(f,"%s %le %s",v1,&v2,v3);
	fclose(f);

	pmem = (rss2/v2)*100;
	return pmem;
}


/*
float pmem2(int PID){
	double v2 = 0;
	double pmem = 0;
	char v1[50],v3[50];

	FILE *f = fopen("/proc/meminfo", "r");
	fscanf(f,"%s %le %s",v1,&v2,v3);
	fclose(f);

	int v4;
	int i = 0;
	char v5[50],v6[50];

	char* tab_PID;
	char* paths;

	tab_PID = calloc(100,sizeof(char));
	memset(tab_PID, '\0', 100);
	sprintf(tab_PID,"%d",PID);
	//printf("PID %s \n",tab_PID);
	paths = calloc(100,sizeof(char));
	memset(paths, '\0', 100);
	strcat(paths, "/proc/");
	strcat(paths, tab_PID);
	strcat(paths, "/status");
	//printf("PATHS %s \n",paths);

	FILE *f2 = fopen(paths, "r");

	while(i < 56){
			fscanf(f2, "%s", v5);
			if( i==54){
				printf("\t V5 %-10s",v5);
				break;
			}
			i++;
	}


	free(paths);
	free(tab_PID);
	fclose(f2);


	/*
	 char c[1000];
    FILE *f2;
    if ((f2 = fopen(paths, "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    // reads text until newline is encountered
    while(i < 28){
		fscanf(f2, "%[^\n]", c);
		printf("Data from the file:\n%s", c);
			if( i==25){
				break;
			}
			i++;
	}
    fclose(f2);
    *


	return pmem;
}
*/
/*

int main(int argc, char** argv){
	int UB,UA,SB,SA = pcpu2(1);
	printf("\nUB %d \n",UB);
	printf("UA %d \n",UA);
	printf("SB %d \n",SB);
	printf("SA %d \n",SA);
	return 0;
}
*/
