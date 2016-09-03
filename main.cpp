#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "main_classes.h"
#include "auxillary.h"

using namespace std;

char extern time_buf[30];



int main(void){
    
    //string s_x1 = "Jolly Sphagetti";
    //Expenditure x1(100,34,"Jolly Sphagetti");
    //x1.printExpenditure();  
   
   /*
    ExpVector Ev1;
	
    Ev1.addEntry("Php",100.34,"the game of thrones");
    Ev1.addEntry("Php",200.36,"pamana crispy adobo");
    Ev1.addEntry("USD",20000.00,"HP pavillion");
    Ev1.addEntry("Php",8500.00,"rent");
    Ev1.addEntry("Php",1037.65,"general trias water");
   
   	*/
    //Ev1.printVctr();
   // Ev1.loadVctr();  
    //Ev1.loadVctr();  
    

	
	//Ev1.printVctr();
   
	//Ev1.exportVctr();  
    /*
    PhPeso tot=Ev1.addTot();
    tot.printphp();
    
    PhPeso a("Php",201.35), b("Php",324.56);
    a.printphp();
    a = a+b;
    a.printphp();
    b.printphp();
    */
    //ofstream f_dest("dest-file.txt");
    //int x=5;
    //f_dest << x << " how how " << x << endl;
	//f_dest.close(); 
	
	  
    //want to create a function that can stream in the contents of the expense vector to a csv
    //well, want a csv file
    
  
   /*
    ifstream f_source("dest-file.csv");
    string tmp_str;
    getline(f_source,tmp_str,'\n');
    cout << tmp_str << endl;
    
    getline(f_source,tmp_str,',');
    
    getline(f_source,tmp_str,',');
    cout << tmp_str << endl;
    float tmp_flt = atof(tmp_str.c_str());
    cout << tmp_flt+0.01 << endl;
    cout << sizeof(tmp_flt);
   // float tmp_flt = stod(tmp_str);
    
    //getline(f_source,tmp_str,',');
    //cout << tmp_str;
    //getline(f_source,tmp_str,',');
    //cout << tmp_str;
    //getline(f_source,tmp_str,',');
    //cout << tmp_str;
    //getline(f_source,tmp_str,',');
    
    f_source.close();
    */
    
    
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
	
	
	timestring_now();
    cout << time_buf;
    
    return 0;
}
