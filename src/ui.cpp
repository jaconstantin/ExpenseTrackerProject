//---------------------------------------------------------------------
//----ui.cpp
//----Author: Jconstan
//-----contains the ui class for the userinterface
//----------------------------------------------------------------------


#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>


//note here, to avoid the conflict in compiling when including the same header file
#ifndef __MAIN_CLASSES
#include "main_classes_v2.h"
#define __MAIN_CLASSES 
#endif

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

#include "ui.h"

//want to create the UI as a class
//for now put all declarations in here

using namespace std;



//default constructor, initialize by loading source file to database
UI::UI(){
	expDatabase.loadVctr("source-file.csv");
	userCmd=0;
}


void UI::printLines(const int n){
	for(int x=0; x<n; ++x) cout << endl;
}


//print errors for runtime exceptions
void UI::handleRunTimeError(runtime_error &error){
	cerr << error.what() << endl << endl; 
}


//check format and white spaces of characters in user input, depends on input type: cmd,date,currency,price
//returns true if an error is found
bool UI::checkCharInput(const char &in, const usrInput_t &inType){
	switch(inType){
		case date:	return ( (!isdigit(in)) && !(in=='/') );
		case currency: return (!isalpha(in));						
		case price: return ( (!isdigit(in)) && !(in=='.') );
		default: return (!isdigit(in));						
	}
}


//get user input with error checks dependent on input type: cmd,date,currency,price
string UI::getUsrInput(usrInput_t inType, const int cmdLimit){
	string tmpUsrIn;
	int errFlag=1;
	int tmpInt;
 
	getline(cin,tmpUsrIn);                                                  //get line needed as cin will stop buffering on a space
	
	while(errFlag==1){
		errFlag=0;
		for(int x=0; x<tmpUsrIn.size(); ++x)	                            //check if all characters are valid, including white spaces
			if(checkCharInput(tmpUsrIn[x],inType)){
				errFlag=1;
				break;
			}
		
		switch(inType){						
			case date: 
				if( (tmpUsrIn.size()<8)||(tmpUsrIn.size()>10) ) errFlag=1;	//check the length of date string in mm/dd/yyyy format
				break;
			case currency:
				break;
			case price:
				 break;
			default:				
				tmpInt = atoi(tmpUsrIn.c_str());		                    //check if numerical command is within valid range
				if(tmpInt > cmdLimit) errFlag=1;
				break;
		}
		
		
		if(errFlag==1){													    //if invalid input, ask for new input and loop again
			cout <<  "invalid input bruv!! Enter correct command =>>  "; 
			getline(cin,tmpUsrIn);
		}
		
	}
	
	return tmpUsrIn;
	
}


