#include <iostream>
#include <string>
#include <vector>

using namespace std;

//one thing that was mentioned is the proper use of class
    //use a single class instead of class hierarchy, depending on the need -> hierarchy was always better and modular for HW.
    //there is a limit in SW, due to the amount of needed interface that will take up memory
//another thing is the use of free functions over member functions
    //though free functions uses iterators as arguments, and i think iterators have public read only access
    //can potentially limit the need for class specific functions...


//note here, all print functions are just for diagnostic...

//to put addition overloading in this class, for the sake of exercise...
//wondering if putting an overload for >> operator to csv is worth it...
//also to put format checking...
//now, make the member of this public, since this is only a basic building block, higher level classes are private anyway..

class PhPeso{
public:
	string currency;
    float value;
    
    PhPeso(const string curr="Php", const float val=0):currency(curr), value(val) {};
    PhPeso operator+(const PhPeso o);
    void printphp();
};



//to put some other methods in this class, such as overloading or having a print for this type...
//though, one other purpose is to use this as a container... to allow a similar implementation of both linked list and STL list
class Expenditure{
private:
    PhPeso price;
    string description;
public:
    Expenditure(const string curr="Php", const float val=0, const string dc="none"):price(curr,val),description(dc){};
    const PhPeso getPrice() const {return price;}
    const string getDesc() const {return description;}
    void printExpenditure();
};


//intial attempt for the container class
//in this implememntation, we use an STL vector, to maximize its built in functions -> a vector of type clas expenditure
//let us build a wrapper class around the STL template, to be able to define desired member functions
//note, I was tempted to just inherit the vector class so i could just add more functions to it, though, they said that this should not be used polymorphically!!

//tried to make the vector member public, since its member contents are by default private, and can only be operated by a set... as vector is a class itself..
    //though that means in main, some other function can directly push back a data to vecexp, as compared to having it private
//Now take note: vector is dynamically allocated perfect for very large amount of data, and it has its own definition of destructors
    //hence, we need not worry about deallocation




class ExpVector{
    vector<Expenditure> vecexp;
public:
    ExpVector(){} //confirmed that this will use a default constructor for the vector, an empty one...
    void addEntry(const string curr, const float, const string dc); //use vector push back for this..
    //void dropEntry(){ vecexp.pop_back(); }                         //push back interface
    
    PhPeso addTot();
    
	void printSize(){ cout << vecexp.size() << endl; }
    void printVctr();    
    
    void exportVctr(); //export current content of a vector to a csv file 
    void loadVctr();
};
    




    
    
    
    
