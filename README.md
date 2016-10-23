--------------------------------------------------------------------
development of an application for convenient tracking of expense
--------------------------------------------------------------------

This repository is my first major project in C++, an expense tracker. Initial revisions will work on a console desktop application.
I am hoping that you guys will take some time to try out my program and comment on anything that can be improved on things such as
	- correct usage of object oriented paradigm
	- coding style and readability
	- usability of the program itself

****************************
  Program Functionality
****************************
	* Record an expense. The program will automatically tag the date of entry
	* Delete the last entry of the user
	* Summarize the current list of expense for a given range of date in one of the following options:
		- per entry
		- per day
		- per month
		- per year
	* automatic save and load of the database to a csv file to allow multiple console sessions
	
*********************
Summary of files
*********************
	The inc folder contains all the header files while the src folder contains all cpp files including main, 
	and the csv file for storing the database.  A makefile is included to be able to build easily from source.

	* main.cpp - main function
	* main_classes.cpp - contains the class declarations and method implementations
	* auxilary.cpp - contains all class and methods associated with getting the current time.
	* ui.cpp - contains the userinteface class to be used on main
	* source-file.csv - text file for storing the database
	* project_status.cpp - rough diary and documentation of the project
	* test_sequences.h - contains testing sequences that were used in intermediate testing of functions, might be a bit outdated...
	
	* userinterface.h - contains old references for doing the user interface
	
