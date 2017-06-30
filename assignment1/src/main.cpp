#include <iostream>
#include <queue>
#include <string.h>
#include <vector> 
#include <deque>


using namespace std; 

// helper functions
void load_data_into_memory(void);
bool create_processes(void); 


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
	//contents of process
	STATE _state;
	int _process_id;  
	int _init_time;
	//a processes queue
	Process(int a_process_id, int a_init_time){
		_process_id = a_process_id; 
		_init_time = a_init_time; 
		_state = BLOCKED; 
	}
	queue<ProcessTask> task_queue;
};

queue<Process> event_list; 
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



bool create_processes(void){
	int index = 1; 
	Process process(0,0);
	ProcessTask task(DISK,0); 
	while(index < input_table_size){
		if(input_table[index].operation == "NEW"){
			if(index>1){ // adding finished processes to the event_list
				event_list.push(process); 
			}
			Process new_process(index, input_table[index].parameter);   
			process = new_process; 
			index++;
		}
		if(input_table[index].operation == "CORE"){
			ProcessTask new_task(CORE, input_table[index].parameter);
			task = new_task; 
		}
		else if(input_table[index].operation == "DISK"){
			ProcessTask new_task(DISK, input_table[index].parameter);
			task = new_task;
		}
		else if(input_table[index].operation == "DISPLAY"){
			ProcessTask new_task(DISPLAY, input_table[index].parameter);
			task = new_task;
		}
		else if(input_table[index].operation == "INPUT"){
			ProcessTask new_task(INPUT, input_table[index].parameter);
			task = new_task;
		}
		else
			return 0;
		process.task_queue.push(task); 
		index++;  
	}
	return 1; 
}