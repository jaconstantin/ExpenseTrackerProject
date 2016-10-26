--------------------------------------------------------------------
development of an application for convenient tracking of expense
--------------------------------------------------------------------

This repository is my first major project in C++, an expense tracker. Initial revisions will work on a console desktop application.
I am hoping that you guys will take some time to try out my program and comment on anything that can be improved on things such as
	- correct usage of object oriented paradigm
	- coding style and readability
	- usability of the program itself

****************************
  Program Version Overview
****************************

There are currently three versions of the program in this repository:

	* Base Expense Tracker for cash only transactions 
	* Cash and Credit Expense Tracker 
	* Base Expense Tracker with a GUI built using Qt Widgets through Qt Creator

****************************
   Base Expense Tracker
****************************
The first version is the base program that has the following functionaility:

	* Record an expense. The program will automatically tag the date of entry. The following information is stored:
		- expense description
		- expense Value
	* Delete the last entry of the user
	* Summarize the current list of expense for a given range of date in one of the following options:
		- per entry
		- per day
		- per month
		- per year
	* automatic save and load of the database to a csv file to allow multiple console sessions
	* a console UI with adequate user input error checking capabilities

The source code for this version can be found on the src and inc directories. A makefile is available to build on source. The object file and executable are also available but note that this was compiled on Cygwin. 

IMPORTANT NOTE HERE: this is the old version so to be able to compile properly, ui.cpp must be modified to include main_classes.h, instead of main_classes_v2.h

The following is a summary of the files that can be found on the src and inc directories

	* main.cpp - main function
	* main_classes.cpp and main_classes.h - contains the class declarations and method implementations
	* auxilary.cpp and auxillary.h - contains all class and methods associated with getting the current time.
	* ui.cpp and ui.h - contains the userinteface class to be used on main
	* source-file.csv - text file for storing the database
	* project_status.cpp - rough diary and documentation of the project
	* test_sequences.h - contains testing sequences that were used in intermediate testing of functions, might be a bit outdated...
	* makefile - makefile to build executable
	* userinterface.h - contains old references for doing the user interface
	* main.exe - executable file of the program built from cygwin

*********************************
 Cash and Credit Expense Tracker
*********************************

The updated version of the program added the feauture to support Credit Card Expenses. Per each expenditure, the following data is now needed:
	- expense description
	- expense value	 -> value of the item
	- Cash downpayment -> cash payment for the item
	
The time of entry and remaining credit Balance are automatically calculated by the program. To record a credit payment, it is suggested to use an expense Value of 0, and the cash payment to the 'cash downpayment field'. This is because the item value had already been recorded previously. This will allow an effective tracking of expenses in terms of:
	- expense value -> expenses incurred when procurring an item, either cash or credit
	- cash downpayment -> actual cash outs
	- credit balance -> remaining credit

All other functionalities including the UI were extended to support this larger data structure, such as summarizing the total expense, cash payments, and credit balance across a date range. 

The updated source code for this version can be found on the 'update' directory. Note that it utilizes some of the code from the base 'src' and 'inc' directory of the base version.

	*main_classes_v2.cpp and main_classes_v2.h - an updated version of main_classes.h to support the extended class for credit information
	*ui_v2.cpp - an updated version of the UI to support the extended class. Note that this uses the same /inc/ui.h as the base version
	*main_v2.cpp - an updated version of main to add the correct v2 headers
	*source-file-credit.csv - a csv file that stores the credit expenditure database
	*makefile_credit - makefile to generate executable for this version
	*main_credit.exe - executable file built from cygwin
	*test_sequences_credit.h - repository for test sequences
	
It is also good to point out that the updated program is capable of supporting both Cash only and Cash and Credit Expenses. This is done by simply using the ui.cpp of the base version (/src/ui.cpp instead of /update/ui_v2.cpp). to support this, other files can be found on the 'update' folder

	*makefile - generate executable for cash only tracker using the updated code
	*source-file.csv - own copy of csv that stores cash expenditure database
	*main.exe - executable file built from cygwin

*************************************
   Base Expense Tracker with qt GUI
*************************************

For a much easier use of the program, a GUI built from Qt is currently being developed. The main goal is to build methods and routines that the will properly interface the front end Widget-based GUI to the back end code, which is the original cpp files for the console based expense tracker. Unfortunately, minor modifications were needed on the original base code. Hence, the 'qtGUI folder contains its own version of main_classes.cpp and auxillary.cpp. 

The source code is found on the folder 'qtGUI'. Note that this GUI  is built using Qt Creator. There are no exe available in the repository, but the code as it is can be compiled and build in Qt Creator. 



***********************************
Implementation Details: Base Program
***********************************
The Base Expense tracker was built using object oriented paradigm of C++. The main class Expenditure was built from a hierarchy of classes: PhPeso, ExpTime, and Description.

The Money class is named PhPeso with fields currency and value. Initially, it only supports Philippine Peso as a currency but it is intended to extend this to support other currencies. The value is assigned a float, which is unfortunately not that accurate and should be fixed if time permits. The +operator was overloaded for convenience.

The time information was given a custom class named ExpTime. The motiviation is to have a much smaller time strucutre as compared to the standard struct tm, in case there will be millions of expenses. Its methods allows it to have constructors with String format arguments, which are then converted to its own custom data types. It also supports comparing dates with varying accuracy from absolute time, to comparing day, month, or just a year, which was very useful in summarizing the expense data in various date Modes.

The description compontent of the expense is a simple std string class.

To handle a collection of Expenditure, a new class named ExpVector was built. It makes use of Vector form the STL as container for Expenditure. This is to utilize its own memory management feautures and other built-in functions. Its iterator was very useful in creating the printVctrRange function, which prints the entries across a specified range of date. File operations Export and Load Vector were added to allow database storage to a csv file.

A console ui class was implemetned for the user interface. This class contains convenient functions in checking the input format of the user. Furthermore, for the sake of exercise, some of ExpVector methods used exceptions for error handling and detection. 

The base program was tested using manual testing only. A comprehensive test sequence was stored in test_sequences.h. However, some of it might not be updated due to the code clean up that I've performed.


***********************************************
Implementation Details: Credit Expense Tracker
***********************************************
The main objective for the major update is to be able to utilize the use of inheritance and Polymorphism. The idea is to let the user choose if he wants a cash only or a cash and credit expense tracker. The advantage is that a cash only tracker is more space efficient, as the latter has two additional PhPeso components.

The Expenditure Class was extended and created CreditExpenditure which contains additional fields: Cashpayment and Credit Balance. 
The goal was to support both Expenditure and CreditExpenditure with minimal function/method additions. Hence, some methods of Expenditure were added and modified such that it is easily extendable by the inherited class.

the ExpVector class was modified to contain a ptr to Expenditure, such that it can hold either Expenditure or CreditExpenditure. Its methods were also modified. Most methods contain similar routines and  a call to a virtual function that depends weather the pointer points to an Expenditure or CreditExpenditure. This way, the ExpVector routines is able to support both base and inherited class.

In terms of the ui, very minimal changes were required. For one, an additional user input is needed to put in the cash payment information, and the rest is the same. 













	
	