int UI::launchUI(){
	
	string tmpStartDate, tmpEndDate, tmpUsrIn;
	dateMode_t tmpDateMode;

	string tmpCurrency, tmpDescription;
	float tmpValue;
	
	cout << "**************************" << endl;
	cout << "**Welcome to my program***" << endl;
	cout << "by JC, 8/18/2016" << endl;
	cout << "program is initialized!" << endl;
	cout << "***************************" << endl;
	cout << endl << endl << endl;
	
	
	int infLoop=0;
	//enter the main UI loop, make this an infinite loop
	
	while(infLoop==0){
		
		cout << "Press the number enclosed by <> to choose your command" << endl;
		cout << "<0>: Exit the program" << endl;
		cout << "<1>: View all expense entries in the database" << endl;
		cout << "<2>: View current list of expense" << endl;
		cout << "<3>: Add an entry" << endl;
		cout << "<4>: Drop the last entry" << endl;
		
		tmpUsrIn = getUsrInput();					 //get user input cmd as string, check format, then convert to int
		userCmd = atoi(tmpUsrIn.c_str()); 
		
		//const char* fName = "source-file.csv";
		
		switch(userCmd){
			
			case 0:   //exit program
				expDatabase.exportVctr("source-file.csv");
				break;
			
			
			case 1:	  //view all entries in database
				printLines(4);
				tmpDateMode = perEntry;
				cout << "*****************************" << endl;
				cout << "***now printing all entries**" << endl;
				cout << "*****************************" << endl;
				printLines(2);
					
				cout << setfill(' ') << setw(7) << "date"
				     << setfill(' ') << setw(13) << "wkday" 
				     << setfill(' ') << setw(9) << "time" 
					 << setfill(' ') << setw(15) << "price"
					 << setfill(' ') << setw(30) << "description\n"; 	
				cout << setfill('-') << setw(120) << "----------------------------------------------\n";
				printLines(2);
				
				//detect if vector is empty before print all
				try{ expDatabase.printVctrRange("01/01/0001","01/01/2300",tmpDateMode); }
				catch (runtime_error &error) { handleRunTimeError(error); }
					
				break;
			
			
			case 2:   //view current list of expense
				printLines(4);
				cout << "enter date in this format => mm/dd/yyyy" << endl;
				cout << "enter the start date here in =>"; 
				tmpStartDate = getUsrInput(date,0);
				cout << "enter the end date here in =>"; 
				tmpEndDate = getUsrInput(date,0);
				printLines(2);
				
				cout << "Press the number enclosed by <> to choose your command" << endl;			
				cout << "<0>: Summarize expense per day" << endl;
				cout << "<1>: Summarize expense per month" << endl;
				cout << "<2>: Summarize expense per year" << endl;
				cout << "<3>: Summarize expense per entry" << endl;
				
				tmpUsrIn = getUsrInput(cmd,3);									  //get user input cmd as string, check format,
				tmpDateMode = static_cast<dateMode_t>(atoi(tmpUsrIn.c_str()));    //then convert to dateMode_t
				
				printLines(4);
				cout << "*****************************" << endl;
				cout << "***now printing entries******" << endl;
				cout << "***" << tmpStartDate << " to " << tmpEndDate << "***" << endl;
				cout << "*****************************" << endl;
				printLines(2);
				
				switch(tmpDateMode){
					case perDay: 
						cout << "    date" << setfill(' ') << setw(37) << "price\n" ;
						break;
					case perMonth: 
						cout << "    month" << setfill(' ') << setw(37) << "price\n" ;
						break;
					case perYear: 
						cout << "    year" << setfill(' ') << setw(37) << "price\n" ;
						break;
					default: 
						cout << setfill(' ') << setw(7) << "date"
							<< setfill(' ') << setw(13) << "wkday" 
							<< setfill(' ') << setw(9) << "time" 
							<< setfill(' ') << setw(15) << "price"
							<< setfill(' ') << setw(30) << "description\n"; 	
						break;
				}
				
				cout << setfill('-') << setw(120) << "----------------------------------------------\n";
				printLines(2);
				
				//detect if vector is empty, then print data per dateMode_t(day,month,year,entry) within date range
				try{ expDatabase.printVctrRange(tmpStartDate,tmpEndDate,tmpDateMode); }
				catch (runtime_error &error) { handleRunTimeError(error); }
				
				//cin.ignore();
				break;
			
			
			case 3:   //add entry
				cout << endl << endl << endl;
				cout << "enter the data for your new expense" << endl;
				
				cout << "please enter the currency =>";                      //getCurrency(currency);
				tmpCurrency = getUsrInput(currency,0);
				
				cout << "please enter the value of the expense =>";          //getValue(value); 
				tmpUsrIn = getUsrInput(price,0);
				tmpValue = atof(tmpUsrIn.c_str());
								
				cout << "please enter the description of the expense =>"; 
				getline(cin,tmpDescription); cout << endl;                   //get line needed as cin will stop buffering on a space
				                                                             //cin.ignore might needed, as the enter key from previous cin can be stored in the cin buffer
				
				expDatabase.addEntry(tmpCurrency,tmpValue,tmpDescription); 
				cout << "***Expense is added to the database!***";
				printLines(4);
				break;
			
			
			case 4:  //drop entry
				cout << "now deleting the last entry" << endl << endl;
				try{ expDatabase.dropEntry(); }
				catch (runtime_error &error) { handleRunTimeError(error); }
				printLines(2);
				break;
				
			
			default:
			printLines(4);
			cout << "***invalid command***\n";
			printLines(2);
			break; 
		}
		
			
		
		if(userCmd==0){
			//expDatabase.exportVctr();
			break;
		}
		
	}
	
	return 0;
	
}

//commit 2 for master future branch