#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// bien bien et toi frérot ?

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
		fclose(f);
	}
	return cpu_usage;
}
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
