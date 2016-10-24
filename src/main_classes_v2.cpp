//---------------------------------------------------------------------
//----main_classes.cpp
//----Author: Jconstan
//-----contains the main class methods of Expenditure
//----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstring>

#include "main_classes_v2.h"

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

//define here some test diagnositc enable variables
#ifndef test
//#define test 1
#endif


using namespace std;

//global variables for time
time_t extern g_t;
struct tm extern *g_now;

//----------------------------------------
//PhPeso Method implementations
//-----------------------------------------


//print with format PhpXXXX.XX
void PhPeso::printPhp(){
    cout << currency;
	cout << std::fixed << std::setprecision(2) << std::setfill(' ') << std::setw(10) << value; //<< endl;
}

//convenience function
PhPeso PhPeso::operator+(const PhPeso o){
	PhPeso tmpMoney;
    tmpMoney.value = value + o.value;
    return tmpMoney;
}

PhPeso PhPeso::operator-(const PhPeso o){
	PhPeso tmpMoney;
    tmpMoney.value = value - o.value;
    return tmpMoney;
}

   
//----------------------------------------
//Expenditure Method implementations
//-----------------------------------------
   
   
//constructor for real time user input
Expenditure::Expenditure(const string curr="Php", const float val=0, const string dc="none"):price(curr,val),description(dc){
	getTimeNow();
	ExpTime exp_timenow_temp(g_now);
	etime = exp_timenow_temp;
}


void Expenditure::printExpenditure(){
	etime.printExpTime();
	cout << "  ";
	price.printPhp(); cout << "\t";
    cout <<'"' << std::setfill('.') << std::setw(30)<< description << '"';
	//cout << endl;
}


//print expenditure to string in csv format
string Expenditure::getCsvToString(){
	
	stringstream tmpStream;
	
	tmpStream << etime.getDate() << "," << etime.getTime() << ","
	          << etime.getStringWkday() << "," << price.getCurrency() << ","
	          << price.getValue() << "," << description;
	
	return tmpStream.str();
}


//----------------------------------------
//CreditExpenditure Method implementations
//Inherits from Expenditure
//all money member use same currency
//-----------------------------------------
//constructor for real time user input
CreditExpenditure::CreditExpenditure(const string curr="Php", const float val=0, const string dc="none", const float cpay=0):
	Expenditure(curr,val,dc),cashPayment(curr,cpay){
	
	getTimeNow();
	ExpTime exp_timenow_temp(g_now);
	etime = exp_timenow_temp;
	creditBalance = price-cashPayment;
	
}


//extend base class print function
void CreditExpenditure::printExpenditure(){	
	Expenditure::printExpenditure();
	cout << "\t"; cashPayment.printPhp(); 
	cout << "\t"; creditBalance.printPhp(); 
}


//extends base class store to string in csv format 
string CreditExpenditure::getCsvToString(){
	
	stringstream tmpStream;
	
	tmpStream << Expenditure::getCsvToString() << ","
			  << cashPayment.getValue() << ","
			  << creditBalance.getValue();
	
	return tmpStream.str();
}


//----------------------------------------
//Exp Vector Method implementations
//-----------------------------------------


//add entry, time=now, for real time user input
void ExpVector::addEntry(const string curr="Php", const float val=0, const string dc="none"){
	Expenditure *tmp = new Expenditure(curr,val,dc);
    vecexp.push_back(tmp);
}


//add entry with time record, for loading from csv file
void ExpVector::addEntry(const string date, const string time, const string wday, const string curr, const float val, const string dc){
	Expenditure *tmp = new Expenditure(date, time, wday, curr, val, dc);
	vecexp.push_back(tmp);
}


//real time user input for CreditExpenditure, use of polymorphism...
void ExpVector::addEntry(const string curr, const float val, const string dc, const float cpay){
	Expenditure *tmp = new CreditExpenditure(curr,val,dc,cpay);
    vecexp.push_back(tmp);
}

//loadVctr input for CreditExpenditure
void ExpVector::addEntry(const string date, const string time, const string wday, const string curr, 				   
		const float val, const string dc, const float cpay, const float cbalance){

	Expenditure *tmp = new CreditExpenditure(date, time, wday, curr, val, dc, cpay, cbalance);
	vecexp.push_back(tmp);		
}


/*
PhPeso ExpVector::addTot(){
    PhPeso tmp;
    for(int i=vecexp.size(); i>0; --i) tmp = tmp + vecexp[i-1].getPrice();
    return tmp;
}
*/


//delete last entry
void ExpVector::dropEntry(){
	emptyExcept();	                 //throw exception and abort if vector is empty
	free(vecexp[vecexp.size()-1]);   //deallocate pointer before pop
	vecexp.pop_back(); 
}  



//print all entries    
void ExpVector::printVctr(){
    for(int i=0; i<vecexp.size(); ++i){
		vecexp[i]->printExpenditure();
		cout << endl;
	} 
}



//export current content of a vector to a csv file, getCsvfunction for Expenditure or CreditExpenditure maybe called
void ExpVector::exportVctr(const char* fName){
	ofstream fDest(fName);
	
	for(int i=0; i<vecexp.size(); ++i){	
		fDest << vecexp[i]->getCsvToString();
		fDest << "\n";
	}
	
	fDest.close();
}    



