#include <stdio.h>

#define MAXCHILD 20


struct Child{
	char * family; 
	char * name; 
	unsigned int arrival_time; 
	unsigned int stay_time; 
};

void create_thread(struct Child child){
	
}

int main(void){
	char * buffer;
	struct Child childs[MAXCHILD];
	int child_count= 0;   
	int arg_count = 0;  

	while(1){
		scanf("%ms", &buffer);
		if (buffer == NULL)
			break;  
		if (arg_count == 0) { childs[child_count].family = buffer;};
		if (arg_count == 1) { childs[child_count].name = buffer;};
		if (arg_count == 2) { childs[child_count].arrival_time = atoi(buffer);};
		if (arg_count == 3) { 
			childs[child_count].stay_time = atoi(buffer); 
			arg_count = -1;
			child_count++; 
		};
		arg_count++; 	
	} 

	for(int i =0 ; i < child_count; i++){
		printf("child#%d family:%s name:%s arrival_time:%d stay_time:%d \n", 
			i,
			childs[i].family, 
			childs[i].name, 
			childs[i].arrival_time, 
			childs[i].stay_time); 
	} 
	return 0; 
}