#include <iostream>
#include <fstream>
#include <cstdlib>
#include "main_classes.h"


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

Expenditure::Expenditure(const string date, const string time, const int wday, const int yday, const string curr, const float val, const string dc):price(curr,val),description(dc){
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
	etime.yday = static_cast<timedate_t>(yday);
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
void ExpVector::addEntry(const string date, const string time, const int wday, const int yday, const string curr, const float val, const string dc){
	Expenditure tmp(date, time, wday, yday, curr, val, dc);
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

void ExpVector::exportVctr(){
	ofstream f_dest("dest-file.csv");
	for(int i=0; i<vecexp.size(); ++i){
		PhPeso tmp = vecexp[i].getPrice();	
		ExpTime tmptime = vecexp[i].getTime();
		
		f_dest << tmptime.month << "/" << tmptime.day << "/" << tmptime.year << ",";
		f_dest << tmptime.hour << ":" << tmptime.min << ":" << tmptime.sec << ",";
		f_dest << tmptime.wkday << "," << tmptime.yday << ",";	
		f_dest << tmp.currency << "," << tmp.value << ",";
		f_dest << vecexp[i].getDesc() << "\n";
	}
	f_dest.close();
}    


void ExpVector::loadVctr(){
 	ifstream f_source("dest-file.csv");
 	string tmp_str[7];
 	while(f_source.good()){
 		for(int x=0; x<6; ++x) getline(f_source,tmp_str[x],',');
 		getline(f_source,tmp_str[6],'\n');
 		addEntry(tmp_str[0], tmp_str[1], atoi(tmp_str[2].c_str()), atoi(tmp_str[3].c_str()), tmp_str[4], atof(tmp_str[5].c_str()), tmp_str[6]);
		
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




 
