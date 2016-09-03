#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;
//name auxillary for aux functions, but for now is used mainly for the date...
//technically the date can be an object, though what do we want to do with it? nothing really, just a tag for now, so just have it as a normal struct

//define custom type to be used for date, max value 65000, good enough for 177 years!
typedef unsigned short timedate_t;



//create our own time structure, make it much smaller than struct tm 36 bytes -> 16 bytes only!!!
struct ExpTime{
	timedate_t day;
	timedate_t month;
	timedate_t year;
	timedate_t wkday;
	timedate_t yday;
	timedate_t hour;
	timedate_t min;
	timedate_t sec;	
	
	const string stringWkday() const;
};

void timestring_now(); //get time
ExpTime tmtoExptime(); //convert the time from struct tm to ExpTime format
timedate_t stringtotimedate(const string &datestr, const size_t spos, char &delim, size_t &npos); //takes in a string format date and time, convert it to a single exptime member



