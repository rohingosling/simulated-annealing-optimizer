//------------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Generic Console Application Platform (G-CAP).
// Application: N/A
// Class:       N/A
// Version:	    1.1
// Date:	    2014
// Author:	    Rohin Gosling
//
// Description:
//
//   Program entry point.
//
//------------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "training_engine.h"

#include <iostream>
#include <string>
#include <exception>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------
// Constants.
//------------------------------------------------------------------------------------------------------------------------------------------

// Message text.

const string C_MSG_EXCEPTION         = "EXCEPTION: ";
const string C_MSG_UNKNOWN_EXCEPTION = "UNKNOWN EXCEPTION: ";

// System commands.

const string C_CMD_PAUSE = "pause";

// Program control.

const bool C_PAUSE_BEFORE_EXIT = true;		// Set to true in order to pause after execution.

//------------------------------------------------------------------------------------------------------------------------------------------
// Functions Declerations.
//------------------------------------------------------------------------------------------------------------------------------------------

void exit_application ( bool pasue_before_exit );


//------------------------------------------------------------------------------------------------------------------------------------------
// C++ main ( Program entry point ).
//------------------------------------------------------------------------------------------------------------------------------------------

int main ( int argc, char* argv[] )
{
	try
	{
		// Decalre and call main application object.

		TrainingEngine application { argc, argv };

		application.run ();
		
		// Exit application.

		exit_application ( C_PAUSE_BEFORE_EXIT );
	}
	catch ( exception& e ) { cout << endl << C_MSG_EXCEPTION << e.what() << endl; }
	catch ( ... )          { cout << endl << C_MSG_UNKNOWN_EXCEPTION     << endl; }

	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - exit_application
//
// DESCRIPTION:
//
// - Provides a wrapper for any cleanup and termination code.
//
// ARGUMENTS:
//
// - pasue_before_exit
//
//   Boolean flag to specify whether or not to pause the console application before terminating.
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
// - The application is cleaned up and ready to be terminated.
//
//------------------------------------------------------------------------------------------------------------------------------------------

void exit_application ( bool pasue_before_exit )
{
	if ( pasue_before_exit )
	{
		cout << endl;
		system ( C_CMD_PAUSE.c_str () );
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------------------------------
