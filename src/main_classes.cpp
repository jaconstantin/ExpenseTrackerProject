#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
//#include <cmath>
#include <iomanip>

#include "main_classes.h"

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

//define here some test diagnositc enable variables
#ifndef test
//#define test 1
#endif


using namespace std;

char extern g_time_buf[30];
time_t extern g_t;
struct tm extern *g_now;

void PhPeso::printPhp(){
    cout << currency;
	cout << std::fixed << std::setprecision(2) << value << endl;
}

PhPeso PhPeso::operator+(const PhPeso o){
	PhPeso tmpMoney;
    tmpMoney.value = value + o.value;
    return tmpMoney;
}
    

Expenditure::Expenditure(const string curr="Php", const float val=0, const string dc="none"):price(curr,val),description(dc){
	timestring_now();
	ExpTime exp_timenow_temp(g_now);
	etime = exp_timenow_temp;
}
    
void Expenditure::printExpenditure(){
	etime.printExpTime();
	cout << "  ";
    cout <<'"'<< description << '"' << "\t";
	price.printPhp(); 
}


//add entry, time=now, for real time user input
void ExpVector::addEntry(const string curr="Php", const float val=0, const string dc="none"){
    Expenditure tmp(curr,val,dc);
    vecexp.push_back(tmp);
}


//add entry with time record, for loading from csv file
void ExpVector::addEntry(const string date, const string time, const string wday, const string curr, const float val, const string dc){
	Expenditure tmp(date, time, wday, curr, val, dc);
	vecexp.push_back(tmp);
}

/*
PhPeso ExpVector::addTot(){
    PhPeso tmp;
    for(int i=vecexp.size(); i>0; --i) tmp = tmp + vecexp[i-1].getPrice();
    return tmp;
}
*/

void ExpVector::dropEntry(){
	emptyExcept();	//throw exception and abort if vector is empty
	vecexp.pop_back(); 
}  
    
void ExpVector::printVctr(){
    for(int i=0; i<vecexp.size(); ++i) vecexp[i].printExpenditure();
}



void ExpVector::exportVctr(){
	ofstream f_dest("source-file.csv");
	for(int i=0; i<vecexp.size(); ++i){
		PhPeso exprtvctr_money_tmp = vecexp[i].getPrice();	
		ExpTime exprtvctr_time_tmp = vecexp[i].getTime();
		
		f_dest << exprtvctr_time_tmp.getDate() << ",";
		f_dest << exprtvctr_time_tmp.getTime() << ",";
		f_dest << exprtvctr_time_tmp.stringWkday() << ",";	
		//f_dest << exprtvctr_money_tmp.getCurrency() << "," << exprtvctr_money_tmp.getValue() << ",";
		f_dest << vecexp[i].getPrice().getCurrency() << "," << vecexp[i].getPrice().getValue() << ",";
		f_dest << vecexp[i].getDesc() << "\n";
	}
	f_dest.close();
}    


void ExpVector::loadVctr(){
 	ifstream f_source("source-file.csv");
	
	if(f_source) //verify if file was opened succesffully
	{
		string tmp_str[6];
		while(f_source.good())
		{
			for(int x=0; x<5; ++x) getline(f_source,tmp_str[x],',');
			getline(f_source,tmp_str[5],'\n');		
			//tmp_str[5] = tmp_str[5].substr(0,tmp_str[5].size()-1); //this line is needed to remove the exta space for source files written manually in excel... once the program is run, and the vector is stored back to the file, this extra space will no longer exist	
			addEntry(tmp_str[0], tmp_str[1], tmp_str[2], tmp_str[3], atof(tmp_str[4].c_str()), tmp_str[5]);
			//addEntry(tmp_curr,atof(tmp_value.c_str()),tmp_desc);
		}
		f_source.close();
		vecexp.pop_back(); //this function copies the null character as the last element, hence remove this
	}
	
	else
	{
		cout << endl << "**************************" << endl;
		cerr << "Warning, could not read from source-file.csv, no data was loaded!\n";
	}
}

