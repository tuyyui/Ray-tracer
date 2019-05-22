#pragma once
#ifndef Color_h
#define Color_h

class Color_t  {

public:
	int r, g, b;
	Color_t(int red, int green, int blue) : r(red), g(green), b(blue) {}
	Color_t scale_by(double scalar)const {
		scalar *= scalar;
		return Color_t(scalar * r, scalar * g, scalar * b);
	}
	Color_t operator *(double scalar)const {
		return Color_t(scalar * r, scalar * g, scalar * b);
	}
	Color_t operator +(const Color_t& rhs) const {
		return Color_t(r + rhs.r, g + rhs.g, b + rhs.b);
	}
};

#endif
