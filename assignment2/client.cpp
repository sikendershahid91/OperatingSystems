#include <iostream> 
#include <string.h>
#include <cstdio>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


using namespace std; 

#define ERROR_MESSAGE(msg) \
	do {perror(msg); exit(1);} while(0)

int main(){
	char hostname[20]; 
	int portnum; 
	cout<< "Enter a server host name:"; 
	cin >>  hostname; 
	cout << "Enter server port number:"; 
	cin >> portnum; 
	const char* hstname = hostname; 
	cin.ignore(); 
	
	int sockfd; 
	struct sockaddr_in serv_addr; 
	struct hostent * server; 

	char buffer[512]; 
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ERROR_MESSAGE("socket error"); 

    if ((server= gethostbyname(hstname)) == NULL)
        ERROR_MESSAGE("ERROR no such host");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portnum);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        ERROR_MESSAGE("ERROR connecting");
    
    int price; 
    while(1){
	    bzero(buffer,512);

	    cout << "Enter a Houston neighborhood:";
	    cin.getline(buffer, 512);  
	    if(strlen(buffer) == 0){
	    	break;
	    }
	    if(write(sockfd,buffer,strlen(buffer)) < 0)
	    	ERROR_MESSAGE("ERROR writing to socket");
	    if(read(sockfd,&price,32) < 0)
	    	ERROR_MESSAGE("ERROR reading from socket");
	    if(price == -1)
	    	cout << "The neighborhood is not in the table\n"; 
	    else 
	   		cout << "this is the price " <<price << endl; 
	}
	cout << "PROGRAM ENDED" << endl; 

    return 0;
}