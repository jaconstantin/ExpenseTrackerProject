#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

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
};

/////////////////////////////////////////////////////////////////////////////////////////////
//note 1.2
//Expenditure class as a container for a single expense data
//not really sure if making the elements private is needed - just for proper encapsulation
//can ensure no stray method will modify this element
///////////////////////////////////////////////////////////////////////////////////////////////

class Expenditure{
    PhPeso price;
    string description;
    ExpTime etime;
public:
    Expenditure(const string curr, const float val, const string dc);  //constructor for real time user input
	Expenditure(const string date = "00/00/0000", const string time = "00/00/00", const string wday = "Sunday", const string curr="Php", const float val=0, const string dc="none")
		:price(curr,val),description(dc),etime(date,time,wday){} //constructor variation, used for loading from csv file	
	
	const PhPeso getPrice() const {return price;}
    const string getDesc() const {return description;}
    const ExpTime getTime() const {return etime;}
	
	void printExpenditure();
    //const bool operator<(const Expenditure &o) const {return etime < o.etime; } //compare expenditure through its date
    //const bool operator<=(const Expenditure &o) const {return etime <= o.etime;} 
};



class ExpVector{
    vector<Expenditure> vecexp;
	void emptyExcept(){ if(vecexp.empty()) throw runtime_error("no expense entries on the Database!!"); } //check if empty, throw exception
public:
    ExpVector(){} //confirmed that this will use a default constructor for the vector, an empty one... ->calls default constructor of vector
    void addEntry(const string curr, const float, const string dc); 
    void addEntry(const string date, const string time, const string wday, const string curr, const float, const string dc);
    //i think the second addentry function must be a private/protected function!
	void dropEntry();                       
    PhPeso addTot();
    
	void printSize(){ cout << vecexp.size() << endl; }
    void printVctr();    
    
    //mode0 per day, 1 per month, 2 per year, 3 per entry
    void printVctrRange(const string &startdate, const string &enddate, const dateMode &mode);  //note here, can't make this const function due to iterator
    
    void exportVctr(); //export current content of a vector to a csv file 
    void loadVctr();
	
	void trialFctn (const string &startdate);
	
    
};
    
//free functions for comparing expenditures
bool expDateLessThan(const Expenditure exp1, const Expenditure exp2);
//bool expDateLessThanEqual(const Expenditure exp1, const Expenditure exp2);
    

