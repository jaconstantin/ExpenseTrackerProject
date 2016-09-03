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