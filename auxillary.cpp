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
char g_time_buf[30];
time_t g_t;
struct tm *g_now;

void timestring_now(){
	g_t = time(0);   // get time now
    g_now = localtime( & g_t );    
    strftime(g_time_buf,30,"%x\t%A\t%X",g_now);   //note here, members of the time structure is in int, to convert this to string
    //cout << g_now->tm_wday;
}

ExpTime::ExpTime(tm *time_now){
	day = static_cast<timedate_t>(time_now->tm_mday);
	month = static_cast<timedate_t>(time_now->tm_mon+1);
	year = static_cast<timedate_t>(time_now->tm_year+1900);
	wkday = static_cast<timedate_t>(time_now->tm_wday);
    hour = static_cast<timedate_t>(time_now->tm_hour);
	min = static_cast<timedate_t>(time_now->tm_min);
	sec = static_cast<timedate_t>(time_now->tm_sec);	
}

ExpTime::ExpTime(const string date, const string time, const string wday){
	size_t expenditure_tmp_npos = 0;
	char expenditure_tmp_delim = '/';
	month = stringtotimedate(date,0,expenditure_tmp_delim,expenditure_tmp_npos);
	day = stringtotimedate(date,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	year = stringtotimedate(date,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	
	//exception routine here for invalid date
	if( (month > 12) || (day > 31) ) throw runtime_error("invalid date!!");
	
	expenditure_tmp_npos = 0;
	expenditure_tmp_delim = ':';
	hour = stringtotimedate(time,0,expenditure_tmp_delim,expenditure_tmp_npos);
	min = stringtotimedate(time,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	sec = stringtotimedate(time,expenditure_tmp_npos+1,expenditure_tmp_delim,expenditure_tmp_npos);
	
	wkday = timedayWkday(wday);
}

timedate_t ExpTime::timedayWkday(const string &wday){
	
	if(wday == "Monday") return 1;
	else if(wday=="Tuesday") return 2;
	else if(wday=="Wednesday") return 3;
	else if(wday=="Thursday")  return 4;
	else if(wday=="Friday") return 5;
	else if(wday=="Saturday")  return 6;
	else return 7;
}


const string ExpTime::getDate(int mode) const{
	stringstream getdate_ss_temp0, getdate_ss_temp1, getdate_ss_temp2, getdate_ss_temp3;
	getdate_ss_temp0 << setfill('0') << setw(2) << month << "/" << setw(2) << day << "/" << year;
	getdate_ss_temp1 << setfill('0') << setw(2) << month << "-" << year;
	getdate_ss_temp2 << year;
	getdate_ss_temp3 << getdate_ss_temp0.str() << "  " << getTime();
	
	switch(mode){
		case 1: return getdate_ss_temp1.str();
		case 2: return getdate_ss_temp2.str();
		case 3: return getdate_ss_temp3.str();
		default: return getdate_ss_temp0.str();
	}

/*
	stringstream getdate_ss_temp;
	switch(mode){
		case 1: getdate_ss_temp << setfill('0') << setw(2) << month << "-" << year;
				break;
		case 2: getdate_ss_temp <<  year;
				break;
		default: getdate_ss_temp << setfill('0') << setw(2) << month << "/" << setw(2) << day << "/" << year;
				break;	
	}
	return getdate_ss_temp.str();
*/	
}

const string ExpTime::getTime() const{
	stringstream getdate_ss_temp;
	getdate_ss_temp << setfill('0') << setw(2) << hour << ":" << setw(2) << min << ":" << setw(2) << sec;
	return getdate_ss_temp.str();	 
}

const string ExpTime::stringWkday() const{
	
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

void ExpTime::printExpTime(){
	cout << getDate() << "  ";
	cout << stringWkday() << "  ";
	cout << getTime();
}


//note the in mode 3, always return false to iterate/print per entry
const bool ExpTime::lessThan(const ExpTime &o, int mode){
	switch(mode){
		case 1: return (monthsEffective() < o.monthsEffective());
		case 2: return (getYears() < o.getYears());
		case 3: return false;
		default: return (daysEffective() < o.daysEffective());
	}
}

const bool ExpTime::isEqual(const ExpTime &o, int mode){
	switch(mode){
		case 1: return (monthsEffective() == o.monthsEffective());
		case 2: return (getYears() == o.getYears());
		case 3: return false;
		default: return (daysEffective() == o.daysEffective());
	}
}



//for the input, use references to avoid making an extra copy, except for spos, since we will use npos as its input argument
//note that this function will also update npos, which is the last delimiter position
timedate_t stringtotimedate(const string &datestr, const size_t spos, char &delim, size_t &npos){
	npos = datestr.find(delim,spos);
	string stmd_tmp_str = datestr.substr(spos,npos-spos);
	timedate_t stmd_tmp_timedate = static_cast<timedate_t>(atoi(stmd_tmp_str.c_str()));
	return stmd_tmp_timedate;
}


