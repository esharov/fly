#ifndef __FLYMATH_HPP
#define __FLYMATH_HPP

#include "flydef.hpp"
#include <cmath>

#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
#endif

template<class type_a>
inline type_a Frac(type_a a)
{
	return a - floor(a);
}


inline r_t Zoom(r_t x, r_t x0, r_t x1, r_t y0, r_t y1)
{
	return (x - x0)/(x1 - x0)*(y1 - y0) + y0;
}

inline r_t Zoom(r_t x, r_t y0, r_t y1) { return Zoom(x, 0, 1, y0, y1); }

inline r_t Sin(r_t a)
{
	return sin(a/180.0*M_PI);
}

inline r_t Cos(r_t a)
{
	return cos(a/180.0*M_PI);
}

inline r_t Tan(r_t a)
{
	return tan(a/180.0*M_PI);
}

inline r_t Arcsin(r_t a)
{
	return asin(a)/M_PI*180;
}

inline r_t Arccos(r_t a)
{
	return acos(a)/M_PI*180;
}

inline r_t Arctan(r_t a)
{
	return atan(a)/M_PI*180;
}


#endif