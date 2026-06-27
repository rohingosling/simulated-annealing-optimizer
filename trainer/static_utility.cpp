//--------------------------------------------------------------------------------------------------------------------------------------
// Project:		Generic Console Application Platform (G-CAP).
// Application:	N/A
// Class:       StaticUtility
// Version:		1.3
// Date:        2015-07-10
// Author:		Rohin Gosling
//
// Description:
//
//   General purpose functions for console applications.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "static_utility.h"

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>

using namespace std;
using namespace std::chrono;	// We will be using some timming functions for measurement.

//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 1/1
//--------------------------------------------------------------------------------------------------------------------------------------

StaticUtility::StaticUtility ( )
{
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------------------------------------------

StaticUtility::~StaticUtility ( )
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - time_to_string
//
// Description:
//
// - Converst a high resolution time in milliseconds, to a string formatted as, HH:MM:SS.000.
//
// Arguments:   
//
// - time
//   High resolution time in miliseconds.
//
// Return Value:
//
// - Formsteed string. Teh string is formatted as, HH:MM:SS.000
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A string representing the formatted time has been compiled and returneed.
//
//--------------------------------------------------------------------------------------------------------------------------------------

// Overload 1/2

string StaticUtility::time_to_string ( long long time )
{
	return time_to_string ( time, true, true, true, true );
}

// Overload 2/2

string StaticUtility::time_to_string ( long long time, bool hours_enabled, bool minutes_enabled, bool seconds_enabled, bool milliseconds_enabled )
{
	// Declare constants.

	const string DELIMITER_HMS = ":";
	const string DELIMITER_MS  = ".";
	const char   PADDING       = '0';
	const int    WIDTH_HMS     = 2;
	const int    WIDTH_MS      = 3;
	
	// Declare local variables.

	stringstream time_string_stream;
	string       time_string;

	// Compute temporal components.

	long long total_seconds = time / 1000;
	long long hours         = total_seconds / 3600;
	long long minutes       = ( total_seconds / 60 ) % 60;
	long long seconds       = total_seconds % 60;
	long long milliseconds  = time % 1000;
	
	// Compile time string.		
	
	if ( hours_enabled )										time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << hours;		
	if ( hours_enabled && minutes_enabled )						time_string_stream << DELIMITER_HMS;
	if ( hours_enabled && !minutes_enabled && seconds_enabled )	time_string_stream << DELIMITER_HMS;
	if ( minutes_enabled )										time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << minutes;
	if ( minutes_enabled && seconds_enabled )					time_string_stream << DELIMITER_HMS;
	if ( seconds_enabled )										time_string_stream << setfill ( PADDING ) << setw ( WIDTH_HMS ) << seconds;
	if ( milliseconds_enabled )									time_string_stream << DELIMITER_MS;
	if ( milliseconds_enabled )									time_string_stream << setfill ( PADDING ) << setw ( WIDTH_MS )  << milliseconds;

	// Convert string stream to string, and return to caller.

	time_string = time_string_stream.str ();

	return time_string;
}

//--------------------------------------------------------------------------------------------------------------------------------------

long long StaticUtility::time_to_milliseconds ( long long time )
{
	long long milliseconds = time % 1000;
	return    milliseconds;
}

//--------------------------------------------------------------------------------------------------------------------------------------

__int64 StaticUtility::time_to_seconds ( long long time )
{
	long long total_seconds = time / 1000;
	long long seconds       = total_seconds % 60;
	return    seconds;
}

//--------------------------------------------------------------------------------------------------------------------------------------

__int64 StaticUtility::time_to_minutes ( long long time )
{
	long long total_seconds = time / 1000;
	long long minutes       = ( total_seconds / 60 ) % 60;
	return    minutes;
}

//--------------------------------------------------------------------------------------------------------------------------------------

__int64 StaticUtility::time_to_hours ( long long time )
{
	long long total_seconds = time / 1000;
	long long hours         = total_seconds / 3600;
	return    hours;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - random_seed
//
// Description:
//
// - Initialize and seed the random number generator.
//
// Arguments:   
//
// - N/A
//
// Return Value:
//
// - N/A
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - The random number generator has been seeded, and is ready to produce randome numbers.
//
//--------------------------------------------------------------------------------------------------------------------------------------


void StaticUtility::random_seed ()
{
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - random_between
//
// Description:
//
// - Generate a random number in the range, [a,b].
//
// Arguments:   
//
// - a
//   Lower bound.
//
// - b
//   Upper bound.
//
// Return Value:
//
// - A real random number in the range, [a, b].
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A real random number in the range, [a, b] has been generated and returned.
//
//--------------------------------------------------------------------------------------------------------------------------------------

double StaticUtility::random_between ( double a, double b )
{
	return 0.0;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - sleep
//
// Description:
//
// - Pause execution of the current thread for a specified number of miliseconds.
//
// Arguments:   
//
// - milliseconds:
//   - The number of miliseconds to pause execution for.
//
// Return Value:
//
// - N/A
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - The current thread will have paused execution for the number of seconds specified by the argument 'milliseconds'.
//
// - Exceution of the paused thread will have resumed after returning from the sleep function.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void StaticUtility::sleep ( const int milliseconds )
{
	this_thread::sleep_for ( chrono::milliseconds ( milliseconds ) );
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - get_max_length
//
// Description:
//
// - Return the length of the longest string in a list of strings.
//
// Arguments:   
//
// - stringList:
//   - A list of strings in the form of a vector.
//   - We will itterate through this list and look for the longest string.
//
// Return Value:
//
// - The length of the longest string in the list.
//
// Pre-Conditions:
//
// - A list of zero or more strings in the form of an STL vector <string>, should be pre-popilated for use.
//
// - In the case of an empty vecotor, the function returns zero.
//   
// Post-Conditions:
//
// - An integer representing the length of the longest string in the vector is returned to the caller.
//
// - The string list it's self is left unchanged.
//
//--------------------------------------------------------------------------------------------------------------------------------------

StaticUtility::Natural StaticUtility::get_max_length ( vector < string > string_list )
{
	// Set the length to zero by default.
	// If the list is empty, then the defualt value of 0 is returned.

	StaticUtility::Natural max_length { 0 };

	// For each string elment of the list.
	// - If the length of the string is greater than our current length,
	// - then update the current length to the newly discovered longest length,
	// - else just keep the lenght as it is.

	for each ( string s in string_list )
	{
		max_length = ( s.length ( ) > max_length ) ? s.length ( ) : max_length;
	}

	// Return the longest string length of all strings in the list.

	return max_length;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - to_upper
//
// Description:
//
// - Converts all characters in a string to upper case.
//
// Arguments:   
//
// - inputString:
//   The string we wish to convert.
//
// Return Value:
//
// - An all upper case copy of inputString..
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A new copy of the strings is created and converted to an all upper case verions of inputString.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::to_upper ( string inputString )
{
	// Create an upper case version of the input string.

	string upper_case_input_string ( inputString );
	transform ( upper_case_input_string.begin ( ), upper_case_input_string.end ( ), upper_case_input_string.begin ( ), toupper );

	return upper_case_input_string;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - to_lower
//
// Description:
//
// - Converts all characters in a string to lower case.
//
// Arguments:   
//
// - inputString
//   The string we wish to convert.
//
// Return Value:
//
// - An all lower case copy of inputString..
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A new copy of the strings is created and converted to an all lower case verions of inputString.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::to_lower ( string inputString )
{
	// Create an upper case version of the input string.

	string lower_case_input_string ( inputString );
	transform ( lower_case_input_string.begin ( ), lower_case_input_string.end ( ), lower_case_input_string.begin ( ), tolower );

	return lower_case_input_string;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - replace_string
//
// Description:
//
// - Searches for all occurences of a substring in inputString, and replace all occurances of the found substring
//   with a replacement string.
//
// Arguments:   
//
// - inputString:
//
//   - The string we wish to search and replace with in.
//
//   - We will make a copy of this string, so the original sring used to supply the argument will remain unchanged.
//
// - search:
//
//   - The sub string we wish to search for.
//
// - replace:
//
//   - The string we wish replace teh substring with.
//
//
// Return Value:
//
// - A copy of the input string, with all occureances of search, replaced by, replace.
//
// Pre-Conditions:
//
// - N/A
//   
// Post-Conditions:
//
// - A copy of the input string, with all occureances of search, replaced by, replace.
//
// - The original input string used for the input string argument, will remain unchanged.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::replace_string ( string input_string, const string& search, const string& replace )
{
	size_t pos = 0;

	while ( ( pos = input_string.find ( search, pos ) ) != string::npos )
	{
		input_string.replace ( pos, search.length ( ), replace );
		pos += replace.length ( );
	}

	return input_string;
}


//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - tokenize_csv_string
//
// Description:
//
// - Parse out all the comma seperated sub strings in an input string, and assign
//   them one by one, to a vector.
//
//   Example:
//
//   - inputString  = "One,Two,Three,Four"
//   - outputVector = { "One", "Two", "Three", "Four" }
//
// Arguments:
//
// - inputString:
//
//   The CSV formatted input string to read.
//
// Return Value:
//
// - A vector, who's elements corespond to the CSV fileds of the input string.
//   If the input string is either empty, or if no valid substrings may be
//   found, then the out put vector is returned as an empty vector.
//
// Pre-Conditions:
//
// - The input string must be a valid CSV formated string.
//   No spaces after the delimiter;
//   e.g.
//     "One,Two" is correct
//     "One, Two" is incorrect because of the space after the ',' character.
//   
// Post-Conditions:
//
// - The out put string has been populated with the CSV sub-strings of the input
//   string.
//
//--------------------------------------------------------------------------------------------------------------------------------------

vector <string> StaticUtility::tokenize_csv_string ( string inputString )
{
	const string DELIMITER = ",";

	vector <string> token_list;
	string          csv_temp { inputString };
	string          element;
	int             delimiter = 0;

	do
	{
		delimiter = csv_temp.find   ( DELIMITER );
		element   = csv_temp.substr ( 0, delimiter );
		csv_temp  = csv_temp.substr ( delimiter + 1, csv_temp.length ( ) - delimiter );

		token_list.push_back ( element );

	}
	while ( delimiter >= 0 );

	return token_list;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Function:
//
// - text_field
//
// Description:
//
// - Compiles a formetted field string by combining a field label and a field name, along with a field label width that can be used to 
//   align field values in the case where multiple text fields are used in a list.
//
//   Example 1:
//
//   - Input arguments:
//     - Field Label = "Name"
//     - Field Value = "Value"
//     - Label Width = 8
//
//   - output String:
//     - Text Field: "Name    Value"
//                    |'''|'''|'''|'''|
//                    0   4   8   12  16
// Arguments:
//
// - fieldLabel:
//
//   The field label
//
// Return Value:
//
// - A vector, who's elements corespond to the CSV fileds of the input string.
//   If the input string is either empty, or if no valid substrings may be
//   found, then the out put vector is returned as an empty vector.
//
// Pre-Conditions:
//
// - The input string must be a valid CSV formated string.
//   No spaces after the delimiter;
//   e.g.
//     "One,Two" is correct
//     "One, Two" is incorrect because of the space after the ',' character.
//   
// Post-Conditions:
//
// - The out put string has been populated with the CSV sub-strings of the input
//   string.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::text_field ( string field_label, string field_value, int label_width, string delimiter )
{
	string label_padding;
	string text;

	int difference = label_width - field_label.length ( );
	
	if ( difference > 0 )
	{
		label_padding = string ( difference, 32 );
	}
	else
	{
		label_padding = "";
	}

	text = field_label + label_padding + delimiter + field_value;

	return text;
}

//------------------------------------------------------------------------------
// int_pad_left.
//------------------------------------------------------------------------------

string StaticUtility::int_pad_left ( int i, char ch, int width )
{
	stringstream padded_string;

	padded_string << setfill ( ch ) << setw ( width ) << i;

	return padded_string.str ();
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - get_numerator_string
//
// DESCRIPTION:
//
// - Given a string formatted as a ratio, e.g. abc/xyz, return the numerator portion of the string.
//
// ARGUMENTS:
//
// - ratio_string
//   - String representation of a ratio.
//   - Example 1: "1/2"
//   - Example 2: "1.00/2.25"
//   - Example 3: "abc/xyz"
//
// RETURN VALUE:
//
// - The numerator portion of the string.
//
//   - Example 1:
//     - Input:  "1/2"
//     - Return: "1"
//
//   - Example 2:
//     - Input:  "1.00/2.25"
//     - Return: "1.00"
//
//   - Example 3:
//     - Input:  "abc/xyz"
//     - Return: "abc"
//
// PRE-CONDITIONS:
//
// - The input string should be correctly formatted as described abouve.
//   
// POST-CONDITIONS:
//
// - The numerator portion of the string is returned.
//
//--------------------------------------------------------------------------------------------------------------------------------------

string StaticUtility::get_numerator_string ( string ratio_string )
{	
	int index;

	// Find the index of the forward slash.

	for ( index = 0; index < (int) ratio_string.length (); index++ )
	{
		if ( ratio_string [ index ] == '/' )
		{
			break;
		}
	}

	// Capture the numerator portion of the string and return.

	string numerator = ratio_string.substr ( 0, index );

	return numerator;
}

//------------------------------------------------------------------------------
// FUNCTION:
//
// - get_denominator_string
//
// DESCRIPTION:
//
// - Given a string formatted as a ratio, e.g. abc/xyz, return the denominator portion of the string.
//
// ARGUMENTS:
//
// - ratio_string
//   - String representation of a ratio.
//   - Example 1: "1/2"
//   - Example 2: "1.00/2.25"
//   - Example 3: "abc/xyz"
//
// RETURN VALUE:
//
// - The denominator portion of the string.
//
//   - Example 1:
//     - Input:  "1/2"
//     - Return: "2"
//
//   - Example 2:
//     - Input:  "1.00/2.25"
//     - Return: "2.25"
//
//   - Example 3:
//     - Input:  "abc/xyz"
//     - Return: "xyz"
//
// PRE-CONDITIONS:
//
// - The input string should be correctly formatted as described abouve.
//   
// POST-CONDITIONS:
//
// - The denominator portion of the string is returned.
//
//------------------------------------------------------------------------------

string StaticUtility::get_denominator_string ( string ratio_string )
{
	int index;
	int length = ratio_string.length ();

	// Find the index of the forward slash.

	for ( index = 0; index < length; index++ )
	{
		if ( ratio_string [ index ] == '/' )
		{
			break;
		}
	}

	// Capture the numerator portion of the string and return.

	string numerator = ratio_string.substr ( index + 1, length - 1 );

	return numerator;
}


//------------------------------------------------------------------------------
// align_string.
//------------------------------------------------------------------------------

string StaticUtility::align_string ( string text, Integer width, Alignment alignment )
{
	string  aligned_string    ( "" );		// Initialise the output string to empty to start with. We will build it up as we go.           
	char    padding_character ( 0x20 );		// A white space character. SPC is usualy a good choice.
	Integer padding_length    ( 0 );		// Initialize the padding to zero. We will calculate it later as required.        

	// Calculate the padding length.
	// - The padding length will be used as a padding specifier in the case where text.length() <= width.
	// - The padding length will be used as an offset into text, in cases where text.length() > width.

	padding_length = width - text.length ( );

	switch ( alignment )
	{
		case ALIGN_LEFT:
		
			if ( ( Integer ) text.length () <= width )
			{
				aligned_string = text + string ( padding_length, padding_character );
			}
			else
			{
				aligned_string = text.substr ( 0, width );
			}
		
			break;

		case ALIGN_RIGHT:
		
			if ( ( Integer ) text.length () <= width )
			{
				aligned_string = string ( padding_length, padding_character ) + text;
			}
			else
			{
				aligned_string = text.substr ( -padding_length, width );
			}
		
			break;

		case ALIGN_CENTER:
		
			if ( ( Integer ) text.length () <= width )
			{
				aligned_string = string ( padding_length / 2, padding_character ) + text;
			}
			else
			{
				aligned_string = text.substr ( -padding_length / 2, width );
			}
		
			break;
	}

	// Return the aligned string.

	return aligned_string;
}

//------------------------------------------------------------------------------
// to_aligned_string.
//------------------------------------------------------------------------------

string StaticUtility::to_aligned_string ( Integer value, Integer width, Alignment alignment )
{
	return align_string ( to_string ( value ), width, alignment );
}

//------------------------------------------------------------------------------
// align_string.
//
// DEPENDENCIES:
//
//   sstream
//------------------------------------------------------------------------------

string StaticUtility::to_aligned_string ( Real value, Integer precision, Integer width, Alignment alignment )
{
	ostringstream output_string;
	output_string << fixed << setprecision ( precision ) << value;
	return align_string ( output_string.str ( ), width, alignment );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - FunctionName
//
// DESCRIPTION:
//
// - Function descrition.
//
// ARGUMENTS:
//
// - N/A
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - N/A.
//   
// POST-CONDITIONS:
//
// - N/A.
//
//--------------------------------------------------------------------------------------------------------------------------------------
