#include <cstdlib>
#include <string>
#include <ctime>

//declare a global template holder current time, to avoid reallocating again, will be used frequently anyway
char time_buf[30];

void timestring_now(){
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    //note here, members of the time structure is in int, to convert this to string
    strftime(time_buf,30,"%x\t%A\t%X",now);
}

