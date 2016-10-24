	
	
//testing Credit Expenditure Constructors
CreditExpenditure cexp0;
CreditExpenditure cexp1("Php",1000,"some expenditure",200);
CreditExpenditure cexp2("08/13/2015","05:45:08","Thursday","Php",1999,"another freakin expense",999,1000);
cexp0.printExpenditure(); cout << endl;
cexp1.printExpenditure(); cout << endl;
cexp2.printExpenditure();

cout << endl << endl << endl;

//building a database for credit expenses

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

Ev1.exportVctr("source-file-credit.csv");

//testing ExpVector containing credit expense
Ev1.loadVctr("source-file-credit.csv");
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