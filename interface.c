//#include <dos.h>
#include "sensors.c"
#include "sensors2.c"

int main(){
	while(1){
		printf("\n");
		printf("\t \t \tBienvenue dans RETOP \n \n");
		date2();
		//printf(",\t salut");:
		printf("\n");
		uptime();
		printf("\n \n");
		memory();
		//swap2();
		processinfo();
		sleep(3);
		//system("clear \n ./interface");
	}
   return 0;
}
