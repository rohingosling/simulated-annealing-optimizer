//------------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Entelect 100k challenge.
// Application: Agent Training Engine
// Class:	    TrainingEngine
// Version:	    1.0
// Date:	    2015
// Author:	    Rohin Gosling
//
// Description:
//
//   Training engine responsible for training an agent to compete in the Entelect 100k challenge.
//
//------------------------------------------------------------------------------------------------------------------------------------------

#pragma once
#include "console_application.h"
#include "test_function.h"

using namespace std;

class TrainingEngine :	public ConsoleApplication
{
	//--------------------------------------------------------------------------------------------------------------------------------------
	// Constants
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// ...

private:
	
	// ...

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Data type aliases
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	using SolutionSE = TestFunction;

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Functions.
	//--------------------------------------------------------------------------------------------------------------------------------------

public:

	// Constructors and destructors

	TrainingEngine ( int argc, char* argv [] );
	~TrainingEngine ();

	// Overriden functions.

	virtual void command_interpreter ( vector <string> command_line ) override;

	// Simulated Anneallling
	
	SolutionSE initialize_solution              ( SolutionSE& solution );
	double     compute_temperature              ( double k );
	double     compute_insulated_temperature    ( double temperature, double temperature_min, double cooling_velocity, double temperature_scale );
	double     compute_exploitation_probability ( double k, double v, double p_max );
	double     compute_acceptance_probability   ( double solution_energy, double candidate_solution_energy, double temperature );
	double     compute_solution_energy          ( SolutionSE& solution );	
	SolutionSE generate_candidate_solution      ( const SolutionSE& solution, double temperature );
	void       optimize                         ();
	void       test_solution                    ( SolutionSE& solution );

	// File managment functions.

	void clear_file               ( string file_name );
	void write_csv_header         (	string file_name );
	void write_itteration_results (	string file_name, long long time, double p_exploit, double solution, double best_solution );
	void write_logfile            ( string file_name, long long time, double data );
	void write_heart_beat         ( string file_name, long long time, long long eta, long long iteration, long long iteration_sample );

	// Display functions.

	void   print_program_info ();	
		
private:

	// Test functions.

	void test_1 ();

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

	// ...
	
private:

	// ...
};

