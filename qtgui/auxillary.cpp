//---------------------------------------------------------------------
//----Auxillary.cpp
//----Author: Jconstan
//-----auxillary functions but was used mainly for the date/time classes
//----------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include "auxillary.h"

using namespace std;
//declare a global template holder current time, to avoid reallocating again, will be used frequently anyway, use prefix g_
time_t g_t;
struct tm *g_now;

//-------------------------------------------------
//Free function implementations for time 
//-------------------------------------------------

//get time now and store struct tm to g_now
//borrowed code from popular sites
void getTimeNow(){
	g_t = time(0);   
    g_now = localtime( & g_t );    
}

//helper function that takes in a string format date and time, convert it to a single exptime member
//spos not using reference, argument can be npos+1 //npos is also updated as last position
timeDate_t stringToTimeDate(const string &dateStr, const size_t sPos, char &delim, size_t &nPos){
	nPos = dateStr.find(delim,sPos);
	string tmpStr = dateStr.substr(sPos,nPos-sPos);
	timeDate_t tmpTimeDate = static_cast<timeDate_t>(atoi(tmpStr.c_str()));
	return tmpTimeDate;
}

//-------------------------------------------------
// Class Exp Time methods
//-------------------------------------------------

//constructor from a time struct tm
ExpTime::ExpTime(tm *timeNow){								
	day = static_cast<timeDate_t>(timeNow->tm_mday);
	month = static_cast<timeDate_t>(timeNow->tm_mon+1);
	year = static_cast<timeDate_t>(timeNow->tm_year+1900);
	wkday = static_cast<timeDate_t>(timeNow->tm_wday);
    hour = static_cast<timeDate_t>(timeNow->tm_hour);
	min = static_cast<timeDate_t>(timeNow->tm_min);
	sec = static_cast<timeDate_t>(timeNow->tm_sec);	
}


//constructor from string date mm/dd/yyyy and time hh:mm:ss
ExpTime::ExpTime(const string date, const string time, const string wday){		
	
	size_t tmpNpos = 0;		//extract date
	char tmpDelim = '/';
	month = stringToTimeDate(date,0,tmpDelim,tmpNpos);
	day = stringToTimeDate(date,tmpNpos+1,tmpDelim,tmpNpos);
	year = stringToTimeDate(date,tmpNpos+1,tmpDelim,tmpNpos);
	
	//exception routine here for invalid date
	if( (month > 12) || (day > 31) /*|| (month == 0) || (day == 0)*/ ) throw runtime_error("invalid date!!");
	
	
	tmpNpos = 0;			//extract time
	tmpDelim = ':';
	hour = stringToTimeDate(time,0,tmpDelim,tmpNpos);
	min = stringToTimeDate(time,tmpNpos+1,tmpDelim,tmpNpos);
	sec = stringToTimeDate(time,tmpNpos+1,tmpDelim,tmpNpos);
	
	wkday = getTimeDateWkday(wday);
}


//convert timeDate_t Wkday to string
const string ExpTime::getStringWkday() const{
	
	switch(wkday){	
		case 1:  return "Monday";
		case 2:  return "Tuesday";
		case 3:  return "Wednesday";
		case 4:  return "Thursday";
		case 5:  return "Friday";
		case 6:  return "Saturday";
		default: return "Sunday";
	}
}


//convert string Wkday to timeDate_t
timeDate_t ExpTime::getTimeDateWkday(const string &wday){
	
	if(wday == "Monday") return 1;
	else if(wday=="Tuesday") return 2;
	else if(wday=="Wednesday") return 3;
	else if(wday=="Thursday")  return 4;
	else if(wday=="Friday") return 5;
	else if(wday=="Saturday")  return 6;
	else return 7;
}


//get date in string, format depends on mode: perDay, month, year, or per entry
const string ExpTime::getDate(dateMode_t mode) const{
	stringstream getdate_ss_temp0, getdate_ss_temp1, getdate_ss_temp2, getdate_ss_temp3;
	getdate_ss_temp0 << setfill('0') << setw(2) << month << "/" << setw(2) << day << "/" << year;
	getdate_ss_temp1 << setfill('0') << setw(2) << month << "-" << year;
	getdate_ss_temp2 << year;
	getdate_ss_temp3 << getdate_ss_temp0.str() << "  " << getTime();
	
	switch(mode){
		case perMonth: return getdate_ss_temp1.str();
		case perYear: return getdate_ss_temp2.str();
		case perEntry: return getdate_ss_temp3.str();
		default: return getdate_ss_temp0.str();
	}

}


//get time in string hh:mm:ss
const string ExpTime::getTime() const{
	stringstream getdate_ss_temp;
	getdate_ss_temp << setfill('0') << setw(2) << hour << ":" << setw(2) << min << ":" << setw(2) << sec;
	return getdate_ss_temp.str();	 
}



void ExpTime::printExpTime(){
	cout << getDate() << "  ";
	cout << std::setfill(' ') << std::setw(10) << getStringWkday() << "  ";
	cout << getTime();
}


//note the in mode 3, always return false to iterate/print per entry
const bool ExpTime::lessThan(const ExpTime &o, dateMode_t mode){
	switch(mode){
		case perMonth: return (getMonthsEffective() < o.getMonthsEffective());
		case perYear: return (getYears() < o.getYears());
		case perEntry: return false;
		default: return (getDaysEffective() < o.getDaysEffective());
	}
}

const bool ExpTime::isEqual(const ExpTime &o, dateMode_t mode){
	switch(mode){
		case perMonth: return (getMonthsEffective() == o.getMonthsEffective());
		case perYear: return (getYears() == o.getYears());
		case perEntry: return false;
		default: return (getDaysEffective() == o.getDaysEffective());
	}
}





