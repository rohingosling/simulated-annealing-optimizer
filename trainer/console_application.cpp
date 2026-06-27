//--------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application Platform (G-CAP).
// Application: N/A
// Class:	    ConsoleApplication
// Version:	    1.3
// Date:        2014
// Author:	    Rohin Gosling
//
// Description:
//
//   Generic console application platform.
//
//   Derive a new class from ConsoleApplication, and then override executeCommandInterpreter to initiate application execution in the 
//   derived class. 
//
//--------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "console_application.h"
#include "static_utility.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cctype>


using namespace std;
using namespace std::chrono;	// We will be using some timming functions for measurement.


//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 1/2
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleApplication::ConsoleApplication ( )
{
	initialize ( 0, nullptr );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Constructor 2/2
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleApplication::ConsoleApplication ( int argc, char* argv [ ] )
{
	initialize ( argc, argv );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// Destructor.
//--------------------------------------------------------------------------------------------------------------------------------------

ConsoleApplication::~ConsoleApplication ( )
{
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - initialize
//
// DESCRIPTION:
//
// - Used to initialize the constructors
// - May also be used independantly.
//
// ARGUMENTS:
//
// - argc 
//   Number of command line arguments.
//
// - argv[]
//   List of command line arguments.
//
// RETURN VALUE:
//
// - N/A
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - The class has been initialized and reset to it's default state.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::initialize ( int argc, char* argv[] )
{
	// Convert C-style command line argument array, to an STL vector.
	// - If the number of arguments is set to zero, then ignore the command line arguments.

	if ( argc > 0 )
	{
		this->command_line = get_command_line_arguments ( argc, argv );
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - Run
//
// DESCRIPTION:
//
// - The Run function is used to launch the application class.
//
// - We use a "run" function, to abscract and isolate execution of an object's, code from any complexities that may
//   be ascociated with configuring and managing the C++ main function.
//
// ARGUMENTS:
//
// - N/A
//
// RETURN VALUE:
//
// - N/A
//
// PRE-CONDITIONS:
//
// - Any class wide global memory requirements have been allocated.
//   
// POST-CONDITIONS:
//
// - The application or object has completed execution.
//
// - All memory allocated by the object, has been de-alocated.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::run ( )
{
	// Start the timer.
		
	auto timer_start = system_clock::now ( );

	// Execute the command line interpreter.

	command_interpreter ( this->command_line );

	// Stop the clock and calculate the elappsed time.

	auto timer_stop   = system_clock::now ( );		// Stop the timer.
	auto elapsed_time = timer_stop - timer_start;	// Calculate file load time.

	// Convert elapsed time to seconds and milliseconds.
	// - Set precision to 3 decimal places.
	// - We will need to use a high precision int to hold the total elapsed time.

	long long delta_time = duration_cast < milliseconds > ( elapsed_time ).count ( );
	
	// Display the elapsed time.

	cout << print_execution_time ( delta_time ) << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - GetCommandLineArguments
//
// DESCRIPTION:
//
// - Convert the standard C-style command line argument array, to an STL vector.
//
// - We do this in order to simplyfy the task of accessing command line arguments
//   in a more modern coding style that is easier to work with, and less prone to 
//   errors.
//
// ARGUMENTS:
//
// - argc:
//   - The number of command line arguments.
//   - This will always be 1 or more, since the appplication executable command
//     name will always be the first argument in the list.
//
// - argv:
//   - A array of C-style strings that hold the arguments.
//   - The first argument is always the executable command.
//
//     e.g.
//
//       Given a command line program that outputs the sum of two integer arguments.
//
//       | > ADD 1 2
//       |
//       | argc = 3
//       | argv = { "ADD", "1", "2" }
//		 |
//       | Return Value = 1 + 2 = 3
//       |
//       | >
//
// RETURN VALUE:
//
// - A vector containing the command line arguments.
//
// PRE-CONDITIONS:
//
// - The C++ main function must be defined using the argc and argv arguments.
//   
// POST-CONDITIONS:
//
// - A vector containing the command line arguments.
//
//--------------------------------------------------------------------------------------------------------------------------------------

vector <string> ConsoleApplication::get_command_line_arguments ( int argc, char* argv [ ] )
{
	// Create a new vector to hold all the command line arguments.

	vector <string> command_line_arguments;

	// Loop through the standard C-style command line arguments, and add each one to the vector.

	for ( int i = 0; i != argc; i++ )
	{
		command_line_arguments.push_back ( argv [ i ] );
	}

	// Return the new command line argument vector back to the caller.

	return command_line_arguments;
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - clear_console
//
// DESCRIPTION:
//
// - Clears the console screen.
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
// - The console is a standard Windows command line console.
//   
// POST-CONDITIONS:
//
// - The console screen has been cleared.
// - the cursor has been moved to the top left character cell of the console screen.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::clear_console ()
{
	try
	{
		HANDLE                     hStdOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD                      count;
		DWORD                      cellCount;
		COORD                      homeCoords = { 0, 0 };

		// Get a handel to the current standard output console device.

		hStdOut = GetStdHandle ( STD_OUTPUT_HANDLE );

		if ( hStdOut == INVALID_HANDLE_VALUE ) throw 0;

		// Get the number of cells in the current buffer.

		if ( !GetConsoleScreenBufferInfo ( hStdOut, &csbi ) ) throw 0;

		cellCount = csbi.dwSize.X * csbi.dwSize.Y;

		// Fill the entire buffer with spaces.

		if ( !FillConsoleOutputCharacter ( hStdOut, (TCHAR) 0x20, cellCount, homeCoords, &count ) ) throw 0;

		// Fill the entire buffer with the current colors and attributes.

		if ( !FillConsoleOutputAttribute ( hStdOut, csbi.wAttributes, cellCount, homeCoords, &count ) ) throw 0;

		// Move the cursor home.

		SetConsoleCursorPosition ( hStdOut, homeCoords );
	}
	catch ( ... )
	{
		cout << endl << C_MSG_EXCEPTION << C_MSG_EXCEPTION_GENERIC << endl;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - move_to
//
// DESCRIPTION:
//
// - Moves the cursor to the console screen location specified by (x, y).
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
// - The console is a standard Windows command line console.
//   
// POST-CONDITIONS:
//
// - The cursor has been moved to the specified (x, y) location.
//
//--------------------------------------------------------------------------------------------------------------------------------------

void ConsoleApplication::move_to ( int x, int y )
{
	HANDLE hStdOut;
	COORD  homeCoords = { x, y };

	// Get a handel to the current standard output console device.

	hStdOut = GetStdHandle ( STD_OUTPUT_HANDLE );

	if ( hStdOut == INVALID_HANDLE_VALUE ) return;

	// Move the cursor home.

	SetConsoleCursorPosition ( hStdOut, homeCoords );
}

//--------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - print_execution_time
//
// DESCRIPTION:
//
// - Print the execution time to the console.
//
// ARGUMENTS:
//
// - margin
//   Number of characters between teh left hand edge of the consol and the first characer of text.
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

// Overload 1/2

string ConsoleApplication::print_execution_time ( long long time )
{
	return print_execution_time ( this->margin, time );
}

//--------------------------------------------------------------------------------------------------------------------------------------

// Overload 2/2

string ConsoleApplication::print_execution_time ( int margin, long long time )
{
	// Constants
		
	const string NEW_LINE = "\n";
	const char   SPACE    = 0x20;

	// Configure console message margin.
	
	string msg_margin ( margin, SPACE );
	string msg_info   ( NEW_LINE );

	// Compile output string.

	ostringstream s;

	s << StaticUtility::time_to_string ( time );

	msg_info += msg_margin + C_MSG_EXECUTION_TIME + SPACE + s.str();
		
	// return output string.

	return msg_info;	
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






