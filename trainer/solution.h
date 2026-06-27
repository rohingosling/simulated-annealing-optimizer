//------------------------------------------------------------------------------------------------------------------------------------------
// Project:	    Machine Learning.
// Application: Simulated Annealing.
// Class:	    Solution
// Version:	    1.0
// Date:	    2015
// Author:	    Rohin Gosling
//
// Description:
//
//   Solution base class. Specific problem domains, should derive specific solution classes from Solution.
//
//------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include <cstdint>

using namespace std;

class Solution
{

public:

	Solution ();
	~Solution ();

public:

	virtual double compute_cost ();

public:

	vector <double> hypothesis;	
};

