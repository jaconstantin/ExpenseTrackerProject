#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

//note here, to avoid the conflict in compiling when including the same header file

#ifndef __MAIN_CLASSES
#include "main_classes.h"
#define __MAIN_CLASSES 
#endif

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif




using namespace std;

char extern g_time_buf[30];
time_t extern g_t;
struct tm extern *g_now;


int main(void){
    
    //string s_x1 = "Jolly Sphagetti";
    //Expenditure x1(100,34,"Jolly Sphagetti");
    //x1.printExpenditure();  
   
    
    ExpVector Ev1;
    
    Ev1.addEntry("USD",298.99,"asus transformer t100ha");
	Ev1.addEntry("Php",100.34,"the game of thrones");
    Ev1.addEntry("Php",200.36,"pamana crispy adobo");
    Ev1.addEntry("USD",20000.00,"HP pavillion");
    Ev1.addEntry("Php",8500.00,"rent");
    Ev1.addEntry("Php",1037.65,"general trias water");
    Ev1.printVctr();
	/*
    cout << g_time_buf << endl;
  	*/
  	
	/*
  	Ev1.loadVctr();
  	Ev1.printVctr();
	*/
	//Ev1.exportVctr();
    
    //try here a code that will see if i can read from a file, a delimit with variable delimters
 
 	//stringtotimedate(const string &datestr, const size_t spos, char delim, size_t &npos)
 	
 	
 	
    /*create a function for getting the current time*/
   //it must be translatable to a fixed length string
	/*
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << endl;

    //note here, members of the time structure is in int, to convert this to string
    char time_buf[30];
    strftime(time_buf,30,"%x\t%A\t%X",now);
    cout << time_buf;
	*/
	
	/*
	timestring_now();
	ExpTime a=tmtoExptime();
    cout << g_time_buf << endl;
    
    cout << a.day << endl;
	cout << a.month << endl;
	cout << a.year << endl;
	cout << a.wkday << endl;
	cout << a.yday << endl;
	cout << a.hour << endl;
	cout << a.min << endl;
	cout << a.sec << endl;
	
	cout << sizeof(ExpTime);
    */
    
    //month_t m2 = December;
    //cout << m2 << endl;
    
    //printf("%\n",m2); //next question here, for enum, can i print the value instead of the integer??
    
   //cout << sizeof(tm) << " " << sizeof(day_t) << " " << sizeof(weekday_t) << " " << sizeof(month_t) << " " << sizeof(ExpTime) << " " << sizeof(char*) << endl;
   //cout << sizeof(Expenditure);
    
   //Expenditure x1("Php",100.34,"the game of thrones");
   //x1.printExpenditure();
   //cout << sizeof(tm) << " " << sizeof(ExpTime) << endl;
 
    
    return 0;
}
