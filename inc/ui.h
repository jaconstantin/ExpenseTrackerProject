//---------------------------------------------------------------------
//----ui.h
//----Author: Jconstan
//-----contains the UI class for the userinterface
//----------------------------------------------------------------------

enum usrInput_t{cmd,date,currency,price};  //user input types

class UI{
	ExpVector expDatabase;			
	int userCmd;			   	           //current user command
	
	void printLines(const int n);
	void handleRunTimeError(runtime_error &error);			           //print errors for runtime exceptions
	bool checkCharInput(const char &in, const usrInput_t &inType);     //check format and white spaces of characters in user input, depends on input type
	string getUsrInput(usrInput_t inType=cmd, const int cmdLimit=4);   //get user input with error checks dependent on input type
	
public:
	UI();			                                                   //default constructor, initialize by loading source file to database
	int launchUI();
};

