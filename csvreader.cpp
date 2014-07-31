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


#include "csvreader.h"

//-----------------------------------------------------------------------------
// Let's overload the stream input operator to read a list of CSV fields (which a CSV record).
// Remember, a record is a list of doubles separated by commas ','.
istream& operator >> ( istream& ins, record_t& record )
{
     // make sure that the returned record contains only the stuff we read now
     record.clear();

     // read the entire line into a string (a CSV record is terminated by a newline)
     string line;
     getline( ins, line );

     // now we'll use a stringstream to separate the fields out of the line
     stringstream ss( line );
     string field;
     while (getline( ss, field, ',' ))
     {
	  // for each field we wish to convert it to a double
	  // (since we require that the CSV contains nothing but floating-point values)
	  stringstream fs( field );
	  double f = 0.0;  // (default value is 0.0)
	  fs >> f;

	  // add the newly-converted field to the end of the record
	  record.push_back( f );
     }

     // Now we have read a single line, converted into a list of fields, converted the fields
     // from strings to doubles, and stored the results in the argument record, so
     // we just return the argument stream as required for this kind of input overload function.
     return ins;
}

//-----------------------------------------------------------------------------
// Let's likewise overload the stream input operator to read a list of CSV records.
// This time it is a little easier, just because we only need to worry about reading
// records, and not fields.
istream& operator >> ( istream& ins, data_t& data )
{
     // make sure that the returned data only contains the CSV data we read here
     data.clear();

     // For every record we can read from the file, append it to our resulting data
     record_t record;
     while (ins >> record)
     {
	  data.push_back( record );
     }

     // Again, return the argument stream as required for this kind of input stream overload.
     return ins;  
}

