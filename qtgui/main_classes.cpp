//---------------------------------------------------------------------
//----main_classes.cpp
//----Author: Jconstan
//-----contains the main class methods of Expenditure
//-----version for Qt, need added functions for output display
//-----------printVctrRange was modified to output to Qt Widgets
//----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

#ifndef __MAIN_CLASSES
#include "main_classes.h"
#define __MAIN_CLASSES
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

//print Money to a string
string PhPeso::getPhp(){
	
	stringstream tempStream;
	tempStream << getCurrency() << std::fixed << std::setprecision(2) << std::setfill(' ') 
	           << std::setw(10) << getValue() << "    ";
			   
	return tempStream.str();
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
	price.printPhp(); cout << "    ";
    cout <<'"' << std::setfill('.') << std::setw(30)<< description << '"';
	cout << endl;
}


//print to string
string Expenditure::getExpenditure() { 
	stringstream tempStream;
	
	tempStream << etime.getDate() << "  "
	           << std::setfill(' ') << std::setw(10) << etime.getStringWkday() << "  "
	           << etime.getTime() << "  ";
	
	tempStream << price.getCurrency() << std::fixed << std::setprecision(2) << std::setfill(' ') 
	           << std::setw(10) << price.getValue() << "    ";
	
	tempStream << '"' << std::setfill('.') << std::setw(30) << description << '"';
		
	return tempStream.str();
	
}   


//----------------------------------------
//Exp Vector Method implementations
//-----------------------------------------

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


//delete last entry
void ExpVector::dropEntry(){
	emptyExcept();	//throw exception and abort if vector is empty
	vecexp.pop_back(); 
}  


//print all entries    
void ExpVector::printVctr(){
    for(int i=0; i<vecexp.size(); ++i) vecexp[i].printExpenditure();
}


//export current content of a vector to a csv file 
void ExpVector::exportVctr(const char* fName){
	ofstream fDest(fName);
	for(int i=0; i<vecexp.size(); ++i){
		PhPeso tmpPrice = vecexp[i].getPrice();	
		ExpTime tmpTime = vecexp[i].getTime();
		
		fDest << tmpTime.getDate() << ",";
		fDest << tmpTime.getTime() << ",";
		fDest << tmpTime.getStringWkday() << ",";	
		//fDest << tmpPrice.getCurrency() << "," << tmpPrice.getValue() << ",";
		fDest << vecexp[i].getPrice().getCurrency() << "," << vecexp[i].getPrice().getValue() << ",";
		fDest << vecexp[i].getDesc() << "\n";
	}
	fDest.close();
}    


//load CSV contents to active ExpVector
void ExpVector::loadVctr(const char* fName){
 	ifstream fSource(fName);
	
	if(fSource) //verify if file was opened succesffully
	{
		string tmpStr[6];
		while(fSource.good())
		{
			for(int x=0; x<5; ++x) getline(fSource,tmpStr[x],',');
			getline(fSource,tmpStr[5],'\n');		
			//tmpStr[5] = tmpStr[5].substr(0,tmpStr[5].size()-1); //this line is needed to remove the exta space for source files written manually in excel... once the program is run, and the vector is stored back to the file, this extra space will no longer exist	
			addEntry(tmpStr[0], tmpStr[1], tmpStr[2], tmpStr[3], atof(tmpStr[4].c_str()), tmpStr[5]);
		}
		fSource.close();
		vecexp.pop_back(); //loadVctr copies the null character as the last element, hence remove this last element
	}
	
	else
	{
		cout << endl << "**************************" << endl;
		cerr << "Warning, could not read from source-file.csv, no data was loaded!\n";
	}
}


