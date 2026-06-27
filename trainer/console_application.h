//--------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application Platform (G-CAP).
// Application: N/A
// Class:	    ConsoleApplication
// Version:	    1.3
// Date:	    2014
// Author:	    Rohin Gosling
//
// Description:
//
//   Generic console application platform.
//
//--------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"

#include <string>
#include <vector>

using namespace std;

class ConsoleApplication
{
	//--------------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// ...

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// ...

protected:

	const int C_DEFAULT_MARGIN = 0;

private:
	
	const string C_MSG_EXECUTION_TIME    = "Program execution time:";		
	const string C_MSG_EXCEPTION         = "EXCEPTION: ";
	const string C_MSG_EXCEPTION_GENERIC = "Generic exception.";
	
	
	//--------------------------------------------------------------------------------------------------------------------------------------
	// Functions.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	ConsoleApplication  ();								// Default constructor.
	ConsoleApplication  ( int argc, char* argv [] );	// Pass through the command line arguments.
	~ConsoleApplication ();								// Desctructor.

	// General consumer functions.

	void initialize    ( int argc, char* argv [] );		// Used to initialize constructors. May also be used indepementantly.
	void run           ();								// Launches the applcation.
	void clear_console ();								// Clear the console.
	void move_to       ( int x, int y );				// Move the cursor to the location specified by (x,y);
	
private:

	// Cammand line management functions.

	vector <string> get_command_line_arguments ( int argc, char* argv [ ] );
	virtual void    command_interpreter        ( vector <string> command_line ) = 0;

	// display functions.

	string print_execution_time ( long long time );
	string print_execution_time ( int margin, long long time );

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Accessors and mutators
	//--------------------------------------------------------------------------------------------------------------------------------------

	// Accessors

	// ...

	// Mutators.

	// ...

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Member data.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	int margin { C_DEFAULT_MARGIN };		// Initialize default text margin.

private:

	vector <string> command_line;			// Pupulated using GetCommandLineArguments.

	
};

