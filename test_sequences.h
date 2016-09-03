
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

///////////////////////////////////////////////////////////////////////////////
//test 3 load data from source csv, then print to see if correct
//test 4 printrange, specifiy various range of date
////////////////////////////////////////////////////////////////////////////////

Ev1.loadVctr();
Ev1.printVctr();

cout << endl << endl;

string date1 = "07/20/2016";
string date2 = "07/20/2016";
Ev1.printVctrRange(date1,date2);

date1 = "02/10/2016";
date2 = "08/03/2016";
Ev1.printVctrRange(date1,date2);

date1 = "02/10/2013";
date2 = "08/03/2018";
Ev1.printVctrRange(date1,date2);

date1 = "02/10/2017";
date2 = "08/03/2018";
Ev1.printVctrRange(date1,date2);


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
