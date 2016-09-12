///////////////////////////////////
//Basic classes Test
//////////////////////////////////
//testing time now constrcutor through struct tm
timestring_now();
ExpTime time_now(g_now);
time_now.printExpTime();
cout << endl;

//testing default constructor, must be 0
ExpTime time1;    
time1.printExpTime();
cout << endl;

//testing new constructor
ExpTime time2("07/20/1988","12:03:50","Wednesday");
time2.printExpTime();
cout << endl;

//testing the new comparison function of ExpTime
cout << time_now.lessthan(time2, 0); //compare with time0
ExpTime time3("08/15/2016","15:33:50","Wednesday"); //compare with slightly less time
cout << time_now.lessthan(time3, 0); 
ExpTime time7("07/15/2016","15:33:50","Wednesday"); //compare with slightly less month
cout << time_now.lessthan(time7, 0); 
ExpTime time4("08/16/2016","15:33:50","Wednesday"); //compare with equal date
cout << time_now.lessthan(time4, 0); 
ExpTime time5("08/17/2016","15:33:50","Wednesday"); //compare with slightly more date
cout << time_now.lessthan(time5, 0);
ExpTime time8("09/15/2016","15:33:50","Wednesday"); //compare with slightly more month
cout << time_now.lessthan(time8, 0); 
ExpTime time6("08/12/2020","15:33:50","Wednesday"); //compare with very future time
cout << time_now.lessthan(time6, 0); //compare with time0

cout << endl;	
cout << time_now.lessthan(time2, 1); //compare with time0
cout << time_now.lessthan(time3, 1); 
cout << time_now.lessthan(time7, 1); 
cout << time_now.lessthan(time4, 1); 
cout << time_now.lessthan(time5, 1);
cout << time_now.lessthan(time8, 1); 
cout << time_now.lessthan(time6, 1); //compare with time0

cout << endl;	
cout << time_now.lessthan(time2, 2); //compare with time0
cout << time_now.lessthan(time3, 2); 
cout << time_now.lessthan(time7, 2); 
cout << time_now.lessthan(time4, 2); 
cout << time_now.lessthan(time5, 2);
cout << time_now.lessthan(time8, 2); 
cout << time_now.lessthan(time6, 2); //compare with time0

cout << endl;	
cout << time_now.isEqual(time2, 0); //compare with time0
cout << time_now.isEqual(time3, 0); 
cout << time_now.isEqual(time7, 0); 
cout << time_now.isEqual(time4, 0); 
cout << time_now.isEqual(time5, 0);
cout << time_now.isEqual(time8, 0); 
cout << time_now.isEqual(time6, 0); //compare with time0

cout << endl;	
cout << time_now.isEqual(time2, 1); //compare with time0
cout << time_now.isEqual(time3, 1); 
cout << time_now.isEqual(time7, 1); 
cout << time_now.isEqual(time4, 1); 
cout << time_now.isEqual(time5, 1);
cout << time_now.isEqual(time8, 1); 
cout << time_now.isEqual(time6, 1); //compare with time0

cout << endl;	
cout << time_now.isEqual(time2, 2); //compare with time0
cout << time_now.isEqual(time3, 2); 
cout << time_now.isEqual(time7, 2); 
cout << time_now.isEqual(time4, 2); 
cout << time_now.isEqual(time5, 2);
cout << time_now.isEqual(time8, 2); 
cout << time_now.isEqual(time6, 2); //compare with time0


cout << endl;	
cout << time_now.lessThanEqual(time2, 0); //compare with time0
cout << time_now.lessThanEqual(time3, 0); 
cout << time_now.lessThanEqual(time7, 0); 
cout << time_now.lessThanEqual(time4, 0); 
cout << time_now.lessThanEqual(time5, 0);
cout << time_now.lessThanEqual(time8, 0); 
cout << time_now.lessThanEqual(time6, 0); //compare with time0

cout << endl;	
cout << time_now.lessThanEqual(time2, 1); //compare with time0
cout << time_now.lessThanEqual(time3, 1); 
cout << time_now.lessThanEqual(time7, 1); 
cout << time_now.lessThanEqual(time4, 1); 
cout << time_now.lessThanEqual(time5, 1);
cout << time_now.lessThanEqual(time8, 1); 
cout << time_now.lessThanEqual(time6, 1); //compare with time0

