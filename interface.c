//#include <dos.h>
#include "sensors.c"

int main(){
	while(1){
		printf("\n");
		printf("\t \t \tBienvenue dans RETOP \n \n");
		temps();
		//printf(",\t salut");
		printf("\n");
		uptime();
		printf("\n \n");
		memory();
		processinfo();
		sleep(3);
		//system("clear \n ./interface");
	}
   return 0;
}
