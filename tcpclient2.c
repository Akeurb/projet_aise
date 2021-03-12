#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9002

int main(){
	//création de socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//choix d'une adresse manuellement
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//connexion au serveur
	int ret = connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	 
	 if(ret < -1){
		 close(sock);
		 perror("plantage lors de la connexion");
	 }
	
	//utilisation du socket
	char buffer[2000];
	recv(sock, &buffer, sizeof(buffer), 0);
	printf("[+] Réception d'un message du serveur :  %s \n", buffer);
	memset(buffer, '\0', sizeof(char));
	strcat(buffer, "./testGTK");
	send(sock, buffer, sizeof(buffer), 0);
	memset(buffer, '\0', sizeof(buffer));
	recv(sock, &buffer, sizeof(buffer), 0);
	
	//affichage du message du server
	//printf("The server sent this mesage : %s \n", buffer);
	
		
	
	close(sock);
	
	return 0;
}
