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
//note here, all print functions are just for diagnostic...
//
//to put addition overloading in this class, for the sake of exercise...
//wondering if putting an overload for >> operator to csv is worth it...
//also to put format checking...
//now, make the member of this public, since this is only a basic building block, higher level classes are private anyway..
/////////////////////////////////////////////////////////////////////////////////////////////

//note to change this in the future, as the float/double accuracy sometimes losses a decimal place, which is very vital in money...
class PhPeso{
public:
	string currency;
    float value;
    
    PhPeso(const string curr="Php", const float val=0):currency(curr), value(val) {};
    PhPeso operator+(const PhPeso o);
    void printphp();
};

/////////////////////////////////////////////////////////////////////////////////////////////
//note 1.2
//to put some other methods in this class, such as overloading or having a print for this type...
//though, one other purpose is to use this as a container... 
//let us try adding the time memebr
///////////////////////////////////////////////////////////////////////////////////////////////

class Expenditure{
private:
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
    //void printDate(int mode=0); //set if 0=daily, 1=monthly, or 2=yearly...
	void printExpenditure();
    const bool operator<(const Expenditure &o) const {return etime < o.etime; } //compare expenditure through its date
    const bool operator<=(const Expenditure &o) const {return etime <= o.etime;} 
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
    void printVctrRange(const string &startdate, const string &enddate, int &mode);  //note here, can't make this const function due to iterator
    
    void exportVctr(); //export current content of a vector to a csv file 
    void loadVctr();
    
};
    



//temporary classes
//use of struct Exptime here requires aux.h to be defined first

    
    
    
