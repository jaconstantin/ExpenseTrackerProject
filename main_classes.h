#include <iostream>
#include <string>
#include <vector>
#include <ctime>

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
	Expenditure(const string date, const string time, const int wday, const int yday, const string curr, const float val, const string dc); //constructor variation, used for loading from csv file
    const PhPeso getPrice() const {return price;}
    const string getDesc() const {return description;}
    const ExpTime getTime() const {return etime;}
    void printExpenditure();
};



class ExpVector{
    vector<Expenditure> vecexp;
public:
    ExpVector(){} //confirmed that this will use a default constructor for the vector, an empty one...
    void addEntry(const string curr, const float, const string dc); 
    void addEntry(const string date, const string time, const int wday, const int yday,const string curr, const float, const string dc);
    
	//void dropEntry(){ vecexp.pop_back(); }                         //push back interface
    PhPeso addTot();
    
	void printSize(){ cout << vecexp.size() << endl; }
    void printVctr();    
    
    void exportVctr(); //export current content of a vector to a csv file 
    void loadVctr();
};
    



//temporary classes
//use of struct Exptime here requires aux.h to be defined first

    
    
    
