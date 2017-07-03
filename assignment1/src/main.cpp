// SIKENDER SHAHID
// PSID 0981476
// COSC 3360
// 6/30/2017

#include <iostream>
#include <queue>
#include <string.h>
#include <vector> 
#include <deque>
#include <stdlib.h>

using namespace std; 

#define MAX_CORE_SIZE 10
#define BLOCKING 1
#define NONBLOCKING 0


struct Process; 
struct ProcessTask;
// event handler routines
void core_request(Process& a_process, int param); 
void core_request_completion(Process& a_process); 
void disk_request(Process& a_process, int param); 
void disk_request_completion(Process& a_process); 
void display_request(Process& a_process, int param); 
void display_request_completion(Process& a_process); 
void input_request(Process& a_process, int param); 
void input_request_completion(Process& a_process); 

// helper routines
void load_data_into_memory(void);
bool create_processes(void); 
void sort_event_list(void); 
bool event_handler(Process& a_process); 
void print_report(void); 
bool create_model(void); 


int CLOCK; 

enum STATE{
	RUNNING, 
	READY, 
	BLOCKED,
	TERMINATED,
}; 

enum TASK{
	CORE, 
	DISK, 
	DISPLAY, 
	INPUT,
};

enum CONTAINER_STATUS{
	FREE, 
	BUSY,
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
	int delay;  
	Process(int a_process_id, int a_init_time){
		_process_id = a_process_id; 
		_init_time = a_init_time; 
		_state = BLOCKED;
		delay = 0;
		// first line, last line, current line not really actually 
		// this will go into process table 
	}   
	Process(){
		_process_id = -1;
		_init_time = -1;
		_state = BLOCKED; 
		delay = 0; 
	}    
	queue<ProcessTask> task_queue;
};

struct Core{
	Process process_container;
	CONTAINER_STATUS status;
}; 

struct Disk{
	Process process_container;
	CONTAINER_STATUS status;
};

// struct Input{
// 	Process process_container; 
// 	CONTAINER_STATUS status; 
// }; 

// struct Display{
// 	Process process_container; 
// 	CONTAINER_STATUS status; 
// }; 
queue<Process> event_list; 
int main(void){
	load_data_into_memory();
	create_processes(); 
	create_model();
	while(!event_list.empty()){
		event_handler(event_list.front()); 
		event_list.pop(); 
	}
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
	TASK task = CORE; 
	while(index < input_table_size){
		if(input_table[index].operation == "NEW"){
			if(index>1){ // adding finished processes to the event_list
				event_list.push(process); 
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

// void sort_event_list(void){

// }

bool event_handler(Process& a_process){
	TASK a_process_task = a_process.task_queue.front()._task;
	int a_param = a_process.task_queue.front()._time; 
	if(a_process_task == CORE)
		core_request(a_process, a_param); 
	else if(a_process_task == DISK)
		disk_request(a_process, a_param); 
	else if(a_process_task == INPUT)
		input_request(a_process, a_param); 
	else if(a_process_task == DISPLAY)
		display_request(a_process, a_param); 
	else
		a_process._state = TERMINATED; 
	if(a_process._state = TERMINATED){
		print_report();
		return 0; 
	}
	return 1; 
}

queue<Process> ready_queue; 
queue<Process> disk_queue; 
int free_cores; 
Disk disk;
Core cores[MAX_CORE_SIZE];
int cores_size = 0; 
bool create_model(void){ 
	if(input_table[0].operation == "NCORES")
		cores_size = input_table[0].parameter;
	else
		return 0;
	if(cores_size > MAX_CORE_SIZE)
		return 0; 
	free_cores = cores_size;
	disk.status = FREE; 
	for(int i = 0; i < cores_size ; i++){
		cores[i].status = FREE; 
	}
	return 1; 
}


// print report helper function prototypes
void queue_traverse(queue<Process> a_queue); 
int busy_core(); 
void print_report(void){
	cout << "TIME ELAPSED:         " << CLOCK << endl;
	cout << "NUMBER OF BUSY CORE:  " << busy_core() << endl;
	cout << "CURRENT PROCESS STATUS" << 0 << endl;
	// for loop
	cout << "   CORE STEP:         " << 0 << endl;
	// pull from core container
	cout << "   DISK STEP:         " << 0 << endl;
	// pull from disk container
	cout << "   INPUT STEP:        " << 0 << endl;
	// pull from input container
	cout << "   DISPLAY STEP:      " << 0 << endl;
	// pull from display container
	cout << "READY QUEUE:\n";
	queue_traverse(ready_queue); 
	cout << "DISK QUEUE:\n";
	queue_traverse(disk_queue); 
	cout << "PROCESS TABLE:        " << 0 << endl;
	cout << "   Process:[" << 0 << "] Start Time:[" << 0 << "] Disk I/O:["<< 0 <<"] Status:[" << 0 << "]\n";
}

// print report helper function
int busy_core(){
	return 0; 
}

void queue_traverse(queue<Process> a_queue){
	queue<Process> temp_queue = a_queue; 
	while(!temp_queue.empty()){
		cout << "	Process:[" << temp_queue.front()._process_id <<"]\n"; 
		temp_queue.pop();
	}
}

// event handler helper function
void core_request(Process& a_process, int request_time){
	if(free_cores > 0){
		int i = 0; 
		while(cores[i].status != FREE && i < cores_size){
			i++; 
		}
		a_process._state = RUNNING; 
		cores[i].process_container = a_process; 
		cores[i].status = BUSY; 
		free_cores--;
		CLOCK = CLOCK + request_time; 
	}
	else{
		a_process._state = READY; 
		ready_queue.push(a_process); 
	}
	core_request_completion(a_process); 
}

void core_request_completion(Process& a_process){
	if(ready_queue.empty()){
		free_cores++; 
		int i = 0; 
		while(cores[i].status == BUSY && i < cores_size){
			cores[i].status = FREE; 
			break; 
		}
	}
	else{
		core_request(ready_queue.front(), ready_queue.front().task_queue.front()._time); 
		ready_queue.pop(); 
	}
	a_process.task_queue.pop(); 
	event_handler(a_process); 
}

void disk_request(Process& a_process, int request_type){
	// 0 - request_type is nonblocking
	// 1 - request_type is blocking
	if(request_type == BLOCKING)
		a_process._state = BLOCKED;
	else{
		a_process._state = READY;
		ready_queue.push(a_process);  
	}
	if(disk.status == FREE){
		disk.process_container = a_process; 
		disk.status = BUSY; 
		CLOCK = CLOCK + 10; 
	}
	else
		disk_queue.push(a_process);
	disk_request_completion(a_process); 
}

void disk_request_completion(Process& a_process){
	if(disk_queue.empty()){
		disk.status = FREE; 
	}
	else{
		disk_request(disk_queue.front(), disk_queue.front().task_queue.front()._time); 
		disk_queue.pop(); 
	}
	a_process.task_queue.pop(); 
	event_handler(a_process); 
}

void display_request(Process& a_process, int terminal_time){
	a_process._state = BLOCKED; 
	CLOCK = CLOCK + terminal_time; 
	display_request_completion(a_process); 
}

void display_request_completion(Process& a_process){
	a_process.task_queue.pop(); 
	event_handler(a_process); 
}

void input_request(Process& a_process, int terminal_time){ 
	a_process._state = BLOCKED; 
	CLOCK = CLOCK + terminal_time;
	input_request_completion(a_process); 
}

void input_request_completion(Process& a_process){
	a_process.task_queue.pop(); 
	event_handler(a_process); 
}
