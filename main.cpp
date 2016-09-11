#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#include <cctype>

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


//create convenience function for adding in spaces
void printLines(const int n){
	for(int x=0; x<n; ++x) cout << endl;
}

//create reference function for empty vector exception handler
//actually, this simply print runtime error message, hence, this should be more generic named..
//so call this runtimeErrorHandler 
void runtimeErrorHandler(runtime_error &error){
	cerr << error.what() << endl << endl; 
}

//input checking for commands, must be an integer 
//not used, since version 2 is much better
int getCommand(const int limit){
	int tmp_getcmd;
	cout << "Enter command =>  ";
	cin >> tmp_getcmd;
	while(cin.fail() || tmp_getcmd > limit){
		cout << endl;
		cin.clear();	//clear cin error
		cin.ignore(1000,'\n');	//ignore the next set of characters, good for blocking string with spaces
		cout <<  "invalid input bruv!! Enter correct command =>>  ";
		cin >> tmp_getcmd;
	}	
	return tmp_getcmd;
}	

//get  command input from user, complete with error checks to ensure proper command
int getCommand2(int cmd_limit){
	string cmd_temp;
	int cmd;
	cout << "Enter command =>  ";
	//cin.ignore(); 
	getline(cin,cmd_temp);
	
	int flag=1;
	while(flag==1){
		flag=0;
		
		for(int x=0; x<cmd_temp.size(); ++x)
		{
			if(!isdigit(cmd_temp[x])){ flag=1;	//detect if content of string is purely digits
				cout <<  "invalid input bruv!! Enter correct command =>>  ";
				//cin.ignore(); 
				getline(cin,cmd_temp);
				break;
			}
		}
		
		cmd = atoi(cmd_temp.c_str());	//detect if the digit is a valid number
		if(cmd > cmd_limit){
			flag=1;
			cout <<  "invalid input bruv!! Enter correct command =>>  ";
			//cin.ignore(); 
			getline(cin,cmd_temp);
		}
	}
	
	return cmd;
}


void getDate(string &date){
	int flag=1;
	//cin.ignore();
	getline(cin,date);
	//cout << date.size() << endl;
	
	while(flag==1){
		flag=0;
		
		if( (date.size()<8)||(date.size()>10) ) flag=1; //detect length of entry
		else{
		
			for(int x=0; x<date.size(); ++x)
				if( (!isdigit(date[x])) && !(date[x]=='/') ) {   //detect if content of string is purely digits or /
					flag=1;	
					break;
				}
		}
		
		if(flag==1){
			cout <<  "invalid input bruv!! Enter correct command =>>  ";
			//cin.ignore(); 
			getline(cin,date);
		}
	}
	
			
}


int main(void){
	
	
//////////////////////
///in this UI, all entries are loaded and stored from a single csv file, source-file.csv
/////////////////////	

//string temp = "hello kitty";
//cout << temp.size() << endl;

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
	cout << "<1>: View all expense entries in the database" << endl;
	cout << "<2>: View current list of expense" << endl;
	cout << "<3>: Add an entry" << endl;
	cout << "<4>: Drop the last entry" << endl;
	
	
	//command = getCommand(4);
	//cin >> command;
	
	command = getCommand2(4);
	// if(cin.fail())
	// {		
		// cin.clear();
		// cin.ignore(1000,'\n');
		// command = 5;
	// }
	
	
	switch(command){
		case 0:
			Ev1.exportVctr();
			break;
			
		case 1:
			printLines(4);
			mode = 3;
			cout << "*****************************" << endl;
			cout << "***now printing all entries**" << endl;
			cout << "*****************************" << endl;
			printLines(2);
			cout << "date \t wkday \t time \t description \t price\n";
			cout << "----------------------------------------------\n";
			printLines(2);
			
			//detect if vector is empty
			try{ Ev1.printVctrRange("01/01/0001","01/01/2300",mode); }
			catch (runtime_error &error) { runtimeErrorHandler(error); }
				
			break;
			
		case 2:
			printLines(4);
			cout << "enter date in this format => mm/dd/yyy" << endl;
			cout << "enter the start date here in =>"; 
			getDate(start_date);
			cout << "enter the end date here in =>"; 
			getDate(end_date);
			printLines(2);
			
			cout << "Press the number enclosed by <> to choose your command" << endl;			
			cout << "<0>: Summarize expense per day" << endl;
			cout << "<1>: Summarize expense per month" << endl;
			cout << "<2>: Summarize expense per year" << endl;
			cout << "<3>: Summarize expense per entry" << endl;
			
			//cin.ignore();
			mode = getCommand2(3);
			
			
			printLines(4);
			cout << "*****************************" << endl;
			cout << "***now printing entries******" << endl;
			cout << "***" << start_date << " to " << end_date << "***" << endl;
			cout << "*****************************" << endl;
			printLines(2);
			
			switch(mode){
				case 0: cout << "date \t price\n"; break;
				case 1: cout << "month \t price\n"; break;
				case 2: cout << "year \t price\n"; break;
				default: cout << "date \t wkday \t time \t description \t price\n"; break;
			}
			
			cout << "----------------------------------------------\n";
			printLines(2);
			
			//detect if vector is empty
			try{ Ev1.printVctrRange(start_date,end_date,mode); }
			catch (runtime_error &error) { runtimeErrorHandler(error); }
			
			//cin.ignore();
			break;
			
		case 3:
			int buffer_temp;
			cout << endl << endl << endl;
			cout << "enter the data for your new expense" << endl;
			cout << "please enter the currency =>"; cin >> currency; cout << endl;
			cout << "please enter the value of the expense =>"; cin >> value; cout << endl;
			cout << "please enter the description of the expense =>"; 
			cin.ignore(); getline(cin,description); cout << endl; 
			//get line needed as cin will stop buffering on a space
			//cin.ignore needed, as the enter key from previous cin will be stored in the cin buffer
			
			//cout << currency << value << description;
			Ev1.addEntry(currency,value,description); 
			cout << "***Expense is added to the database!***";
			printLines(4);
			break;
		
		case 4:
			cout << "now deleting the last entry" << endl << endl;
			try{ Ev1.dropEntry(); }
			catch (runtime_error &error) { runtimeErrorHandler(error); }
			printLines(2);
			break;
			
		default:
			printLines(4);
			cout << "***invalid command***\n";
			printLines(2);
			break; 
	}
	
	if(command==0){
		Ev1.exportVctr();
		break;
	}
}	

	return 0;	
}
