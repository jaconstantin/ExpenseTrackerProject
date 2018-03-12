#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#include <cctype>


//note here, to avoid the conflict in compiling when including the same header file

#ifndef __MAIN_CLASSES
#include "main_classes.h"
#define __MAIN_CLASSES 
#endif

#ifndef __AUXILLARY
#include "auxillary.h"
#define __AUXILLARY 
#endif

#include "ui.h"

using namespace std;

char extern g_time_buf[30];
time_t extern g_t;
struct tm extern *g_now;


int main(void){
	
	
//////////////////////
///in this UI, all entries are loaded and stored from a single csv file, source-file.csv
/////////////////////	

	UI session1;
	session1.launchUI();

	return 0;	
}


//add a comment as first commit