#include <iostream>
#include <fstream>
#include <cstdlib>
#include "main_classes.h"


//define here some test diagnositc enable variables
#ifndef test
//#define test 1
#endif


using namespace std;

void PhPeso::printphp(){
    cout << currency << value << endl;
}

PhPeso PhPeso::operator+(const PhPeso o){
    PhPeso tmp;
    tmp.value = value + o.value;
    return tmp;
}
    
////////////////
//put this here for a while, should be in auxillary.cpp
//don't know how to compile .h files properly!!
//overload the << operator of ExpTime, for a nice print output
////////////////
/* not sure if this is worth it..
ostream& operator<<(ostream &output, const ExpTime &et){
	output << et.month << "/" << et.day << "/" << et.year << "  " 
	       << et.hour << ":" << et.min << ":" << et.sec << "  "; 
	//strftime(g_time_buf,30,"%x\t%A\t%X",g_now);
	return output;
}
*/    

Expenditure::Expenditure(const string curr="Php", const float val=0, const string dc="none"):price(curr,val),description(dc){
	timestring_now();
	etime = tmtoExptime();
}

Expenditure::Expenditure(const string date, const string time, const int wday, const string curr, const float val, const string dc):price(curr,val),description(dc){
	size_t expenditure_tmp_npos = 0;
	char expenditure_tmp_delim = '/';
	etime.month = stringtotimedate(date,0,expenditure_tmp_delim,expenditure_tmp_npos);
	etime.day = stringtotimedate(date,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	etime.year = stringtotimedate(date,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	
	expenditure_tmp_npos = 0;
	expenditure_tmp_delim = ':';
	etime.hour = stringtotimedate(time,0,expenditure_tmp_delim,expenditure_tmp_npos);
	etime.min = stringtotimedate(time,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	etime.sec = stringtotimedate(time,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	
	etime.wkday = static_cast<timedate_t>(wday);
}

    
void Expenditure::printExpenditure(){
    cout << etime.month << "/" << etime.day << "/" << etime.year << "  " 
	     << etime.hour << ":" << etime.min << ":" << etime.sec << "  "; 
	cout << etime.stringWkday() << "  ";
	cout <<'"'<< description << '"' << "\t";
    price.printphp();
 
}


//add entry, time=now, for real time user input
void ExpVector::addEntry(const string curr="Php", const float val=0, const string dc="none"){
    Expenditure tmp(curr,val,dc);
    vecexp.push_back(tmp);
}

//add entry with time record, for loading from csv file
void ExpVector::addEntry(const string date, const string time, const int wday, const string curr, const float val, const string dc){
	Expenditure tmp(date, time, wday, curr, val, dc);
	vecexp.push_back(tmp);
}

PhPeso ExpVector::addTot(){
    PhPeso tmp;
    for(int i=vecexp.size(); i>0; --i) tmp = tmp + vecexp[i-1].getPrice();
    return tmp;
}
    
void ExpVector::printVctr(){
    for(int i=0; i<vecexp.size(); ++i) vecexp[i].printExpenditure();
}

void ExpVector::printVctrRange(const string &startdate, const string &enddate){
	Expenditure prntrng_exp_temp(startdate, "00:00:00", 3, "Php",0,"none");
	Expenditure prntrng_exp_temp2(enddate, "00:00:00", 3, "Php",0,"none");
	
	///////////////////////////////////////////////////////////////////////
	#ifdef test
	cout << "prntrng_exp_temp -->";
	prntrng_exp_temp.printExpenditure();
	
	ExpTime testprntrng_exptime_temp = prntrng_exp_temp.getTime();
	ExpTime testprntrng_exptime_temp2 = prntrng_exp_temp2.getTime();
	cout << "printing days effective of start date to end date ---> ";
	cout << testprntrng_exptime_temp.test_get_dayseffective() << "--->>" << testprntrng_exptime_temp2.test_get_dayseffective();
	cout << endl;
	#endif
	////////////////////////////////////////////////////////////////////////
	
	//need to put error check see if initial date is out of bounds
	//if output is true, then can continue with the function
	Expenditure prntrng_exp_temp3 = vecexp.back();
	if(!(prntrng_exp_temp <= prntrng_exp_temp3)){
		cout << "no records for the specified range" << endl << endl;
		return;
	}
	
	vector<Expenditure>::iterator low;
	low = lower_bound(vecexp.begin(), vecexp.end(), prntrng_exp_temp);
	
	#ifdef test
	cout << "printing the expenditure output of lowerbound function...-->";
	low->printExpenditure();
	cout << endl << endl;
	#endif
	
	
	PhPeso prntrng_moneytot_temp;   //add total functionality
	for(low; (*low) <= prntrng_exp_temp2; ++low){
		low->printExpenditure();
		prntrng_moneytot_temp = prntrng_moneytot_temp + low->getPrice();
		if( (low+1) == vecexp.end()) break;		//also need to indicate a stop when we go out of bounds
		
		#ifdef test
		testprntrng_exptime_temp = low->getTime();
		cout << "days effective of last printed entry is... " << testprntrng_exptime_temp.test_get_dayseffective() << endl;
		cout << "continue the loop??? ....." << ( (*low) <= prntrng_exp_temp2) << endl;
		cout << "cumulative total is = "; 
		prntrng_moneytot_temp.printphp(); 
		cout << endl << endl;
		#endif
	}
	cout << "total expenditure........";
	prntrng_moneytot_temp.printphp();
	cout << endl << "done printing entries..." << endl << endl;
}


void ExpVector::exportVctr(){
	ofstream f_dest("dest-file.csv");
	for(int i=0; i<vecexp.size(); ++i){
		PhPeso tmp = vecexp[i].getPrice();	
		ExpTime tmptime = vecexp[i].getTime();
		
		f_dest << tmptime.month << "/" << tmptime.day << "/" << tmptime.year << ",";
		f_dest << tmptime.hour << ":" << tmptime.min << ":" << tmptime.sec << ",";
		f_dest << tmptime.wkday << ",";	
		f_dest << tmp.currency << "," << tmp.value << ",";
		f_dest << vecexp[i].getDesc() << "\n";
	}
	f_dest.close();
}    


void ExpVector::loadVctr(){
 	ifstream f_source("source-file.csv");
 	string tmp_str[6];
 	while(f_source.good()){
 		for(int x=0; x<5; ++x) getline(f_source,tmp_str[x],',');
 		getline(f_source,tmp_str[5],'\n');
 		addEntry(tmp_str[0], tmp_str[1], atoi(tmp_str[2].c_str()), tmp_str[3], atof(tmp_str[4].c_str()), tmp_str[5]);
		
		//addEntry(tmp_curr,atof(tmp_value.c_str()),tmp_desc);
	 }
	f_source.close();
	vecexp.pop_back(); //this function copies the null character as the last element, hence remove this
	
 }

 
////////////////////////////////// 
//temp files
//why is this flagging a redefintion error?
//Expenditure_temp::Expenditure_temp(const string curr, const float val, const string dc):price(curr,val),description(dc){
//	timestring_now();
//	etime = tmtoExptime();
//};




 
