#include <iostream>
#include <queue>
#include <string.h>
#include <vector> 
#include <deque>


using namespace std; 

// helper functions
void load_data_into_memory(void);
bool create_processes(void); 
void sort_event_list(void); 


bool event_handler(); 

enum STATE{
	RUNNING, 
	READY, 
	BLOCKED, 
}; 
enum TASK{
	CORE, 
	DISK, 
	DISPLAY, 
	INPUT,
};

struct ProcessTask{
	TASK _task;
	int _time; 
	ProcessTask(TASK atask, int atime){
		_task = atask; 
		_time = atime; 
	}
}; 

struct Process{
	STATE _state;
	int _process_id;  
	int _init_time;
	int first_line; 
	int last_line; 
	int current_line; 
	Process(int a_process_id, int a_init_time){
		_process_id = a_process_id; 
		_init_time = a_init_time; 
		_state = BLOCKED; 
	}       
	queue<ProcessTask> task_queue;
};


int main(void){
	load_data_into_memory(); 


	return 0; 
}



struct Data{
	string operation; 
	int parameter; 
};
vector<Data> input_table(2);
int input_table_size=0; 
void load_data_into_memory(void){
	while(cin >> input_table[input_table_size].operation && cin >> input_table[input_table_size].parameter){
		input_table_size++; 
		input_table.resize(2+input_table_size); 
	}
	cout << input_table_size << endl; 
}



deque<Process> event_list; 
bool create_processes(void){
	int index = 1; 
	Process process(0,0);
	TASK task = CORE; 
	while(index < input_table_size){
		if(input_table[index].operation == "NEW"){
			if(index>1){ // adding finished processes to the event_list
				event_list.push_back(process); 
			}
			Process new_process(index, input_table[index].parameter);   
			process = new_process; 
			index++;
		}
		if(input_table[index].operation == "CORE")
			task = CORE;
		else if(input_table[index].operation == "DISK")
			task = DISK;
		else if(input_table[index].operation == "DISPLAY")
			task = DISPLAY;
		else if(input_table[index].operation == "INPUT")
			task = INPUT;
		else
			return 0;
		ProcessTask process_task(task, input_table[index].parameter); 
		process.task_queue.push(process_task); 
		index++;  
	}
	return 1; 
}

void sort_event_list(void){
	
}

void create_model(void){ 
	//setup core 
	//set disk 
	//set display 
	//set input
}