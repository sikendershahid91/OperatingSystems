#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <netinet/in.h>
#include <unistd.h>

using namespace std; 

#define ERROR_MESSAGE(msg) \
	do {perror(msg); exit(1);} while(0)

#define MESSAGE_SIZE 256

struct Data{
	string location; 
	int price; 
};

vector<Data> database(2); 
int database_size = 0;
void add_2_database(string _location, int _price){
	database[database_size].location = _location; 
	database[database_size].price = _price;
	database_size++; 
	database.resize(1+database_size);
}


void load_data_into_memory(string& filename){
	string line;
	string neighborhood;
	int fs_index[] = {0,0,0,0};
	int fs_count = 0;
	int c_position = 0;   
	int price;  
	ifstream file(filename.c_str()); 
	while(getline(file, line)){
		fs_count = 0; 
		c_position = 0; 
		for(unsigned int i = 0; i < line.length();i++){
			if(line[i] == '/'){
				fs_index[fs_count+1] = i;
				fs_count++; 
			}

			if(line[i] == ','){
				c_position = i;
				fs_index[2] = c_position-2; 
			}
		} 
		price = std::stoi( line.substr(c_position+2, line.length()) );
		if( fs_count > 0){
			for(int j = 0, k= 0; j <= fs_count ; j++){
				k = (j == 1)? 2: 0;
				neighborhood = line.substr(fs_index[j] + k, fs_index[j+1] - fs_index[j]);
				add_2_database(neighborhood, price); 
			}

		}else{
			neighborhood = line.substr(0, c_position);
			add_2_database(neighborhood, price);  
		} 
	}
	file.close(); 
}

void print_database(void){
	for(int i  = 0; i < database_size; i++)
		cout << database[i].location << ": " << database[i].price << endl; 
}

void server(int ); 
void run_server(){
	int portnum; 
	cout << "Enter server port number:"; 
	cin  >> portnum; 
	if(portnum < 2000 || portnum> 60000)
		ERROR_MESSAGE("INACCURATE PORT VALUE");
	server(portnum);
}

void response(char *, int &); 
void server(int portnum){
	int sockfd, newsockfd, cli_addr_length;
	char buffer[512]; 
	struct sockaddr_in serv_addr, cli_addr; 

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			ERROR_MESSAGE("SOCKET ERROR"); 
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_addr.s_addr = INADDR_ANY;  // ?
	serv_addr.sin_port = htons(portnum);
	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) <0)
			ERROR_MESSAGE("ERROR binding");
	
	while(1){
		listen(sockfd, 5); 
		cli_addr_length = sizeof(cli_addr); 
		if((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &cli_addr_length)) < 0)
			ERROR_MESSAGE("ERROR accepting");
		int value; 
	
		bzero(buffer, 512);
		if(read(newsockfd, buffer, 512) < 0 )
			ERROR_MESSAGE("ERROR reading from socket");
		else
			cout << "message received\n";
		response(buffer, value);
		if(write(newsockfd, &value, 32)<0) 
			ERROR_MESSAGE("Error writing to socket");
		else
			cout << "response sent\n";

		close(newsockfd); 
	}
}

void response(char * buffer, int &value){
	cout << buffer <<endl; 
	for(int i = 0; i <= database_size ; i++){
		if(database[i].location == buffer){
			value = database[i].price; 
			break;
		}
		if(i == database_size)
			value = -1; 
	}
	 
}

int main(void){
	string filename = " "; 
	cout <<"ENTER FILE NAME\n";
	cin >> filename; 
	load_data_into_memory(filename); 
	run_server(); 

	return 0; 
}