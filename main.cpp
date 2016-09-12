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
#include "main_classes.h"
#define __MAIN_CLASSES 
#endif

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

#include "userinterface.h"


//define here a variable for test diagnositc messages


using namespace std;

char extern g_time_buf[30];
time_t extern g_t;
struct tm extern *g_now;




int main(void){
	
	
//////////////////////
///in this UI, all entries are loaded and stored from a single csv file, source-file.csv
/////////////////////	

	//UI();
	string start_date, end_date, cmd_temp;
	int mode;

	string currency, description;
	float value;
	
	ExpVector Ev1;
	mode = 3;
	try{ Ev1.printVctrRange("01/01/0001","01/01/2300",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	cout << "********************************************" << endl << endl;
	cout << "check0: print no expense due to empty vector" << endl << endl;
	cout << "********************************************" << endl << endl;
	//print no expense entries


	Ev1.loadVctr();
	try{ Ev1.printVctrRange("01/01/0001","01/01/2300",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	cout << "********************************************" << endl << endl;
	cout << "check1: just printed all entry from source csv" << endl << endl;
	cout << "********************************************" << endl << endl;
	//print all expense in the vector per entry
	
	try{ Ev1.printVctrRange("13/01/0001","01/01/2300",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	try{ Ev1.printVctrRange("01/32/0001","01/01/2300",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	try{ Ev1.printVctrRange("01/28/0001","0100102300",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	try{ Ev1.printVctrRange("0000000000","01/01/2020",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	cout << "********************************************" << endl << endl;
	cout << "check2: invalid dates as input to printVctr range, not print anything except for the last entry" << endl << endl;
	cout << "********************************************" << endl << endl;
	//all invalid dates, except for the last one, which is unfortunately not fixed 00000000 -> 0000000012 is valid and is considered as a month
	
	
	Ev1.addEntry("Php",33500,"dell inspiron 7000");
	Ev1.addEntry("Php",2500,"Microsoft Office 365");
	Ev1.addEntry("Php",500,"lunch at Romeo's Grill");
	try{ Ev1.printVctrRange("01/01/2016","01/01/2017",mode); }
	catch (runtime_error &error) { runtimeErrorHandler(error); }
	cout << "********************************************" << endl << endl;
	cout << "check3: print all expense in 2016 including the latest 3 additional entries" << endl << endl;
	cout << "********************************************" << endl << endl;
	//print all expense in 2016 with all additional entries
	
	
	mode = 0; //0,1,2, or 3
	string date1 = "07/20/2016";
	string date2 = "07/20/2016";

	Ev1.printVctrRange(date1,date2,mode);
	cout << "********************************************" << endl << endl;
	cout << "check4: no records for specified range for 7/20/2016" << endl << endl;
	cout << "********************************************" << endl << endl;

	date1 = "02/07/2016";
	date2 = "02/07/2016";
	Ev1.printVctrRange(date1,date2,mode);
	cout << "********************************************" << endl << endl;
	cout << "check5: one record for 2/07/2016, per day" << endl << endl;
	cout << "********************************************" << endl << endl;

	date1 = "02/10/2016";
	date2 = "08/03/2016";
	Ev1.printVctrRange(date1,date2,mode);
	cout << "********************************************" << endl << endl;
	cout << "check6: per day entry from 2/10/2016 to 8/3/2016" << endl << endl;
	cout << "********************************************" << endl << endl;

	
	date1 = "02/10/2013";
	date2 = "08/03/2018";
	
	mode=1;
	Ev1.printVctrRange(date1,date2,mode);
	cout << "********************************************" << endl << endl;
	cout << "check7: per month entry, all entries from 2013 to 2018" << endl << endl;
	cout << "********************************************" << endl << endl;

	mode=2;
	Ev1.printVctrRange(date1,date2,mode);
	cout << "********************************************" << endl << endl;
	cout << "check8: per year entry, all entries from 2013 to 2018" << endl << endl;
	cout << "********************************************" << endl << endl;


	date1 = "02/10/2017";
	date2 = "08/03/2018";
	Ev1.printVctrRange(date1,date2,mode);
	cout << "********************************************" << endl << endl;
	cout << "check9: no records for specified range for 2017 onwards" << endl << endl;
	cout << "********************************************" << endl << endl;
	
	Ev1.exportVctr();
	cout << "********************************************" << endl << endl;
	cout << "check10: exported current vector, gotta check the new csv file" << endl << endl;
	cout << "********************************************" << endl << endl;
	

	return 0;	
}
