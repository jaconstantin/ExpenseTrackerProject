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
