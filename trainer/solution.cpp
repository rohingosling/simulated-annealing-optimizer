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

#include "stdafx.h"
#include "solution.h"


Solution::Solution ()
{
}


Solution::~Solution ()
{
}

double Solution::compute_cost ()
{
	return 0.0;
}

