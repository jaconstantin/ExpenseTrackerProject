//Rev1

//this is the first attempt to create the budget management app
//here, the main fork is to use a linked list (instead of a dynamic array) for the object container of expenditures
//i read that linked list has a couple of advantages,
    //efficient memory allocation, only allocate upon insertion
    //easy to insert between elements, no need to reallocate memory
    //but, has difficulty with random access of elements, as you need to traverse the pointers
    //some says that it can have advantage in sorting algorithms, where you need to insert a large number of elements at the middle
    //reordering the sequence will simply involve repointing the pointers
    //though, the elements is distributed in a non contagious memory space
//in contrast, a dyanmic array, especially a vector, handles memory additions by allocating an extra amount of space every time a space runs out
    //for a dynamic array, to increase its size, a new memory is allocated and the contents of the old array is copied into
    //the STL allocaates extra space, to avoid the need for reallocation every time an insertion occurs
    //this has the penalty of memory allocation efficiency, as an extra memory needs to be allocated everytime
    //though, it has the advantage of not using extra space for the pointer, and allows indexing for random acces of elements
    //furthermore, it is located in contiguous mem locations so ideally faster travesing/iterating all thru=ough out
    //perfect if we only need to insert at the end, as inserting a the middle will definetly need reallocation or reassignment
    
    //aslo want to add here, the beauty of vector, wherein its contents are stored on the heap - taken care of by the class, yey!
    
//so for practice purposes, i try to create a linked list as an object container for fun
//i also made LnkExp class as a friend class to the smaller object units for simplicity..


//August 3, 2016
//This is the version of the release
//basic functionalities only, add entry, delete entry, opertion always at the end of the vector
//also supports a simple import or export to text file
//also, the function prototype for automatically getting the time is added...
//now, lets move into the next revision


//August 3, 2016
//Rev1.1

//for now, let us assume that we only have a one big vector of data... stored chronollogically

//first addition is to add the data/time info on the entries, as well as categories?
	//best way to handle the Day, Month, Year, Dayweek, week?, time?
	//in the text file, it is best to let it be a single string? 08/03/2016 \t Wednesday \t 21:14:00
	//how about in the struct? -> important here is the date because i want to use them to find data... 
		//idea is to put in a data from/to, and return all values
		//hmm.. should i create my own time class? -> better convert it to days from 1900...
		//or just use the normal standard...
		//also, if in the future we would like to add functionality such as return by day, dayweek, week, month, then better have their own fields, can use enum for those...
//for now, let us put a default 

//so action item is to first type define a specific time structure to be used for expense vector 


//ExpVector now has its own time member, though it is still in raw format
//next do a nice print function that wull show everythin
//then do a nice print file function that is both nice to shpw, while preserving all information..
	//here maybe we can overwrite the << operator of the time struct,... but no, it is not worth it!! just do a manual print function, use a weekday decode function
	//export vector function also done!
//next step, a vector load function? then some search algos?
	//for loading from spread sheet, we need to create a new add entry and new Expenditure constructor that will have the time as another input arguments
	//currently, loadvectro_Tmp simply reads each entry in the csv into a string array, each string is then passed as the argument to add entry
	//this in turn allow add entry to forward the string inputs to a new expenditure constructor
	//now in the new expenditure function, a new function named stringtotimedate is used to extract 8/5/2016 and 23:54:23 into their own respecitve Exptime structures
	
//NOTE this is the next current workint verion 1.1... though note that there are still a couple of things needed to clean up
	//the include of header files is a bit messy - ok
	//the constructor of Expenditure is in .cpp instead of a .h -ok
	//copy load vector temp to load vector and delete the temp class and functions. -ok
	//the last is the tmp variable names, which ideally should be function_tmp_type
	//committing this initial working revision
	


//////////////////////////////////////////////////////////
///Now, let us move on to Rev 1.2!!!
///
///Set the goals for this Rev
/// =have useful summarizing fucntions for our database
///1. return entries given a specified range of date
///2. return the total expenditure for the specified date range
////////////////////////////////////////////////////////////

//so how do we plan on implementing this
//1. currently, we are to store all data in single vector, wonder if it is wise to save an array of pointers to mark some check points..
//2. if we want to print data ex per day, per month, per year, then maybe it is also wise to have new data structures for them
//3. though 2 does not seem necessary for the target functionalities of rev 1.2



//also think about what can be inherited eg: cash expense from card expense
//both have desc, time, value
//key diff between the two? payment terms, whereas cash is one time, while card can be staggard
	//hence card expenditure will have extra fields paid amount, remaining balance, interest rate
	//the second difference is how it is reflected on the cash flow
	//cash payment is just straight forward addition and total..
	//whereas for card, only the downpayment will be added to the total, and the remaining credit will go to a separate function
	//let us put some interesting credit function, such as auto increment of interests...
