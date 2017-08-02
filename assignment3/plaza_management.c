#include <stdio.h>
#include <pthread.h>

#define MAXCHILD 20

static int capulet_count; 
static int montague_count;
static pthread_mutex_t access = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t ok = PTHREAD_COND_INITIALIZER;  

struct person{
	char * family; 
	char * name; 
	unsigned int arrival_time; 
	unsigned int stay_time; 
};

void * capulet(void * arg){
	struct person* a_person = (struct person *) arg;
	printf("%s %s arrives at time %d\n", a_person->family, a_person->name, a_person->arrival_time); 

	pthread_mutex_lock(&access); 
	while(montague_count > 0){
		pthread_cond_wait(&ok, &access); 
	}
	capulet_count++;
	pthread_cond_signal(&ok); 
	pthread_mutex_unlock(&access);  
	printf("%s %s enters the plaza\n", a_person->family, a_person->name);
	sleep(a_person->stay_time); // why cant i use this? 
//	sleep(5); 
	printf("%s %s leaves the plaza\n", a_person->family, a_person->name);
	capulet_count--; 
// why does ok get stuck if i dont broad cast? 
	if(capulet_count == 0)
		pthread_cond_broadcast(&ok); 
	pthread_exit((void*)0); 

}

void * montague(void * arg){
	struct person* a_person = (struct person *) arg;
	printf("%s %s arrives at time %d\n", a_person->family, a_person->name, a_person->arrival_time); 

	pthread_mutex_lock(&access); 
	while(capulet_count > 0){
		pthread_cond_wait(&ok, &access); 
	}
	montague_count++; 
	pthread_cond_signal(&ok);
	pthread_mutex_unlock(&access); 
	printf("%s %s enters the plaza\n", a_person->family, a_person->name);
	sleep(a_person->stay_time);  
	printf("%s %s leaves the plaza\n", a_person->family, a_person->name);
	montague_count--;
	if(montague_count == 0)
		pthread_cond_broadcast(&ok); 
	pthread_exit((void*)0);   
}

int main(void){
	char * buffer;
	struct person log[MAXCHILD];
	int n_child= 0;   
	int n_arg = 0;  

	while(1){
		scanf("%ms", &buffer);
		if (buffer == NULL)
			break;  
		if (n_arg == 0) { log[n_child].family = buffer;};
		if (n_arg == 1) { log[n_child].name = buffer;};
		if (n_arg == 2) { log[n_child].arrival_time = atoi(buffer);};
		if (n_arg == 3) { 
			log[n_child].stay_time = atoi(buffer); 
			n_arg = -1; 
			n_child++; 
		};
		n_arg++; 	
	} 

	pthread_t tids[n_child];
	void * (*gang) (void*);
	for(int i = 0; i < n_child; i++){
		gang = (strcmp(log[i].family, "Capulet") == 0)? capulet: montague;
		pthread_create(&tids[i], NULL, gang, &log[i]);
		sleep(1);  
	} 

	for(int i = 0; i < n_child; i++){
		pthread_join(tids[i], NULL);  
	}

	return 0; 
}