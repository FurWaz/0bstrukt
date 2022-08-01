#pragma once

class Common
{
public:
	template<class A> static A clamp(A val, A min, A max)
	{
		if (val > max) return max;
		if (val < min) return min;
		return val;
	}
};