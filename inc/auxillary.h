//---------------------------------------------------------------------
//----Auxillary.h
//----Author: Jconstan
//-----auxillary functions but was used mainly for the date/time classes
//----------------------------------------------------------------------


//define here some test diagnositc enable variables
#ifndef test
//#define test 1
#endif

using namespace std;


typedef unsigned short timeDate_t;				    //define custom type to be used for date, max value 65000, good enough for 177 years!
enum dateMode_t{perDay,perMonth,perYear,perEntry};  //for summarizing entries


//Free functions dealing with time
void getTimeNow(); 
timeDate_t stringToTimeDate(const string &dateStr, const size_t sPos, char &delim, size_t &nPos); //helper function that takes in a string format date and time, 
                                                                                                  //convert it to a single exptime member

//create our own time structure for the expenditure class, make it much smaller than struct tm 36 bytes -> 16 bytes only!!!
class ExpTime{
	timeDate_t day;
	timeDate_t month;
	timeDate_t year;
	timeDate_t wkday;
	timeDate_t hour;
	timeDate_t min;
	timeDate_t sec;	
	
	//only called by member methods
	//convert string Wkday to timeDate_t
	timeDate_t getTimeDateWkday(const string &day);	
	
	const int getDaysEffective()const {return (static_cast<int>(month)*31)+(static_cast<int>(year)*366)+static_cast<int>(day);} 
	const int getMonthsEffective()const {return static_cast<int>(month)+(static_cast<int>(year)*12);}
	const int getYears() const {return (static_cast<int>(year)*12); }
	
public:
	ExpTime():day(0),month(0),year(0),wkday(0),hour(0),min(0),sec(0){}
	ExpTime(tm *timeNow);
	ExpTime(const string date, const string time, const string wday);
	
	const string getStringWkday() const;		           //convert timeDate_t Wkday to string
	const string getDate(dateMode_t mode=perDay) const;	   //get date in string, format depends on mode: perDay, month, year, or per entry
	const string getTime() const;			 			   //get time in string hh:mm:ss
	void printExpTime();
	
	//compare etime using date only
	const bool operator<(const ExpTime &o) const  {return getDaysEffective() < o.getDaysEffective();}
	const bool operator<=(const ExpTime &o) const {return getDaysEffective() <= o.getDaysEffective();}
	
	//create a more general function for comparing etime using day, month, or year, mode0 for day, 1 for month, 2 for year, 3 for per time/entry -- assumes no same entry can be done at the same time
	const bool lessThan(const ExpTime &o, dateMode_t mode);
	const bool isEqual(const ExpTime &o, dateMode_t mode);
	const bool lessThanEqual(const ExpTime &o, dateMode_t mode){return (lessThan(o,mode) || isEqual(o,mode));}
	
	//diagnostic functions onnly
	#ifdef test
	const int test_get_dayseffective() const{
		int testdayseffect_days_temp = getDaysEffective();
		return testdayseffect_days_temp;
	}
	#endif	
};