void ExpVector::printVctrRange(const string &startdate, const string &enddate, const dateMode &mode){
	
	emptyExcept();	//throw exception and abort if vector is empty

	Expenditure prntrng_stexp_temp(startdate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure prntrng_endexp_temp(enddate, "00:00:00", "Sunday", "Php",0,"none");
	PhPeso prntrng_moneytot_temp, prntrng_moneytot_temp2;   //add total functionality
	Expenditure prntrng_prevexp_temp("00/00/2500","00:00:00","Sunday","Php",0,"none");  //ensures that the loop will start
	int prntrng_findflag_temp = 0; //check if a valid entry is returned
	
	//need to put error check see if initial date is out of bounds, if output is true, then can continue with the function
	Expenditure prntrng_lstexp_temp = vecexp.back();
	//if(!( expDateLessThanEqual(prntrng_stexp_temp,prntrng_lstexp_temp) )){
	if(!( prntrng_stexp_temp.getTime() <= prntrng_lstexp_temp.getTime() )){
		cout << "****no records for the specified range****" << endl << endl;
		return;
	}
	
	vector<Expenditure>::iterator low;
	low = lower_bound(vecexp.begin(), vecexp.end(), prntrng_stexp_temp, expDateLessThan); //find initial entry using function pointer
		
	//for(low; (*low) <= prntrng_endexp_temp; ++low){ 
	for(low; (low->getTime() <= prntrng_endexp_temp.getTime()); ++low){
		prntrng_findflag_temp = 1; //found at least 1 entry
		
		#ifdef test
		cout << "moneytot_temp = ";	
		prntrng_moneytot_temp.printPhp();
		#endif
	
		
		ExpTime prntrng_currtime_temp1 = low->getTime();
		ExpTime prntrng_prevtime_temp2 = prntrng_prevexp_temp.getTime(); 
		prntrng_moneytot_temp2 =  prntrng_moneytot_temp2 + low->getPrice(); //accumulate grand total
		
		if(prntrng_currtime_temp1.lessThanEqual(prntrng_prevtime_temp2,mode)) prntrng_moneytot_temp = prntrng_moneytot_temp + low->getPrice(); //compare if same date, prev date will never be > curr date
		else{ //next date
			if(mode==perEntry) low->printExpenditure(); //print by entry, always go to this statement
			else{
	 			cout << prntrng_prevtime_temp2.getDate(mode) << ".........";
				prntrng_moneytot_temp.printPhp();  
			   	prntrng_moneytot_temp = low->getPrice(); //reset total count
			}
		}
		prntrng_prevexp_temp = *low;
		
		if( (low+1) == vecexp.end()) break;		//also need to indicate a stop when we go out of bounds
		
	}
	
	if(prntrng_findflag_temp==1){ 	//for queries with only 1 entry
		//no need for this statement in mode 'perEntry', since its bool function always return false, hence, always printsexpenditure per entry
		if(mode!=perEntry){
			ExpTime prntrng_prevtime_temp2 = prntrng_prevexp_temp.getTime();
			cout << prntrng_prevtime_temp2.getDate(mode) << ".........";
			prntrng_moneytot_temp.printPhp();
		}
		cout << "total expenditure for the said range = ";
		prntrng_moneytot_temp2.printPhp();
		cout << endl << "done printing entries..." << endl << endl;	
	}
	else cout << "****no records for specified range****" << endl << endl;
}


//free functions for comparing expenditures
bool expDateLessThan(const Expenditure exp1, const Expenditure exp2){ return (exp1.getTime() < exp2.getTime()); }
//bool expDateLessThanEqual(const Expenditure exp1, const Expenditure exp2){ return (exp1.getTime() <= exp2.getTime()); }

void ExpVector::trialFctn(const string &startdate){
	cout << "now inside trial function lalala";
	vector<Expenditure>::iterator low;
	Expenditure prntrng_stexp_temp(startdate, "00:00:00", "Sunday", "Php",0,"none");
	//low = lower_bound(vecexp.begin(), vecexp.end(), prntrng_stexp_temp); //find initial entry
	//cout << endl;
	//low->printExpenditure();
	cout << endl << "try again";
	low = lower_bound(vecexp.begin(), vecexp.end(), prntrng_stexp_temp, expDateLessThan);
	low->printExpenditure();
	
	
}

////////////////////////////////// 
//temp files
//why is this flagging a redefintion error?
//Expenditure_temp::Expenditure_temp(const string curr, const float val, const string dc):price(curr,val),description(dc){
//	timestring_now();
//	etime = tmtoExptime();
//};



