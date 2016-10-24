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
#include "main_classes_v2.h"
#define __MAIN_CLASSES 
#endif

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

#include "ui.h"


using namespace std;

char extern g_time_buf[30];
time_t extern g_t;
struct tm extern *g_now;




int main(void){
	
	
//////////////////////
///in this UI, all entries are loaded and stored from a single csv file, source-file.csv
/////////////////////	

	UI session1;
	session1.launchUI();
	
	//cout << strcmp("souce-file.csv","source-file.csv");
	//const char* s1 = "source-file.csv";
	//const char* s2 = "source-file.csv";
	
	//string s3 = s1;
	//string s4 = s2;
	//cout << s3.compare(s4);
	
	
	
	//testing expenditure constructors
	/*
	Expenditure exp0;
	Expenditure exp1("Php",203.04,"some expenditure");
	Expenditure exp2("08/13/2015","05:45:08","Thursday","Php",1999,"another freakin expense");

	exp0.printExpenditure(); cout << endl;
	exp1.printExpenditure(); cout << endl;
	exp2.printExpenditure(); cout << endl;
	
	cout << endl << endl << endl;
	
	
	CreditExpenditure cexp0;
	CreditExpenditure cexp1("Php",1000,"some expenditure",200);
	CreditExpenditure cexp2("08/13/2015","05:45:08","Thursday","Php",1999,"another freakin expense",999,1000);
	cexp0.printExpenditure(); cout << endl;
	cexp1.printExpenditure(); cout << endl;
	cexp2.printExpenditure();
	
	cout << endl << endl << endl;
	*/
	
	
	//ExpVector Ev1;
	//Ev1.loadVctr("source-file-credit.csv");
	//Ev1.printVctr();
	
	//Ev1.addEntry("Php",34000,"asus transformer t100ha",20000.50);
	//Ev1.addEntry("Php",150.45,"game of thrones S01e02",150.45);
	//Ev1.addEntry("Php",1046.99,"pamana dinner",0);
	//Ev1.printVctr();
	//Ev1.exportVctr("source-file-credit.csv");

	

	
	//cout << endl << endl << endl;
	
	//Ev1.addEntry("USD",298.99,"asus transformer t100ha");
	//Ev1.addEntry("Php",100.34,"the game of thrones");
	//Ev1.addEntry("Php",200.36,"pamana crispy adobo");
	
	//Ev1.exportVctr();


	
	
	
	
	
	/*
	string startDate = "07/20/2018";
	string endDate = "08/21/2019";
	
	Expenditure tmpStartExp(startDate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure *ptrEndExp = new Expenditure(endDate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure *ptrStartExp = &tmpStartExp;
	*/
	
	return 0;	
}
