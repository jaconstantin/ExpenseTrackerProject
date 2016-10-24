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

	//UI session1;
	//session1.launchUI();
	
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
	
	
	ExpVector Ev1;
	
	
	
	
	Ev1.addEntry("07/20/2014","11:30:45","Sunday","Php",21000,"asus zenfone 3",0,21000);
	Ev1.addEntry("07/20/2014","11:32:45","Sunday","Php",36000,"HP elitebook",10000,26000);
	Ev1.addEntry("08/13/2014","13:30:45","Wednesday","Php",0,"credit card payment",25000,-25000);
	
	Ev1.addEntry("01/05/2015","11:30:45","Monday","Php",0,"credit card advance payment",20000,-20000);
	Ev1.addEntry("01/05/2015","11:32:45","Monday","Php",8500,"gov hills rent",8500,0);
	Ev1.addEntry("03/12/2015","13:30:45","Thursday","Php",2400.35,"hawaian bbq",0,2400.35);
	Ev1.addEntry("03/13/2015","14:30:45","Friday","Php",25000,"tokyo airfare",0,25000);
	Ev1.addEntry("05/25/2015","15:32:45","Wednesday","Php",0,"credit card payment",30000,-30000);
	Ev1.addEntry("05/25/2015","16:30:45","Wednesday","Php",3000,"IELTS test payment",3000,0);
	Ev1.addEntry("05/25/2015","17:30:45","Wednesday","Php",100000,"Sulo Riviera Reception",10000,90000);
	
	
	
	Ev1.addEntry("Php",10000,"Foch apartment Rent",10000);
	Ev1.addEntry("Php",3400.2,"Coles Grocery",3400.2);
	
	//Ev1.loadVctr("source-file-credit.csv");
	Ev1.printVctr();
	
	dateMode_t mode = perDay; //0,1,2, or 3
	string date1 = "08/13/2014";
	string date2 = "05/25/2015";
	Ev1.printVctrRange(date1,date2,mode);
	
	mode = perMonth;	
	date1 = "08/13/2000";
	date2 = "05/25/2018";
	Ev1.printVctrRange(date1,date2,mode);
	
	mode=perYear;
	Ev1.printVctrRange(date1,date2,mode);
	
	mode=perEntry;
	Ev1.printVctrRange(date1,date2,mode);
	
	Ev1.exportVctr("source-file-credit.csv");

	

	
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
