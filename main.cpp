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

	ExpVector Ev1;

	Ev1.loadVctr();
	Ev1.printVctr();
	cout << endl << endl;
	Ev1.exportVctr();
		
	int mode = 1; //0,1,2, or 3
	string date1 = "07/20/2016";
	string date2 = "07/20/2016";
	
	Ev1.printVctrRange(date1,date2,mode);
	
	date1 = "02/07/2016";
	date2 = "02/07/2016";
	Ev1.printVctrRange(date1,date2,mode);
	
	date1 = "02/10/2016";
	date2 = "08/03/2016";
	Ev1.printVctrRange(date1,date2,mode);
	
		
	date1 = "02/10/2013";
	date2 = "08/03/2018";
	Ev1.printVctrRange(date1,date2,mode);
	
	
	date1 = "02/10/2017";
	date2 = "08/03/2018";
	Ev1.printVctrRange(date1,date2,mode);

		
	

    return 0;
}
