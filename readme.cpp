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
	
	
	
	


