#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 30


int main(int argc, char ** argv){
	// printf("argc :%d \n", argc); 			// utilizing redirection
	// for(int i= 1; i<argc; i++){
	// 	printf("argv : %s\n", argv[i]); 
	// }
	char * text = calloc(1,1), buffer[BUFFERSIZE]; 
	while(fgets(buffer, BUFFERSIZE, stdin)){
		text = realloc(text, strlen(text) + 1 + strlen(buffer)); 
		strcat(text, buffer); 
		printf("%s", buffer); 
	}
	printf("\n"); 
	
	return 0;
}