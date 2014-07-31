///////////////////////////////////////////////////
// CSV to Float Reader				 //
// 						 //
// Written by:					 //
// http://www.cplusplus.com/user/Duoas/		 //
// taken from:					 //
// http://www.cplusplus.com/forum/general/17771/ //
// 						 //
// 2009						 //
///////////////////////////////////////////////////


#ifndef CSVREADER_H
#define CSVREADER_H 1

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

typedef vector <double> record_t;
typedef vector <record_t> data_t;

istream& operator >> ( istream& ins, record_t& record );
istream& operator >> ( istream& ins, data_t& data );

#endif // CSVREADER_H