cout << endl;	
cout << time_now.lessThanEqual(time2, 2); //compare with time0
cout << time_now.lessThanEqual(time3, 2); 
cout << time_now.lessThanEqual(time7, 2); 
cout << time_now.lessThanEqual(time4, 2); 
cout << time_now.lessThanEqual(time5, 2);
cout << time_now.lessThanEqual(time8, 2); 
cout << time_now.lessThanEqual(time6, 2); //compare with time0

//testing expenditure constructors
Expenditure exp0;
Expenditure exp1("Php",203.04,"some expenditure");
Expenditure exp2("08/13/2015","05:45:08","Thursday","Php",1999,"another freakin expense");

exp0.printExpenditure();
//cout << endl;
exp1.printExpenditure();
exp2.printExpenditure();
cout << endl;

cout << endl << endl;


///////////////////////////////////////////////////////////////////////////////
//test 1, simple add real time add entries, then print time...
//check if all added entries are printed correctly, with correct time stamp
//
//test 2, export to csv file
//just review the csv file
////////////////////////////////////////////////////////////////////////////////

ExpVector Ev1;
    
Ev1.addEntry("USD",298.99,"asus transformer t100ha");
Ev1.addEntry("Php",100.34,"the game of thrones");
Ev1.addEntry("Php",200.36,"pamana crispy adobo");
Ev1.addEntry("USD",20000.00,"HP pavillion");
Ev1.addEntry("Php",8500.00,"rent");
Ev1.addEntry("Php",1037.65,"general trias water");
Ev1.printVctr();
Ev1.exportVctr();

///////////////////////////////////////////////////////////////////////////////
//test 3 load data from source csv, then print to see if correct
//test 4 printrange, specifiy various range of date, and modes of total
////////////////////////////////////////////////////////////////////////////////

ExpVector Ev1;

Ev1.loadVctr();
Ev1.printVctr();
cout << endl << endl;

ExpTime time2("07/20/1988","12:03:50","Wednesday");
time2.printExpTime();
cout << endl;

/*
cout << time2.getDate(0) << endl;
cout << time2.getDate(1) << endl;
cout << time2.getDate(2) << endl;
*/

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


//////////////////////////////////////////////////////////
////Stress testing of sequences to simulate user usage
//////////////////////////////////////////////////////////

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
cout << "total expenditure Php 146103.9"			   << endl << endl;
cout << "********************************************" << endl << endl;
//print no expense entries


Ev1.loadVctr();

Ev1.dropEntry();
Ev1.dropEntry();
Ev1.dropEntry();

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
cout << "total expenditure => Php 171,189.3" << endl << endl;
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
cout << "expenditure value is 1250.42, dinner date" << endl << endl;
cout << "********************************************" << endl << endl;

date1 = "02/10/2016";
date2 = "08/03/2016";
Ev1.printVctrRange(date1,date2,mode);
cout << "********************************************" << endl << endl;
cout << "check6: per day entry from 2/10/2016 to 8/3/2016" << endl << endl;
cout << " 8252.67, 9984.23, 10400, 20000, 20000"	   << endl << endl;
cout << "********************************************" << endl << endl;


date1 = "02/10/2013";
date2 = "08/03/2018";

mode=1;
Ev1.printVctrRange(date1,date2,mode);
cout << "********************************************" << endl << endl;
cout << "check7: per month entry, all entries from 2013 to 2018" << endl << endl;
cout << "1050, 9000.45, 1364.12, 49716.92, 50400, 32538.35, 38534, tot=182604" << endl << endl;
cout << "********************************************" << endl << endl;

mode=2;
Ev1.printVctrRange(date1,date2,mode);
cout << "********************************************" << endl << endl;
cout << "check8: per year entry, all entries from 2013 to 2018" << endl << endl;
cout << "two entries, total = 182604" << endl << endl;
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





/////////////////////////////////
//other commented sequences
////////////////////////////////

//string s_x1 = "Jolly Sphagetti";
//Expenditure x1(100,34,"Jolly Sphagetti");
//x1.printExpenditure();  

//timestring_now();
//cout << g_time_buf << endl;
//ExpTime et_now = tmtoExptime();

//cout << et_now.daytimesyear() << " " << et_now.yday;
