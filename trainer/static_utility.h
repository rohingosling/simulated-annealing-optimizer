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

#pragma once

#include "stdafx.h"

#include <string>
#include <vector>
#include <iomanip>

using namespace std;


class StaticUtility
{
	//----------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//----------------------------------------------------------------------------------------------------------------------------------

public:

	using Natural   = unsigned long;									// N: n Є {  0 ≤ x ≤ ∞  }
	using Integer   = long;												// Z: n Є { -∞ ≤ x ≤ ∞  }
	using Real      = double;											// R:
	using Complex	= struct { Real r; Real i; };						// C:
	using Alignment = enum { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT };	// Text alignment.
	using TokenList = vector <string>;									// List of token strings.


	//----------------------------------------------------------------------------------------------------------------------------------
	// Functions.
	//----------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	StaticUtility  ( );		// Default constructor.	
	~StaticUtility ( );		// Desctructor.

	// General purpose, usefull functions.
 
	static void      sleep                  ( const int milliseconds );
	static Natural	 get_max_length         ( vector < string > string_list );
	static string	 to_upper               ( string input_string );
	static string	 to_lower               ( string input_string );
	static string    replace_string         ( string input_string, const string& search, const string& replace );		
	static string    text_field             ( string field_label, string field_value, int label_width, string delimiter );	
	static TokenList tokenize_csv_string    ( string input_string );
	static string    int_pad_left           ( int i, char ch, int width );
	static string    get_numerator_string   ( string ratio_string );
	static string    get_denominator_string ( string ratio_string );

	// Date and time.
		
	static string    time_to_string       ( long long time );
	static string    time_to_string       ( long long time, bool show_hours, bool show_minutes, bool show_seconds, bool show_milliseconds );
	static long long time_to_milliseconds ( long long time );
	static long long time_to_seconds      ( long long time );
	static long long time_to_minutes      ( long long time );
	static long long time_to_hours        ( long long time );

	// Random number generation.

	static void   random_seed    ();	
	static double random_between ( double a, double b );
	
	// String conversion functions.

	static string align_string      ( string text, Integer width, Alignment alignment );
	static string to_aligned_string ( Integer value, Integer width, Alignment alignment );
	static string to_aligned_string ( Real value, Integer precision, Integer width, Alignment alignment );
	

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//--------------------------------------------------------------------------------------------------------------------------------------

	// Accessors

	// ...

	// Mutators.

	// ...

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// ...

private:

	// ...

};