//load CSV contents to active ExpVector
void ExpVector::loadVctr(const char* fName){
 	ifstream fSource(fName);
	
	string tmpStr1 = "source-file.csv";
	string tmpStr2 = fName;
	
	if(fSource) //verify if file was opened succesffully
	{
		string tmpStr[8];
		while(fSource.good())
		{	
			if(tmpStr1.compare(tmpStr2)==0){   //if source-file.csv, load an Expenditure						
				for(int x=0; x<5; ++x) getline(fSource,tmpStr[x],',');
				getline(fSource,tmpStr[5],'\n');		
				////please view Note jcImpt1
				addEntry(tmpStr[0], tmpStr[1], tmpStr[2], tmpStr[3], atof(tmpStr[4].c_str()), tmpStr[5]);
			}
			else{                              //if source-file-credit.csv, load a CreditExpenditure	
				for(int x=0; x<7; ++x) getline(fSource,tmpStr[x],',');
				getline(fSource,tmpStr[7],'\n');	
				
				addEntry( tmpStr[0], tmpStr[1], tmpStr[2], tmpStr[3], atof(tmpStr[4].c_str()), tmpStr[5], 
					atof(tmpStr[6].c_str()), atof(tmpStr[7].c_str()) );		
			}
		}
		fSource.close();
		dropEntry();		                   //loadVctr copies the null character as the last element, hence remove this last element
	
	}
	
	else
	{
		cout << endl << "**************************" << endl;
		cerr << "Warning, could not read from source-file.csv, no data was loaded!\n";
	}
}


//print entries within specified range of date depending on mode: 0 per day, 1 per month, 2 per year, 3 per entry
void ExpVector::printVctrRange(const string &startDate, const string &endDate, const dateMode_t &mode){
	
	emptyExcept();			                                                  //throw exception and abort if vector is empty

	Expenditure *tmpStartExp = new Expenditure(startDate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure *tmpEndExp = new Expenditure(endDate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure *tmpPrevExp = new Expenditure("00/00/2500","00:00:00","Sunday","Php",0,"none");  //ensures that the loop will start
	
	PhPeso tmpMoneyTot, tmpMoneyTot2;   
	int tmpFindFlag = 0;                                                      //check if a valid entry is returned
	
	
	//check if initial date is out of bounds
	Expenditure *tmpLastExp = vecexp.back();
	if(!( tmpStartExp->getTime() <= tmpLastExp->getTime() )){
		cout << "****no records for the specified range****" << endl << endl;
		return;
	}
	
	
	//find initial entry at StartDate with lower bound using function pointer
	vector<Expenditure*>::iterator low;
	low = lower_bound(vecexp.begin(), vecexp.end(), tmpStartExp, expDateLessThan);
	
	
	//iterate database until endDate, note low is a pointer to an expenditure pointer...
	for(low; ((*low)->getTime() <= tmpEndExp->getTime()); ++low){
		tmpFindFlag = 1; 		                                  //found at least 1 entry
		
		#ifdef test
		cout << "moneytot_temp = ";	
		tmpMoneyTot.printPhp();
		#endif
	
		ExpTime tmpCurrTime = (*low)->getTime();
		ExpTime tmpPrevTime = tmpPrevExp->getTime(); 
		tmpMoneyTot2 =  tmpMoneyTot2 + (*low)->getPrice();            //accumulate grand total
		
		
		 //if same day/month/year/entry, accumulate total
		if(tmpCurrTime.lessThanEqual(tmpPrevTime,mode)) tmpMoneyTot = tmpMoneyTot + (*low)->getPrice();   
		else{                                                      //next date
			if(mode==perEntry){
				(*low)->printExpenditure();                           //print by entry always go to this statement
				cout << endl;
			} 
			else{
	 			cout << tmpPrevTime.getDate(mode) << ".........";  //print corresponding date 
				tmpMoneyTot.printPhp(); cout << endl;              //print accumulated total
			   	tmpMoneyTot = (*low)->getPrice();                     //reset total count
			}
		}
		tmpPrevExp = *low;
		
		if( (low+1) == vecexp.end()) break;		                   //also need to indicate a stop when we go out of bounds
		
	}
	
	if(tmpFindFlag==1){ 	//for queries with only 1 entry
		//no need for this statement in mode 'perEntry', since its bool function always return false, hence, always printsexpenditure per entry
		if(mode!=perEntry){
			ExpTime tmpPrevTime = tmpPrevExp->getTime();
			cout << tmpPrevTime.getDate(mode) << ".........";
			tmpMoneyTot.printPhp(); cout << endl;
		}
		cout << "total expenditure for the said range = ";
		tmpMoneyTot2.printPhp();
		cout << endl << "done printing entries..." << endl << endl;	
	}
	else cout << "****no records for specified range****" << endl << endl;
	
}


//-------------------------------------------
//free functions for comparing expenditures
//--------------------------------------------

bool expDateLessThan(const Expenditure* exp1, const Expenditure* exp2){ return (exp1->getTime() < exp2->getTime()); }






