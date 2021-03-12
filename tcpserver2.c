#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#define PORT 9002

/* OBJECTIF : au final, le client demande l'exécution
 * de notre programme
 * et le serveur doit lui retourner ses valeurs*/

int main(){
	char buff[2000] = "Bienvenue sur le serveur! \n";
	//buff[0] = "Bienvenue sur le serveur! \n";
	
	//lecture d'un fichier 
	/*
	FILE *f = fopen("sat3_aka.txt","r");
	char ligne[100];
	fgets(ligne, 100, f);
	fclose(f);
	* */
	
	//création du socket serveur
	int listen_socket;
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	
	//definition de l'adresse du serveur
	struct sockaddr_in server_address;
	//memset(server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//la fonction bind affecte une adresse locale au socket qu'on vient de créer
	int ret = bind(listen_socket,(struct sockaddr*) &server_address , sizeof(server_address));
	listen(listen_socket,2);
	
	int client_socket;
	socklen_t addrlen;
	pid_t child;
	
			
	//send the message
	send(client_socket, buff, sizeof(buff), 0);
	printf("[+] envoi message de bienvenue. \n");
	client_socket = accept(listen_socket, NULL , &addrlen);
	printf("[+] connexion acceptée avec le client.\n");
	//memset(buff, '\0', 2000);
	recv(client_socket, &buff, sizeof(buff), 0);
	
	system("./testGTK2");
	
	close(client_socket);
		
	if(client_socket <0){
		exit(1);
	}
		
		

	
	//close the socket
	close(listen_socket);
	
	return 0;
}
