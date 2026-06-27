//--------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "training_engine.h"
#include "static_utility.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <random>
#include <math.h>
#include <thread>
#include <string>

using namespace std;
using namespace std::chrono;	// We will be using some timming functions for measurement.

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Constructor 1/1
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

TrainingEngine::TrainingEngine ( int argc, char* argv [] ) : ConsoleApplication { argc, argv }
{
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

TrainingEngine::~TrainingEngine ()
{
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - ExecuteCommandInterpreter
//
// DESCRIPTION:
//
// - Execute commands passed in through the command line.
//
// - ExecuteCommandInterpreter should be overloaded in a derived class, and not
//   called directly.
//
//   1. Extend ConsoleApplication.
//   2. Overload ExecuteCommandInterpreter() to implement commands.
//   3. Call an instance of the derived class in Main.cpp.
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
// - N/A
//   
// POST-CONDITIONS:
//
// - The apropriate commands, as defined in a derived class, have been executed.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::command_interpreter ( vector <string> command_line ) 
{
	// Declaire local variables.

	bool run_test { false };

	// Get the number of arguments on the command line, including the command it's self.

	int argument_count { (int) command_line.size () };
	int argument_index { 0 };

	// Execute commands.

	switch ( argument_count )
	{
		case 1:	

			run_test = false;

			if ( !run_test )
			{
				print_program_info ();
				optimize ();
			}
			else
			{
				test_1 ();
			}
			break;

		case 2:			
			break;

		default:			
			break;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::test_1 ()
{
	// Declare loca variables.

	long long time;

	// Start test

	cout << endl << "[APPLICATION] Test Started." << endl;

	steady_clock::time_point clock_start = steady_clock::now ();

	this_thread::sleep_for ( milliseconds ( 2500 ) );	

	steady_clock::time_point clock_stop = steady_clock::now ();

	steady_clock::duration duration = clock_stop - clock_start;

	time = duration_cast <milliseconds> ( duration ).count ();

	// Report results.

	cout << "[APPLICATION] Time    = " << StaticUtility::time_to_string       ( time, true, true, true, true ) << endl;
	cout << "[APPLICATION] Hours   = " << StaticUtility::time_to_hours        ( time)                          << endl;
	cout << "[APPLICATION] Minutes = " << StaticUtility::time_to_minutes      ( time)                          << endl;
	cout << "[APPLICATION] Seconds = " << StaticUtility::time_to_seconds      ( time)                          << endl;
	cout << "[APPLICATION] ms      = " << StaticUtility::time_to_milliseconds ( time)                          << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - initialize_solution
//
// DESCRIPTION:
//
// - Initialize a solutin and prepare if for simulated annealing. 
//
// ARGUMENTS:
//
// - solution
//   The address of a solution to initialize.
//
// RETURN VALUE:
//
// - N/A.
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - The input solutions has been optimized.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

TrainingEngine::SolutionSE TrainingEngine::initialize_solution ( SolutionSE& solution )
{
	// Declare local constants.

	const double HYPOTHESIS_MIN = 0.0;
	const double HYPOTHESIS_MAX = 1.0;

	// Define local data types

	enum InitializationSetting
	{
		INIT_RANDOM,
		INIT_MIN,
		INIT_MAX,
		INIT_MEAN,
		INIT_CUSTOM
	};

	// Declare local variables.

	InitializationSetting setting          { INIT_MEAN };	
	double                constraint       { 0.0 };
	int                   constraint_index { 0 };
	int                   constraint_count { (int) solution.hypothesis.size () };

	// Initialize random number generator.

	random_device                      rd;
    mt19937                            random_generator    ( rd() );
    uniform_real_distribution <double> random_distribution ( 0.0, 1.0 );	

	// Configure initialization.

	setting          = INIT_MEAN;
	constraint_index = 0;

	switch ( setting )
	{
		case INIT_RANDOM:	constraint = random_distribution ( random_generator );	break;
		case INIT_MIN:		constraint = HYPOTHESIS_MIN;							break;
		case INIT_MAX:		constraint = HYPOTHESIS_MAX;							break;
		case INIT_MEAN:		constraint = 0.5 * HYPOTHESIS_MAX;						break;
		case INIT_CUSTOM:	constraint = 0.0;										break;
	};

	// Initialize solution.

	for ( int constraint_index = 0; constraint_index < constraint_count; constraint_index++ )
	{		
		solution.hypothesis      [ constraint_index ] = constraint;		
	}

	// Return initizlized solution.

	return solution;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - compute_insulated_temperature
//
// DESCRIPTION:
//
// - Insulate the temperature in order to prevent runaway energy transfer. 
//
// ARGUMENTS:
//
// - temperature
//   Input temperature. 
//
// - temperature_min
//   Minimum temperature. 
//
// - cooling_velocity
//   The rate at which colling may occur.
//   - The slower the cooling velocity, the longer the system remains in a high energy state, effectivly alowing the algorythm to search the problem space
//     for a longer period of time. The algorythm will converge to a beter solution, after a longer training period.
//   - The faster the cooling velocity, the less time the algorythm spends searching the problem space. The algorythm will converge to a less optimal
//     solution, over a shorter training period.
//
// - temperature_scale
//   Controls the energy input to the system.
//
// RETURN VALUE:
//
// - The insulated transformation of the input argument 'temperature'.
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - The insulated transformation of the input argument 'temperature', is returned.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

double TrainingEngine::compute_insulated_temperature ( double temperature, double temperature_min, double cooling_velocity, double temperature_scale )
{
	// Declare local variables.

	double insulated_temperature { 0.0 };				// Temperature schedule.
	double x                     { 0.0 };				// Natural logarythm exponenet.
	double t                     { temperature };		// Temperature.
	double t_min                 { temperature_min };	// Minimum temperature.
	double t_scale               { temperature_scale };	// Temperature scaling factor.
	double v                     { cooling_velocity };	// Cooling rate.
	
	// Compute temperature schedule.

	x                     = ( t - 1 ) / v;
	insulated_temperature = t_min + t_scale * exp ( x );

	return insulated_temperature;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - compute_exploitation_probability
//
// DESCRIPTION:
//
// - The exploitation probability is computed to give the algorythm a share of itterations, that is can use to further refine the best solution
//   discovered  so far.
//
// - The exploitation condition is a non-standard extention to the standard version of the simulated annealing algorythm.
//
// ARGUMENTS:
//
// - k
//   Normalized itteration index. Specifies how far along in the training schedule we are.
//
// - v
//   Exploitation velocity.
//
// - p_max
//   Pamximum probability.
//
// RETURN VALUE:
//
// - The insulated transformation of the input argument 'temperature'.
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - A stochastic probability is computed, that will be used by the algorythm to descide whether or not to perform best solution refinement or not.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

double TrainingEngine::compute_exploitation_probability ( double k, double v, double p_max )
{
	// Declare local variables.

	double p { 0.0 };					// Exploitation schedule.	

	// Compute the explotatio scheudle.

	p = p_max * exp ( v * ( k - 1 ) );	// Calculate the exploitation schedule.

	return p;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - generate_candidate_solution
//
// DESCRIPTION:
//
// - Configure a new candidate solution with a hypothesus, based on the current temperature of the solution system.
//
// - The higher the temperature, the wider the rxploritary hypothesis range will be.
//
// ARGUMENTS:
//
// - solution
//   Solution object to configure with candidate parameters.
//
// - insulated_temperature
//   Current temperature of the solution system.
//
// RETURN VALUE:
//
// - Configured solution object.
//
// PRE-CONDITIONS:
//
// - The solution object 'solution' should be initialized before being passed in.
//   
// POST-CONDITIONS:
//
// - The solution object 'solution' is configured with the new candidate solution parameters.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

TrainingEngine::SolutionSE TrainingEngine::generate_candidate_solution ( const SolutionSE& solution, double insulated_temperature )
{
	// Declare local variables.

	SolutionSE candidate_solution { solution };
	double     hypothesus         { solution.hypothesis [ 0 ] };
	double     hypothesus_range   { insulated_temperature };
	double     hypothesus_move    { 0.0 };
	
	// Initialize random number generator.

	random_device                      rd;
    mt19937                            random_generator    ( rd() );
    uniform_real_distribution <double> random_distribution ( 0.0, 2.0 * hypothesus_range );

	// Calculate new hypothesus.

	hypothesus_move = random_distribution ( random_generator );
	hypothesus     += hypothesus_move - hypothesus_range;

	if ( hypothesus > 1.0 ) hypothesus = 2.0 - hypothesus;
	if ( hypothesus < 0.0 ) hypothesus = -hypothesus;

	// Update solution hypothesus.

	candidate_solution.hypothesis [ 0 ] = hypothesus;

	return candidate_solution;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - compute_solution_energy
//
// DESCRIPTION:
//
// - Computes the energy moment of the current solution.
//
// - For most applications, this will simply be a wrapper for the algorythm's optimization cost function. However, more sophisicated energy computations
//   over and abouve the cost function may be implemented.
//
// ARGUMENTS:
//
// - solution
//   A solution object from which to compute the soltion energy.
//
// RETURN VALUE:
//
// - Normalized real value in the range [0.0..1.0], representing the solution energy.
//
// PRE-CONDITIONS:
//
// - The solution object should be initialized before being passed in.
//   
// POST-CONDITIONS:
//
// - The solution energy of the solution energy of the input solution has been computed and returned to the caller.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

double TrainingEngine::compute_solution_energy ( SolutionSE& solution )
{	
	return solution.compute_cost ();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - compute_acceptance_probability
//
// DESCRIPTION:
//
// - Acceptance function used to compare a candidate solution's energy with a a target solution energy level, in order to determin if the candidate solution
//   has less energy than the targe solution. The caller would use this function to determine if the candidate solution should be accepted as the next
//   best solution.
//
// - The target solution energy is usualy populated with the energy level of the current best soltion.
//
// ARGUMENTS:
//
// - solution_energy
//   The target solution energy. Usualy set to the solution energy of the best solution so far.
//
// - candidate_solution_energy
//   The solution energy of a candidate soltion we would like to compare with the target solution.
//
// - temperature
//   The current system temperature. This will be used as the probability threshold below which the acceptance probability will be 0.0.
//
// RETURN VALUE:
//
// - Candidate solution probability.
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - The candidate soltion probability has been computed, and returned to the caller.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

double TrainingEngine::compute_acceptance_probability ( double solution_energy, double candidate_solution_energy, double temperature )
{
	double p { 0.0 };
	double x { 0.0 };

	if ( temperature > 0.0 )
	{
		if ( candidate_solution_energy < solution_energy )
		{
			p = 1.0;
		}
		else
		{
			x = -( candidate_solution_energy - solution_energy ) / temperature;
			p = exp ( x );
		}
	}
	else
	{
		p = 0.0;
	}

	return p;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - compute_temperature
//
// DESCRIPTION:
//
// - Compute the system temperarute 
//
// - xxx
//
// ARGUMENTS:
//
// - k
//   Normalized itteration index. Specifies how far along in the training schedule we are.
//
// RETURN VALUE:
//
// - The temperature of the system, based on how far into the straining/cooling schedule we are.
//
// PRE-CONDITIONS:
//
// - N/A
//   
// POST-CONDITIONS:
//
// - A temperature based on where we are in the cooling schedule has been computed and returned to the caller.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

double TrainingEngine::compute_temperature ( double k )
{
	// Declare local variables.

	double t { 0.0 };

	// Compute temprature, and return value to caller.

	t = 1.0 - k;

	return t;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - optimize
//
// DESCRIPTION:
//
// - Implementaion of standard Simulated Annealing, extended to support late quatum exploitation.
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
// - The input data file must exist before calling optimize(). 
//   
// POST-CONDITIONS:
//
// - An optimized solution has been found.
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::optimize ()
{
	// Declare local variables.

	ofstream   data_file;
	ofstream   log_file;
	string     data_file_name { "simulated_annealing_output.csv" };		// Relative path -- written to the current working directory.
	string     log_file_name  { "simulated_annealing.log" };			// Relative path -- written to the current working directory.

	SolutionSE solution;
	SolutionSE candidate_solution;
	SolutionSE best_solution;
	
	double     solution_energy              { 0.0 };
	double     candidate_solution_energy    { 0.0 };
	double     solution_min_energy          { 0.0 };
	double     temperature                  { 0.0 };
	double     random_number                { 0.0 };
	double     transition_probability       { 0.0 };
	double     insulated_temperature        { 0.0 };
	double     exploitation_probability     { 0.0 };
	double     exploitation_velocity        { 0.0 };
	double     exploitation_probability_max { 0.0 };
	double     temperature_scale            { 0.0 };
	double     cooling_velocity             { 0.0 };
	double     temperature_min              { 0.0 };
	double     k                            { 0.0 };			// Normalized itteration index.
	long long  time                         { 0 };
	int        execution_time_hours         { 0 };
	int        execution_time_minutes       { 0 };
	int        execution_time_seconds       { 0 };
	int        execution_time_milliseconds  { 0 };			
	long long  duration_m                   { 0 };
	long long  duration_s                   { 0 };
	long long  duration_ms                  { 0 };	
	long long  elapsed_time                 { 0 };	
	long long  eta                          { 0 };
	long long  heart_beat                   { 0 };
	long long  heart_beat_frequency         { 0 };	
	long long  iteration                    { 0 };	
	long long  iteration_sample             { 0 };
	
	// Open files for writeing.

	clear_file  ( data_file_name );
	clear_file  ( log_file_name );
			
	// Initialize random number generator.

	random_device                      rd;
    mt19937                            random_generator    ( rd() );
    uniform_real_distribution <double> random_distribution ( 0.0, nextafter ( 1.0, DBL_MAX ) );

	// Configure simulated annealing algorythm.
		
	temperature                  =   1.0;				// Temperature                            - Starting temperature.
	temperature_min              =   0.05;				// Insulated Temperature                  - Minimum temperature.
	temperature_scale            =   0.1;				// Insulated Temperature                  - Temperature scaling factor.
	cooling_velocity             =   0.2;				// Insulated Temperature                  - Cooling velocity.
	exploitation_velocity        = 256.0;				// Best solution exploitation probability - Excalation velocity.
	exploitation_probability_max =   1.0;				// Best solution exploitation probability - Maximum probability.
	iteration                    =   0;                 // Loop monitoring                        - Iteration counter.
	iteration_sample             =   0;                 // Loop monitoring                        - Last iteration sample.

	// Configure heart beat. Just set 'heart_beat_frequency' in milliseconds.

	heart_beat_frequency = 100;							// Time - Heart beat frequency.
	elapsed_time         = 0;							// Time - We will start counting from t = 0 miliseconds.	
	heart_beat           = 0;							// Time - HEart beat.

	// Configure execution time.

	execution_time_hours        = 0;					// Execution time - Set hours.
	execution_time_minutes      = 10;					// Execution time - Set minutes.
	execution_time_seconds      = 0;					// Execution time - Set seconds.
	execution_time_milliseconds = 0; 					// Execution time - Set milliseconds.	

	// Compute total execution duration in milliseconds.

	duration_m  = execution_time_minutes      + execution_time_hours * 60;
	duration_s  = execution_time_seconds      + duration_m * 60;					
	duration_ms = execution_time_milliseconds + duration_s * 1000;					

	// Initialize output streams.

	write_csv_header ( data_file_name );
	cout << "Planned execution duration: " << StaticUtility::time_to_string ( duration_ms ) << endl << endl;	

	// Execute annealing algorythm.

	solution      = initialize_solution ( solution );
	best_solution = solution;
			
	while ( time < duration_ms )
	{
		// Start the timer.

		steady_clock::time_point timer_start = steady_clock::now ();

		// Convert time to normalized itteration index.

		k = (double) time / (double) duration_ms;

		// Compute the temperature and temperature schedule.

		temperature           = compute_temperature           ( k );
		insulated_temperature = compute_insulated_temperature ( temperature, temperature_min, cooling_velocity, temperature_scale );

		// Generate a new candidate solution.

		candidate_solution = generate_candidate_solution ( solution, insulated_temperature );

		// Compute solution energies.

		solution_min_energy       = compute_solution_energy ( best_solution );
		solution_energy           = compute_solution_energy ( solution );		
		candidate_solution_energy = compute_solution_energy ( candidate_solution );		
		
		// Compare solution energies, and transition if the transition probability is high enough.

		transition_probability = compute_acceptance_probability ( solution_energy, candidate_solution_energy, temperature );
		random_number          = random_distribution    ( random_generator );

		// Move to candidate solution.

		if ( transition_probability > random_number )
		{
			solution = candidate_solution;

			// Save best solution so far.

			if ( candidate_solution_energy < solution_min_energy )
			{				
				best_solution = candidate_solution;
				
				write_logfile ( log_file_name, (long) time, solution.hypothesis [ 0 ] );
			}
		}
		else
		{
			// Exploit best solution found so far.

			exploitation_probability = compute_exploitation_probability ( k, exploitation_velocity, exploitation_probability_max );

			if ( exploitation_probability > random_number )
			{
				solution = best_solution;
			}
		}

		// Stop the clock and calculate the elappsed time.

		steady_clock::time_point timer_stop = steady_clock::now ();					// Stop the timer.
		steady_clock::duration   duration   = timer_stop - timer_start;				// Calculate elapsed time.
		elapsed_time    = duration_cast < milliseconds > ( duration ).count ( );	// Convert from duration to an integer.
		time           += elapsed_time;												// Update current time step.

		// Update heart beat.

		heart_beat += elapsed_time;
		if ( heart_beat > heart_beat_frequency )
		{
			eta = duration_ms - time;

			write_heart_beat         ( log_file_name, time, eta, iteration, iteration_sample );			
			write_itteration_results ( data_file_name, (long) time, exploitation_probability, solution.hypothesis[0], best_solution.hypothesis[0] );	

			heart_beat = 0;
			iteration_sample = iteration;
		}

		// Update iteration counter.

		++iteration;
	}

	// Force solution to be the best solution we have found so far. This is usefull for short runs that may not converge consistantly.

	solution_energy     = compute_solution_energy ( solution );	
	solution_min_energy = compute_solution_energy ( best_solution );

	if ( solution_min_energy < solution_energy )
	{
		solution = best_solution;
	}
	write_itteration_results ( data_file_name, (long) time, exploitation_probability, solution.hypothesis[0], best_solution.hypothesis[0] );	
		
	// Close files.

	write_logfile ( log_file_name, (long) time, solution.hypothesis [ 0 ] );			
	data_file.close  ();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::write_csv_header (	string file_name )
{
	// Declare local variables.

	string delimiter { ',' };

	// Open file for appending.

	ofstream file;
	file.open ( file_name, ios_base::app );

	// Write to file.

	file << "Time"  << delimiter;
	file << "P(ex)" << delimiter;
	file << "S"     << delimiter;
	file << "SB"    << endl;

	// Close file.

	file.close ();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::write_itteration_results ( string file_name, long long time, double p_exploit, double solution, double best_solution )
{
	// Declare local variables.

	string delimiter { ',' };

	// Open file for appending.

	ofstream file;
	file.open ( file_name, ios_base::app );

	// Write to file.

	file << time           << delimiter;
	file << p_exploit      << delimiter;
	file << solution       << delimiter;
	file << best_solution  << endl;
	
	// Close file.

	file.close ();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::write_logfile ( string file_name, long long time, double data )
{
	// Declare local variables.

	int    low_precision       = 3;
	int    high_precision      = 6;
	int    low_precision_width = 5;
	int    high_precision_with = 8;
	char   delimiter           = '\t';
	char   padding             = ' ';
	string flag                = " *";

	// Open file for appending.

	ofstream log_file;
	log_file.open ( file_name, ios_base::app );
	
	// Write to log file.

	log_file << StaticUtility::time_to_string ( time ) << flag << delimiter << "argmax(f) = "; 	
	log_file << setfill ( padding ) << setw ( low_precision_width ) << setprecision ( low_precision  ) << fixed << data << delimiter;
	log_file << setfill ( padding ) << setw ( high_precision_with ) << setprecision ( high_precision ) << fixed << data << delimiter;
	log_file << (int)  (data*255) << delimiter;
	log_file << (char) (data*255);
	log_file << endl;

	// Close file.

	log_file.close ();

	// Write to console.

	cout << StaticUtility::time_to_string ( time ) << flag << delimiter << "argmax(f) = "; 	
	cout << setfill ( padding ) << setw ( low_precision_width ) << setprecision ( low_precision  ) << fixed << data << delimiter;	
	cout << setfill ( padding ) << setw ( high_precision_with ) << setprecision ( high_precision ) << fixed << data << delimiter;	
	cout << (int)  (data*255) << delimiter;
	cout << (char) (data*255);
	cout << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::write_heart_beat ( string file_name, long long time, long long eta, long long iteration, long long iteration_sample )
{
	// Declare local variables.

	long iterations_per_heart_beat { (long) ( iteration - iteration_sample ) };

	// Open file for appending.

	ofstream file;
	file.open ( file_name, ios_base::app );

	// Write to file.

	file << StaticUtility::time_to_string ( time ) << "\t" << iteration << " (" << iterations_per_heart_beat << ")";
	file << "\t" << "ETA = " << StaticUtility::time_to_string (eta);
	file << endl;

	// Close file.

	file.close ();

	// Write to console.

	cout << StaticUtility::time_to_string ( time ) << "\t" << iteration << " (" << iterations_per_heart_beat << ")";
	cout << "\t" << "ETA = " << StaticUtility::time_to_string (eta);
	cout << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::clear_file ( string file_name )
{
	ofstream file;
	file.open ( file_name );
	file.close ();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void TrainingEngine::print_program_info ()
{
	cout << endl;
	cout << "Program: Simulated Annealing - ANN Trainer" << endl;
	cout << "Version: 1.0"                               << endl;
	cout << "Date:    2015-08-12"                        << endl;
	cout << "Author:  Rohin Gosling"                     << endl;
	cout << endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION:
//
// - xxx
//
// DESCRIPTION:
//
// - xxx
//
// ARGUMENTS:
//
// - xxx
//   xxx
//
// RETURN VALUE:
//
// - xxx
//
// PRE-CONDITIONS:
//
// - xxx
//   
// POST-CONDITIONS:
//
// - xxx
//
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