//BIG ASS question here... can we join different sub classes in one vector? maybe not...


////////////////////////////////////////////////////////////////
/// now what are we going to do
///////////////////////////////////////////////////////////////
//1. yes currently, let us just use a single vector, then use the algorithm binary seacrch to look for the start date. then start iterating till we reach the end date
//2. note that algorithm binary search usually works with values onlym

//implementation list
//added exp time function, daytimes year
//then, added an override function for operator<, to be used for lower_bound function -> uses the operator< on the type pouitned to by the iterator
//this results in the need for temp expenditure objects, since that is where lower bound can work
//then did a simple loop function to return a range of date, through iterator iteration

//CAREFULLY test this, as there are still bugs on this eg: the operator< will stop only when element is greater than the value, so it will include the last out of bound entry
	//also, note the the .end iterator will return last, which is an invalid member - this occurs when you search an out of bounds date
	//another bug, not working with year yet...
		//alright, dayto years is in no way working - dayXyears, it should be day+(year*366) - FIXED!!

//note consider reimplementing daytimes year as another operator< overload

/////////////////////////////////////////////
///checkpoint for commit
/////////////////////////////////////////////////////

//to start changing the bugs, let us now create an operator< overload for etime...
//now etime has it own overload for operator<, comparing only date and not the timem
//modified operator< for expenditure, making use of etime <, makes more sense, but take note that expenditure is now compared via date
//added private function dayseffective(from year 0), only used by the operators..


//now, added a snippet for handling out of bound input, check this first before proceeding... done
//also changed the for loop for returning/printing the said expenditures
//also added out of bounds checking for the end date....

//////////////////////////
//now commit again
////////////////////////

//the final task is to make this a proper function of exp vector
//but now, i realize one big shit that must be added here - that is, the conversion between date and yday, and vice versa
//but, i don't really need an exact year day conversion so why not just drop the yday
	//calcualte the wait by using year*366 + month*31 + day -> adding extra in the multiplier will ensure
	//note that we need not remove yday as of now.... let us make it as part of the clean up
	//now changing how we compare date - simply change dayseffective function... very easy change
	//but now discovered one more bug, if we specify the same start and end date, what will happen?
		//it is good that it works! note: the for loop will first check the condition before starting to iterate
//it is now in a function!!

//few things to clean up - removal of yday in all of the things - looks ok 
//testing -> adding #ifdef include for in function diagnostics - currently doing this, trying to add it through an h file, seems not working flawlessly for dev
	//added complete diagnostic messages for the print range function enabled by the pre processor test...
	//to improve this implementation in the future... anyway note that this can also be replaced by the debugger
//also, compiling all the test sequences into one? - combined main test sequences, currently passing
//last comment here... currently naming of temporary function variables is functionname_type_temp# ->which can be improved by specifying a more specifi type name
	//eg prntrng_exp_temp -> prntrng_startexp_temp


/////////////////////////
////commit, final phase of rev 1.2, the total function
////////////////////////
//for now, let us just add the total at the end of print range function
//total function now done, unfortunately, the money data class has bugs - float, sometimes, the value gets rounded due to probably accuracy of floating points
//also, it will be better to ensure the print format to be off two decimal places...		
//Rev 1.2 is done!!!	
/////////////////////////


///////////////////////
//side note on data encapsulation
///////////////////////
//as mentioned, it aims to hide the function implementation to the user, and just expose the function/interface to it
//for example, class exp vector, the vector member is private as its implementation is not important for the user
//what the user wants is to be able to add entries, load/store from file, and print
//this is an example of data abstratction, using data without knowing how it is stored
//let us note that this is only made possible by having member functions because they are the only way to actually interface with the private data
//it is said that this will separate the properties of the data from its acutal implementation
//hence an object, containing both functions and related methods, for easier modelling of real objects


//now, i am not sure if my class hierarchy is of proper practice, the main object exp vectro is good bec it is based solely on an STL container
//furthermore, since this is the main object, as of now, all the rest of the class hierarchy is private regardless of its strucutre

//for expenditure, we know there is currency, value, description, and time, but we do not actually know how it is structured
//though we can create an expenditure, or print its contents
//for PhPeso or money, not really much here but it is really nice to create this as one structure
//furhtermore, it allows the convenience of using the addition operator overlaod for money
//can potentially extend this object

//also note the object comment for time, but do that in the future




///////////////////////
///end sidenote///////
////////////////////////


//////////////////////////////
//Moving on to Rev 1.3?
/////////////////////////////
//target functionality, is to have ability to summarize the expense per day, or per month
//have greatly though about this, but it seems that this can be done by extending the current iteration used by print range...
	//in the though process, one can think of having a pointer map, already containing the total per day and per month. as a result, we would not need to iterate per entry but at the cost of more storage
