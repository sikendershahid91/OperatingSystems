// sockets are endpoints of network communication
// posix sockets api, standard for linux/unix/bsd

#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char * arbv[]){
	int socket_desc; 
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

	if(socket_desc == -1){
		printf("Could not create socket\n");
	}
	else{
		printf("Socket created\n"); 
		printf("Socket's status:[%d]\n", socket_desc); 
	}
	return 0; 
}

// created a socket and returned a descriptor 
// this can descriptor can be used in other functions
