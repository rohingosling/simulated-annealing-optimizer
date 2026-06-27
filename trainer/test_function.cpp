#include "stdafx.h"
#include "test_function.h"

#include <vector>
#include <cstdint>
#include <math.h>

using namespace std;

//------------------------------------------------------------------------------------------------------------------------------------------

TestFunction::TestFunction ()
{
	// Initialize test cases.

	initialize_test_cases ();

	// Initialize hypothesis.

	this->hypothesis.push_back ( 1.0 );
}

//------------------------------------------------------------------------------------------------------------------------------------------

TestFunction::~TestFunction ()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

void TestFunction::initialize_test_cases ()
{
	// Initialize local variables.

	WaveFunction f;							// Function parameters.
	double       pi        { M_PI };		// Value of pi.
	int          fi        { 0 };			// Wave function index.
	double       amplitude { 0.0 };
	double       frequency { 0.0 };
	double       phase     { 0.0 };

	// Test configuration.

#if 1
	fi = 0;
	f.parameters [ fi++ ] = {  0.100, 	 1.000,   0.000 };
	f.parameters [ fi++ ] = {  1.500, 	64.000,   0.016 };
	f.parameters [ fi++ ] = {  0.990, 	96.000,   0.011 };
	f.parameters [ fi++ ] = {  0.653,  144.000,   0.007 };
#else
	amplitude =   1.0;
	frequency =  10.0;
	phase     =  -0.157;

	fi = 0;
	f.parameters [ fi++ ] = { amplitude, frequency, phase };
	f.parameters [ fi++ ] = { amplitude, frequency, phase };
	f.parameters [ fi++ ] = { amplitude, frequency, phase };
	f.parameters [ fi++ ] = { amplitude, frequency, phase };
#endif

	this->test_case.push_back ( f );
}

//------------------------------------------------------------------------------------------------------------------------------------------

double TestFunction::compute_cost () 
{
	// Calculate the number of constraints in this hypothesis.

	int constraint_count = this->hypothesis.size ();

	// Retrieve raw input data.

	double pi    { M_PI };
	double range { 1.0 };										// 255 for 8-bit data.
	double h     { this->hypothesis [ constraint_count - 1 ] };

	// Compute the normalized input parameter.

	double x = h / range;		// Normalize input data.
	double t = 2.0 * pi * x;	// Convert to radians.

	// Compute g(t)

	int test_case_id = 0;
	
	double gt { 0.0 };
	double a  { 0.0 };
	double f  { 0.0 };
	double p  { 0.0 };
	int    n  { C_WAVE_FUNCTION_COUNT };

	for ( int i = 0; i < n; i++ )
	{
		// Retrieve tast case data.

		a = this->test_case [ test_case_id ].parameters [ i ].amplitude;
		f = this->test_case [ test_case_id ].parameters [ i ].frequency;
		p = this->test_case [ test_case_id ].parameters [ i ].phase;

		// Compute wave function, g(t).

		gt += a * sin ( f * ( t + p ) );
	}

	// Compute f(t)

	double average = 1.0 / n;
	double scale   = 0.5;	
	double ft      = scale * ( 1.0 + average * gt );

	// Compute function cost.

	double cost = 1.0 - ft; 

	// return value.	

	return cost;
}

//------------------------------------------------------------------------------------------------------------------------------------------