//for this rev, let us just extend the iteration process, see how to efficiently create the function structure...

//to summarize per day
	//again find the start iterator as is in print range...
	//per each element, accumulate the sum per day, and simply print, once the date had changed.
	
//1.added expenditure member function printDate
//2. now, printrangeday function is done - improved some of the parts from print by entry...

//printrangemonth can be done in a very similar function. the question is, can we combine this to have a single printrange function?



///////////////
//Rev 1.4
/////////////
//this rev requires a lot of work. Target is to have a single function for printvctr range, with the option to print by entry, by day, month, or year
//two ways of doing this
	//1. implement an exp time compare function, with argument to choose to compare by day, month, year etc...
		//let us start to do this
	//2. two, is to create multiple exptime subclasses, each with own overload for the operator< - not sure if this is a smart way to do inheritance...
		//this will need an interface to copy the time values from different subclasses, which i believe is not doable..

//first step, is making exptime a class
//1. modified exp time to be a class, now making constructors for it
//2. also creating prtinexptime function, now width formatting function
//3. now starting to reflect the exptime changes to the expenditure class, however need to determine something first
	//if i have a constructor PhPeso(int x=0, int y=0):x(a),b(a) -> will this be valid for the default constructor? PhPeso x1; - well yes, but i need to specify all?
	//so right now. it is really understandable why expenditure will not use a default constructor, because not all members are initiailized by ths construcotr
	//Expenditure::Expenditure(const string curr="Php", const float val=0, const string dc="none"):price(curr,val),description(dc){
	
	//now at export vector ->want to implement a new interface for ExpTime -> getTime, getDate, stringWkday that returns the neeed info as string. 
	//this way, the ExpTime class is now fully abstracted/encapsulated, as the user can use this class without knowing the timedate structure thingy...
	//printExpTime also changed to just use the new built in functions gettime and getDate.
	//export vector now looking good...
	
	//now on to store vector, again, new interface functions are needed, this time... by using a setter
	//currently fixing the new constructor of exp time, wherin the argumetns are string date, time, and wkday.. having problem with converting wkday to int...
	//now, changes are reflected on the new constructor for expenditure, note that i put default values here, so that it can also serve as the default constrcutor
	//also done with simple changes, loadvector now also working..!!
	
	//now working on print range day - also working, done!!
//now pause here, want to re-implement this function, to accomodate various comparison of time...
	//first and foremost, the operator< overload is mandatory for both ExpTime and Expenditure, as it is the needed criteria for the lower_bound function - in expenditure domain
	//besides that, we can fully operate on exptime only.. so let us make a function that will compare exptime in units of time, day, month, and year - done
	//now let us leave printrange, instead let us play with printrangeday
		//printrangeday now also working, did some mods on how ExpTime getDate is implemented, again implement the mode
		//however, some problem with printDate
		//finally done, Rev1.4!!


///////////////////////
///next Rev, 1.5
//////////////////////
//need to add another mode to printrangeday -> per entry, then replace/redefine definition of printrange
	//done by introducing mode 3, which will print per entry
	
//need to add total at the end of each summary = also done!
//this time, I would like to create the console UI
	//well a simple UI using main is not working - need a way to hanle an input of string.... as it seems that cin >> only takes up to the white space
	//actually, just need to google of a way to stream in a string with spaces, as Cin does not seem to be enough = review the char* argc, argc crap...
	
	
////////////////////
//start of branched, continuing rev 1.5, fixing UI, call this Rev 1.51	
////////////////////
//now, add entry is working done by using getline, instead of cin to have a user input of an entire sentence
//note the use of cin.ignore(), useful in cases wherein \n character is being unwillingly buffered...
//added function that upon exit, the current list is pushed back to the source-csv file
//big note here - this is the sole modification to main_classes.cpp wherein export vector is changed to export from dest-file to source-file
//now pushing the user interface back to userinterface.h

//list of things that can be improved in the UI
//1. error checking for inputs - try exceptions here?
//2. appearance... need more print lines to have a pretty nice text data presentation
//3. probably add an easier print data, wherein give the user the option to simply print all, instead of printing a range

//commit first as Rev 1.51
//////////////////////////////


/////////////////////////////////////
//Further notes for future work
////////////////////////////////////

//important change logs for merging with inheritance rev2 branched
//change1. is the added fix for loadvector function to be compatible with cygwin
//change2 is to have load and store vector to the same source.csv
//change3, ensure that UI code is in a separate header file



//though, want to do something to ensure that we don't compare time on the level of expeniture...
//furutre things to do: use Enum to define the mode, 0,1,2 - day, month, year
	//lastly, it seems that expenditure memebers are better off public - useless data encapsulation, as we are gettinge each of the members anyway
	//furthermore, php money class neeing more improvements, and can be a class of its own

