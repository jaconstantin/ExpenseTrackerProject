#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
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


ExpTime tmtoExptime(){
	ExpTime tmp;
	tmp.day = static_cast<timedate_t>(g_now->tm_mday);
	tmp.month = static_cast<timedate_t>(g_now->tm_mon+1);
	tmp.year = static_cast<timedate_t>(g_now->tm_year+1900);
	tmp.wkday = static_cast<timedate_t>(g_now->tm_wday);
    tmp.hour = static_cast<timedate_t>(g_now->tm_hour);
	tmp.min = static_cast<timedate_t>(g_now->tm_min);
	tmp.sec = static_cast<timedate_t>(g_now->tm_sec);	
	return tmp;
}


//for the input, use references to avoid making an extra copy, except for spos, since we will use npos as its input argument
//note that this function will also update npos, which is the last delimiter position
timedate_t stringtotimedate(const string &datestr, const size_t spos, char &delim, size_t &npos){
	npos = datestr.find(delim,spos);
	string stmd_tmp_str = datestr.substr(spos,npos-spos);
	timedate_t stmd_tmp_timedate = static_cast<timedate_t>(atoi(stmd_tmp_str.c_str()));
	return stmd_tmp_timedate;
}


