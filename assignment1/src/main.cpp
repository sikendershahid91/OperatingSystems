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
void print_report(void); 
void create_model(void); 

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

struct Input{
	Process process_container; 
	CONTAINER_STATUS status; 
}; 

struct Display{
	Process process_container; 
	CONTAINER_STATUS status; 
}; 

int main(void){
	load_data_into_memory();
	create_processes(); 
	create_model(); 


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



bool event_handler(void){



}


queue<Process> ready_queue; 
queue<Process> disk_queue; 
//no queues for input and display needed. 
//Dont have to core objects or disk objects

int free_cores; 
bool disk; 
void create_model(void){ 
	//setup core 
	//set disk 
	//set display 
	//set input

}


//helper function prototypes
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
