#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

//note here, to avoid the conflict in compiling when including the same header file

#ifndef __MAIN_CLASSES
#include "main_classes.h"
#define __MAIN_CLASSES 
#endif

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif


//define here a variable for test diagnositc messages


using namespace std;

char extern g_time_buf[30];
time_t extern g_t;
struct tm extern *g_now;


int main(void){
	
//////////////////////
///in this UI, all entries are loaded and stored from a single csv file, source-file.csv
/////////////////////	


ExpVector Ev1;
Ev1.loadVctr();

string start_date, end_date;
int mode;

string currency, description;
float value;


cout << "**************************" << endl;
cout << "**Welcome to my program***" << endl;
cout << "by JC, 8/18/2016" << endl;
cout << "program is initialized!" << endl;
cout << "***************************" << endl;
cout << endl << endl << endl;

int inf_loop=0, command=0, subcommand=0;
//enter the main UI loop, make this an infinite loop
while(inf_loop==0){
	
	cout << "Press the number enclosed by <> to choose your command" << endl;
	cout << "<0>: Exit the program" << endl;
	cout << "<1>: View current list of expense" << endl;
	cout << "<2>: Add an entry" << endl;
	
	cin >> command;
	
	if(command==1){
		
		cout << endl << endl << endl;
		cout << "enter the start date here =>"; cin >> start_date; cout << endl;
		cout << "enter the end date here =>"; cin >> end_date; cout << endl << endl;
		
		cout << "Press the number enclosed by <> to choose your command" << endl;
		cout << "<0>: Summarize expense per day" << endl;
		cout << "<1>: Summarize expense per month" << endl;
		cout << "<2>: Summarize expense per year" << endl;
		cout << "<3>: Summarize expense per entry" << endl;
		cin >> mode;
		Ev1.printVctrRange(start_date,end_date,mode);
	}
	
	else if(command==2){
		
		int buffer_temp;
		cout << endl << endl << endl;
		cout << "enter the data for your new expense" << endl;
		cout << "please enter the currency =>"; cin >> currency; cout << endl;
		cout << "please enter the value of the expense =>"; cin >> value; cout << endl;
		cout << "please enter the description of the expense =>"; 
		cin.ignore(); getline(cin,description); cout << endl;   
		//get line needed as cin will stop buffering on a space
		//cin.ignore needed, as the enter key from previous cin will be stored in the cin buffer
		
		cout << currency << value << description;
		Ev1.addEntry(currency,value,description); 	
		
	}
	
	else{
		Ev1.exportVctr();
		break; 
	}
}	

	return 0;	
}
