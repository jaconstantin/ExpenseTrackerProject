//---------------------------------------------------------------------
//----main_classes.h
//----Author: Jconstan
//-----contains the main class methods of Expenditure
//-----version for Qt, need added functions for output display
//-----------printVctrRange was modified to output to Qt Widgets
//----------------------------------------------------------------------

#include <iostream>

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif


using namespace std;

//note 1.1

/////////////////////////////////////////////////////////////////////////////////////////
//money class PhPeso, since it will not support other currencies yet...
//addition overload, for convenience
//members made private for proper data encapsulation of the PhPeso class
//float not good, as some accuracy in addition is lost... unfortunately, it is very tedious to fix this as this was considered float from UI downto primitive class
//temporary fix is to just set the precision when printing...
/////////////////////////////////////////////////////////////////////////////////////////////

class PhPeso{
	string currency;
    float value;
public:
    PhPeso(const string curr="Php", const float val=0):currency(curr), value(val) {};
    PhPeso operator+(const PhPeso o);
	
	const string getCurrency() const { return currency; } 
	const float getValue() const { return value; }
    void printPhp();
	string getPhp(); 	//print Money to a string
};

/////////////////////////////////////////////////////////////////////////////////////////////
//note 1.2
//Expenditure class as a container for a single expense with time data
//not really sure if making the elements private is needed - just for proper encapsulation
//can ensure no stray method will modify this element
///////////////////////////////////////////////////////////////////////////////////////////////

class Expenditure{
    PhPeso price;
    string description;
    ExpTime etime;
	
public:
	//constructor for real time user input
    Expenditure(const string curr, const float val, const string dc);  
	
	//constructor variation, used for loading from csv file
	Expenditure(const string date = "00/00/0000", const string time = "00/00/00", const string wday = "Sunday", const string curr="Php", 
		const float val=0, const string dc="none"):price(curr,val),description(dc),etime(date,time,wday){} 	
	
	const PhPeso getPrice() const {return price;}
    const string getDesc() const {return description;}
    const ExpTime getTime() const {return etime;}
	
	void printExpenditure();   //print to cout
	string getExpenditure();   //print to string
};


///////////////////////////////////////////////////////////////////////////////////////////////
//Use Vector from STL as container for the expense database class
///////////////////////////////////////////////////////////////////////////////////////////////

class ExpVector{
    vector<Expenditure> vecexp;
	void emptyExcept(){ if(vecexp.empty()) throw runtime_error("no expense entries on the Database!!"); }                    //check if empty, throw exception
	void addEntry(const string date, const string time, const string wday, const string curr, const float, const string dc); //only load can call this
																															 //include date on input
public:
    ExpVector(){} 													  //calls default constructor, empty vector
    void addEntry(const string curr, const float, const string dc);   //real time user input, auto get date
	void dropEntry();                       					      //delete last entry
    
	PhPeso addTot();												  //add all expense 
	void printSize(){ cout << vecexp.size() << endl; }
    void printVctr();    										      //print all entries
    
    //print entries within specified range of date; mode0 per day, 1 per month, 2 per year, 3 per entry   //note here, can't make this const function due to iterator
	//to make this compatible with Qt GUI, instead of printing to cout, just return the string...
    string printVctrRange(const string &startDate, const string &endDate, const dateMode_t &mode);  
    
    void exportVctr(const char* fName); //export current content of a vector to a csv file 
    void loadVctr(const char* fName);   //load content of csv to database
	

	//for Qt output
	int getSize() { return vecexp.size(); }
	string getExpenditure(int index);
    
};
   
   
//-------------------------------------------
//free functions for comparing expenditures
//--------------------------------------------

bool expDateLessThan(const Expenditure exp1, const Expenditure exp2);  //needed by lowerbound function

    

