#include <iostream>
#include <fstream>
#include <cstdlib>
#include "main_classes.h"

using namespace std;

void PhPeso::printphp(){
    cout << currency << value << endl;
}

PhPeso PhPeso::operator+(const PhPeso o){
    PhPeso tmp;
    tmp.value = value + o.value;
    return tmp;
}
    

    
    
void Expenditure::printExpenditure(){
    cout <<'"'<< description << '"' << "\t";
    price.printphp();
}

    
void ExpVector::addEntry(const string curr="Php", const float val=0, const string dc="none"){
    Expenditure tmp(curr,val,dc);
    vecexp.push_back(tmp);
}

PhPeso ExpVector::addTot(){
    PhPeso tmp;
    for(int i=vecexp.size(); i>0; --i) tmp = tmp + vecexp[i-1].getPrice();
    return tmp;
}
    
void ExpVector::printVctr(){
    for(int i=0; i<vecexp.size(); ++i) vecexp[i].printExpenditure();
}

void ExpVector::exportVctr(){
	ofstream f_dest("dest-file.csv");
	for(int i=0; i<vecexp.size(); ++i){
		PhPeso tmp = vecexp[i].getPrice();
		f_dest << tmp.currency << "," << tmp.value << ",";
		f_dest << vecexp[i].getDesc() << "\n";
	}
	f_dest.close();
}    


 void ExpVector::loadVctr(){
 	ifstream f_source("dest-file.csv");
 	string tmp_curr, tmp_desc, tmp_value;
 	while(f_source.good()){
 		getline(f_source,tmp_curr,',');
 		getline(f_source,tmp_value,',');
 		getline(f_source,tmp_desc,'\n');
 		addEntry(tmp_curr,atof(tmp_value.c_str()),tmp_desc);
	 }
	f_source.close();
	vecexp.pop_back(); //this function copies the null character as the last element, hence remove this
	
 }