//print entries within specified range of date depending on mode: 0 per day, 1 per month, 2 per year, 3 per entry
//to make this compatible with Qt GUI, instead of printing to cout, just return the string...
string ExpVector::printVctrRange(const string &startDate, const string &endDate, const dateMode_t &mode){
	
	emptyExcept();			                                                  //throw exception and abort if vector is empty
	stringstream tmpStringBuf;

	Expenditure tmpStartExp(startDate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure tmpEndExp(endDate, "00:00:00", "Sunday", "Php",0,"none");
	Expenditure tmpPrevExp("00/00/2500","00:00:00","Sunday","Php",0,"none");  //ensures that the loop will start
	
	PhPeso tmpMoneyTot, tmpMoneyTot2;   
	int tmpFindFlag = 0;                                                      //check if a valid entry is returned
	
	
	//check if initial date is out of bounds
	Expenditure tmpLastExp = vecexp.back();
	if(!( tmpStartExp.getTime() <= tmpLastExp.getTime() )){
		tmpStringBuf << "****no records for the specified range****" << endl << endl;
		return tmpStringBuf.str();
	}
	
	
	//find initial entry at StartDate with lower bound using function pointer
	vector<Expenditure>::iterator low;
	low = lower_bound(vecexp.begin(), vecexp.end(), tmpStartExp, expDateLessThan); 
	
	
	//iterate database until endDate
	for(low; (low->getTime() <= tmpEndExp.getTime()); ++low){
		tmpFindFlag = 1; 		                                  //found at least 1 entry
		
		ExpTime tmpCurrTime = low->getTime();
		ExpTime tmpPrevTime = tmpPrevExp.getTime(); 
		tmpMoneyTot2 =  tmpMoneyTot2 + low->getPrice();            //accumulate grand total
		
		
		 //if same day/month/year/entry, accumulate total
		if(tmpCurrTime.lessThanEqual(tmpPrevTime,mode)) tmpMoneyTot = tmpMoneyTot + low->getPrice();   
		else{                                                      //next date
		
			if(mode==perEntry) tmpStringBuf << low->getExpenditure() << endl;       //print by entry always go to this statement
			else{
	 			tmpStringBuf << tmpPrevTime.getDate(mode) << ".........";           //print corresponding date 
				tmpStringBuf << tmpMoneyTot.getPhp() << endl;                       //print accumulated total
			   	tmpMoneyTot = low->getPrice();                                      //reset total count
			}
		}
		tmpPrevExp = *low;
		
		if( (low+1) == vecexp.end()) break;		                   //also need to indicate a stop when we go out of bounds
		
	}
	
	if(tmpFindFlag==1){ 	//for queries with only 1 entry
		//no need for this statement in mode 'perEntry', since its bool function always return false, hence, always printsexpenditure per entry
		if(mode!=perEntry){
			ExpTime tmpPrevTime = tmpPrevExp.getTime();
			tmpStringBuf << tmpPrevTime.getDate(mode) << ".........";
			tmpStringBuf << tmpMoneyTot.getPhp() << endl;
		}
		tmpStringBuf << endl << "total expenditure for the said range = ";
		tmpStringBuf << tmpMoneyTot2.getPhp();
		tmpStringBuf << endl << "done printing entries..." << endl << endl;	
	}
	else tmpStringBuf << "****no records for specified range****" << endl << endl;
	
	return tmpStringBuf.str();
}


//-------------------------------------------
//for Qt output
//-------------------------------------------
string ExpVector::getExpenditure(int index){
	stringstream tempStream;
	
	tempStream << vecexp[index].getTime().getDate() << "  "
	           << std::setfill(' ') << std::setw(10) << vecexp[index].getTime().getStringWkday() << "  "
	           << vecexp[index].getTime().getTime() << "  ";
	
	tempStream << vecexp[index].getPrice().getCurrency() << std::fixed << std::setprecision(2) << std::setfill(' ') 
	           << std::setw(10) << vecexp[index].getPrice().getValue() << "    ";
	
	tempStream << '"' << std::setfill('.') << std::setw(30) << vecexp[index].getDesc() << '"';
		
	//tempStream << vecexp[index].printExpenditure();
	return tempStream.str();
}


//-------------------------------------------
//free functions for comparing expenditures
//--------------------------------------------

bool expDateLessThan(const Expenditure exp1, const Expenditure exp2){ return (exp1.getTime() < exp2.getTime()); }






