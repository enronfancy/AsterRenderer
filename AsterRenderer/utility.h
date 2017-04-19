#pragma once

#include <assert.h>

template <typename T>
bool inRange(T& value, T lower, T upper, T increment)
{
	//assert(lower <= upper);
	bool inRange = false;
	
	if(lower < upper)
	{
		inRange = (value >= lower &&  value < upper);
	}
	else
	{
		inRange = (value > upper &&  value <= lower);
	}

	return inRange;
}
