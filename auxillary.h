#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <stdexcept>

//define here some test diagnositc enable variables
#ifndef test
//#define test 1
#endif

using namespace std;
//name auxillary for aux functions, but for now is used mainly for the date...
//technically the date can be an object, though what do we want to do with it? nothing really, just a tag for now, so just have it as a normal struct

//define custom type to be used for date, max value 65000, good enough for 177 years!
typedef unsigned short timedate_t;
//enum day_t{Monday=1,Tuesday=2,Wednesday=3,Thursday=4,Friday=5,Saturday=6,Sunday=7}; //special enumtype for encoding wkday


//create our own time structure, make it much smaller than struct tm 36 bytes -> 16 bytes only!!!
//in the future, maybe make this an object? 
	//the point of data encapsulation is to make the implementation hidden to the user
	//hence, the user is expected to use the function through a limited set of public methods/members, such as view data through a print function... etc...
	//for this case, can make the time struct private, then maybe the public interface is print date
	//also a protected function for writing the time and date can be implemented by using standard strings as argument

class ExpTime{
	timedate_t day;
	timedate_t month;
	timedate_t year;
	timedate_t wkday;
	timedate_t hour;
	timedate_t min;
	timedate_t sec;	
	
	timedate_t timedayWkday(const string &day);
	const int daysEffective()const {return (static_cast<int>(month)*31)+(static_cast<int>(year)*366)+static_cast<int>(day);} //only called by memebr functions
	const int monthsEffective()const {return static_cast<int>(month)+(static_cast<int>(year)*12);}
	const int getYears() const {return (static_cast<int>(year)*12); }
	

public:
	ExpTime():day(0),month(0),year(0),wkday(0),hour(0),min(0),sec(0){}
	ExpTime(tm *time_now);
	ExpTime(const string date, const string time, const string day);
	
	const string stringWkday() const;
	const string getDate(int mode=0) const;
	const string getTime() const;
	void printExpTime();
	
	//compare etime using date only
	const bool operator<(const ExpTime &o) const  {return daysEffective() < o.daysEffective();}
	const bool operator<=(const ExpTime &o) const {return daysEffective() <= o.daysEffective();}
	
	//create a more general function for comparing etime using day, month, or year, mode0 for day, 1 for month, 2 for year, 3 for per time/entry -- assumes no same entry can be done at the same time
	const bool lessThan(const ExpTime &o, int mode);
	const bool isEqual(const ExpTime &o, int mode);
	const bool lessThanEqual(const ExpTime &o, int mode){return (lessThan(o,mode) || isEqual(o,mode));}
	
	//diagnostic functions onnly
	#ifdef test
	const int test_get_dayseffective() const{
		int testdayseffect_days_temp = dayseffective();
		return testdayseffect_days_temp;
	}
	#endif	
};

void timestring_now(); //get time

//note, think about making these functions as member function, especilaly ExpTime
ExpTime tmtoExptime(); //convert the time from struct tm to ExpTime format
timedate_t stringtotimedate(const string &datestr, const size_t spos, char &delim, size_t &npos); //takes in a string format date and time, convert it to a single exptime member



