
#pragma once

#include "solution.h"

#include <vector>
#include <cstdint>

using namespace std;

class TestFunction : public Solution
{
public:

	#define M_PI 3.14159265358979323846

	static const int C_WAVE_FUNCTION_COUNT = 4;

public:

	using FunctionParameters = struct
	{
		double amplitude;
		double frequency;
		double phase;
	};

	using WaveFunction = struct 
	{
		FunctionParameters parameters [ C_WAVE_FUNCTION_COUNT ];
	};


public:

	TestFunction ();
	~TestFunction ();

public:

	void   initialize_test_cases ();
	double compute_cost () override;

public:

	vector <WaveFunction> test_case;
};

