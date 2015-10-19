#ifndef __FLY_VECTOR_HPP
#define __FLY_VECTOR_HPP

#include <cmath>
//#include <cassert>


#ifndef M_PI
#define M_PI    3.14159265358979323846264338327950288   /* pi */
//#define M_PI           3.14159265358979323846  /* pi */
#endif

#define DEG2RAD(x) ((x * M_PI) / 180.0)
//#define EPSILON (4.37114e-07)

const double epsilon = 4.37114e-05;
#define EPSILON epsilon

template<class T>
struct vector2_c
{
	T x;
	T y;

	vector2_c(T a = 0) : x(a), y(a) {}
	vector2_c(T nx, T ny)
			: x(nx), y(ny)
	{
	}

	/**
	 * Copy constructor.
	 * @param src Source of data for new created instance.
	 */
	vector2_c(const vector2_c<T>& src)
			: x(src.x), y(src.y)
	{
	}

	/**
	 * Copy casting constructor.
	 * @param src Source of data for new created instance.
	 */
	template<class FromT>
	vector2_c(const vector2_c<FromT>& src)
			: x(static_cast<T>(src.x)), y(static_cast<T>(src.y))
	{
	}

	static vector2_c<T>& zero() 
	{ 
		static vector2_c<T> data;
		return data; 
	}

	/**
	 * Copy casting operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	vector2_c<T>& operator=(const vector2_c<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		return *this;
	}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator=(const vector2_c<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, else reference to y 
	 * y coordinate.
	 */
	/*
	T& operator[](int n)
	{
		assert(n >= 0 && n <= 1);
		if (0 == n)
			return x;
		else
			return y;
	}
	*/

	/**
	 * Constant array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, else reference to y
	 * y coordinate.
	 */
	/*
	const T& operator[](int n) const
	{
		assert(n >= 0 && n <= 1);
		if (0 == n)
			return x;
		else
			return y;
	}
	*/

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator+(const vector2_c<T>& rhs) const
	{
		return vector2_c<T>(x + rhs.x, y + rhs.y);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator-(const vector2_c<T>& rhs) const
	{
		return vector2_c<T>(x - rhs.x, y - rhs.y);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator*(const vector2_c<T>& rhs) const
	{
		return vector2_c<T>(x * rhs.x, y * rhs.y);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator/(const vector2_c<T>& rhs) const
	{
		return vector2_c<T>(x / rhs.x, y / rhs.y);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator+=(const vector2_c<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/**
	 * Substraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator-=(const vector2_c<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator*=(const vector2_c<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator/=(const vector2_c<T>& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	//--------------[ scalar vector operator ]--------------------
	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator+(T rhs) const
	{
		return vector2_c<T>(x + rhs, y + rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator-(T rhs) const
	{
		return vector2_c<T>(x - rhs, y - rhs);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator*(T rhs) const
	{
		return vector2_c<T>(x * rhs, y * rhs);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T> operator/(T rhs) const
	{
		return vector2_c<T>(x / rhs, y / rhs);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator+=(T rhs)
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator-=(T rhs)
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector2_c<T>& operator/=(T rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs.x - rhs.y | < EPSILON,
	 * same for y-coordinate.
	 */
	bool operator==(const vector2_c<T>& rhs) const
	{
		return (std::abs(x - rhs.x) < EPSILON) && (std::abs(y - rhs.y) < EPSILON);
	}

	bool operator==(const T a) const
	{
		return x == a && y == a;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const vector2_c<T>& rhs) const
	{
		return !(*this == rhs);
	}

	vector2_c<T> operator-() const
	{
		return vector2_c<T>(-x, -y);
	}
};

template<class T> inline T Square(const vector2_c<T> o) { return o.x*o.x + o.y*o.y; }

template<class T> inline T Abs(const vector2_c<T> o) { return(T) std::sqrt( Square(o) ); }

template<class T> inline vector2_c<T> Trend(const vector2_c<T> o) 
{ 
	T a = Abs(o);
	return vector2_c<T>(o.x/a, o.y/a); 
}

template<class T>
inline vector2_c<T> Min(const vector2_c<T> b, const vector2_c<T> a)
{
	return vector2_c<T>( Min(b.x, a.x) , Min(b.y, a.y) );
}

template<class T>
inline vector2_c<T> Max(const vector2_c<T> b, const vector2_c<T> a)
{
	return vector2_c<T>( Max(b.x, a.x) , Max(b.y, a.y) );
}

/**
 * Class for three dimensional vector.
 * There are four ways of accessing vector components.
 * Let's have <code>Vector3f v</code>, you can either:
 * <ul>
 * 	<li>access as position (x,y,z) &mdash; <code>v.x = v.y = v.z = 1;</code></li>
 * 	<li>access as texture coordinate (s,t,u) &mdash; <code>v.s = v.t = v.u = 1;</code></li>
 * 	<li>access as color (r,g,b) &mdash; <code>v.r = v.g = v.b = 1;</code></li>
 * 	<li>access via operator[] &mdash; <code>v[0] = v[1] = v[2] = 1;</code></li>
 * </ul>
 */
template<class T>
class vector3_c
{
public:
	
	T x;
	T y;
	T z;


	/**
	 * Creates and sets to (0,0,0)
	 */
	vector3_c()
			: x(0), y(0), z(0)
	{
	}

	/**
	 * Creates and sets to (x,y,z)
	 * @param nx initial x-coordinate value
	 * @param ny initial y-coordinate value
	 * @param nz initial z-coordinate value
	 */
	vector3_c(T nx, T ny, T nz)
			: x(nx), y(ny), z(nz)
	{
	}

	/**
	 * Copy constructor.
	 * @param src Source of data for new created vector3_c instance.
	 */
	vector3_c(const vector3_c<T>& src)
			: x(src.x), y(src.y), z(src.z)
	{
	}

	/**
	 * Copy casting constructor.
	 * @param src Source of data for new created vector3_c instance.
	 */
	template<class FromT>
	vector3_c(const vector3_c<FromT>& src)
			: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z))
	{
	}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator=(const vector3_c<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	/**
	 * Copy casting operator.
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	vector3_c<T> operator=(const vector3_c<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		return *this;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y, else reference to z 
	 * y coordinate.
	 */
	T & operator[](int n)
	{
		assert(n >= 0 && n <= 2);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else
			return z;
	}

	/**
	 * Constant array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y, else reference to z
	 * y coordinate.
	 */
	const T & operator[](int n) const
	{
		assert(n >= 0 && n <= 2);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else
			return z;
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator+(const vector3_c<T>& rhs) const
	{
		return vector3_c<T>(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator-(const vector3_c<T>& rhs) const
	{
		return vector3_c<T>(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator*(const vector3_c<T>& rhs) const
	{
		return vector3_c<T>(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator/(const vector3_c<T>& rhs) const
	{
		return vector3_c<T>(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator+=(const vector3_c<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator-=(const vector3_c<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator*=(const vector3_c<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator/=(const vector3_c<T>& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	/**
	 * Dot product of two vectors.
	 * @param rhs Right hand side argument of binary operator.
	 */
	T dotProduct(const vector3_c<T>& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	/**
	 * Cross product operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> crossProduct(const vector3_c<T>& rhs) const
	{
		return vector3_c<T>(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x, x * rhs.y - rhs.x * y);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator+(T rhs) const
	{
		return vector3_c<T>(x + rhs, y + rhs, z + rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator-(T rhs) const
	{
		return vector3_c<T>(x - rhs, y - rhs, z - rhs);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator*(T rhs) const
	{
		return vector3_c<T>(x * rhs, y * rhs, z * rhs);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T> operator/(T rhs) const
	{
		return vector3_c<T>(x / rhs, y / rhs, z / rhs);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator+=(T rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator-=(T rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector3_c<T>& operator/=(T rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs.x - rhs.y | < EPSILON,
	 * same for y-coordinate, and z-coordinate.
	 */
	bool operator==(const vector3_c<T>& rhs) const
	{
		return std::fabs(x - rhs.x) < EPSILON && std::fabs(y - rhs.y) < EPSILON && std::fabs(z - rhs.z) < EPSILON;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const vector3_c<T>& rhs) const
	{
		return !(*this == rhs);
	}

	/**
	 * Unary negate operator
	 * @return negated vector
	 */
	vector3_c<T> operator-() const
	{
		return vector3_c<T>(-x, -y, -z);
	}

	//-------------[ size operations ]---------------------------
	/**
	 * Get length of vector.
	 * @return lenght of vector
	 */
	T length() const
	{
		return (T) std::sqrt(x * x + y * y + z * z);
	}

	/**
	 * Return square of length.
	 * @return length ^ 2
	 * @note This method is faster then length(). For comparison
	 * of length of two vector can be used just this value, instead
	 * of more expensive length() method.
	 */
	T lengthSq() const
	{
		return x * x + y * y + z * z;
	}

	/**
	 * Normalize vector
	 */
	void normalize()
	{
		T s = length();
		x /= s;
		y /= s;
		z /= s;
	}

	//------------[ other operations ]---------------------------
	/**
	 * Rotate vector around three axis.
	 * @param ax Angle (in degrees) to be rotated around X-axis.
	 * @param ay Angle (in degrees) to be rotated around Y-axis.
	 * @param az Angle (in degrees) to be rotated around Z-axis.
	 */
	void rotate(T ax, T ay, T az)
	{
		T a = cos(DEG2RAD(ax));
		T b = sin(DEG2RAD(ax));
		T c = cos(DEG2RAD(ay));
		T d = sin(DEG2RAD(ay));
		T e = cos(DEG2RAD(az));
		T f = sin(DEG2RAD(az));
		T nx = c * e * x - c * f * y + d * z;
		T ny = (a * f + b * d * e) * x + (a * e - b * d * f) * y - b * c * z;
		T nz = (b * f - a * d * e) * x + (a * d * f + b * e) * y + a * c * z;
		x = nx;
		y = ny;
		z = nz;

	}

	/**
	 * Linear interpolation of two vectors
	 * @param fact Factor of interpolation. For translation from positon
	 * of this vector to vector r, values of factor goes from 0.0 to 1.0.
	 * @param r Second Vector for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	vector3_c<T> lerp(T fact, const vector3_c<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	//-------------[ conversion ]-----------------------------

	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class vector3_c<T>)
	 * used for passing vector3_c<T> values to gl*3[fd] functions.
	 */
	operator T*()
	{
		return (T*) this;
	}

	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class vector3_c<T>)
	 * used for passing vector3_c<T> values to gl*3[fd] functions.
	 */
	operator const T*() const
	{
		return (const T*) this;
	}
};


/**
 * Class for four dimensional vector.
  * There are four ways of accessing vector components.
 * Let's have <code>Vector4f v</code>, you can either:
 * <ul>
 * 	<li>access as position in projective space (x,y,z,w) &mdash; <code>v.x = v.y = v.z = v.w = 1;</code></li>
 * 	<li>access as texture coordinate (s,t,u,v) &mdash; <code>v.s = v.t = v.u = v.v = 1;</code></li>
 * 	<li>access as color (r,g,b,a) &mdash; <code>v.r = v.g = v.b = v.a = 1;</code></li>
 * 	<li>access via operator[] &mdash; <code>v[0] = v[1] = v[2] = v[3] = 1;</code></li>
 * </ul>
 */
template<class T>
class vector4_c
{
public:

	T x;
	T y;
	T z;
	T w;

	/**
	 * Creates and sets to (0,0,0,0)
	 */
	vector4_c(T a = 0)
			: x(a), y(a), z(a), w(a)
	{
	}

	/**
	 * Creates and sets to (x,y,z,z)
	 * @param nx initial x-coordinate value (R)
	 * @param ny initial y-coordinate value (G)
	 * @param nz initial z-coordinate value (B)
	 * @param nw initial w-coordinate value (Alpha)
	 */
	vector4_c(T nx, T ny, T nz, T nw)
			: x(nx), y(ny), z(nz), w(nw)
	{
	}

	/**
	 * Copy constructor.
	 * @param src Source of data for new created vector4_c instance.
	 */
	vector4_c(const vector4_c<T>& src)
			: x(src.x), y(src.y), z(src.z), w(src.w)
	{
	}

	/**
	 * Copy casting constructor.
	 * @param src Source of data for new created vector4_c instance.
	 */
	template<class FromT>
	vector4_c(const vector4_c<FromT>& src)
			: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z)), w(static_cast<T>(src.w))
	{
	}

	vector4_c(const vector3_c<T>& src, T w)
		: x(src.x), y(src.y), z(src.z), w(w)
    {}

	template <typename FromT>
	vector4_c(const vector3_c<FromT>& src, FromT w)
		: x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z)), w(static_cast<T>(w))
    {}

	/**
	 * Copy operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator=(const vector4_c<T>& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	/**
	 * Copy casting operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	template<class FromT>
	vector4_c<T> operator=(const vector4_c<FromT>& rhs)
	{
		x = static_cast<T>(rhs.x);
		y = static_cast<T>(rhs.y);
		z = static_cast<T>(rhs.z);
		w = static_cast<T>(rhs.w);
		return *this;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y coordinate, n = 2 reference to z,  
	 * else reference to w coordinate.
	 */
	T & operator[](int n)
	{
		assert(n >= 0 && n <= 3);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else if (2 == n)
			return z;
		else
			return w;
	}

	/**
	 * Array access operator
	 * @param n Array index
	 * @return For n = 0, reference to x coordinate, n = 1
	 * reference to y coordinate, n = 2 reference to z,
	 * else reference to w coordinate.
	 */
	const T & operator[](int n) const
	{
		assert(n >= 0 && n <= 3);
		if (0 == n)
			return x;
		else if (1 == n)
			return y;
		else if (2 == n)
			return z;
		else
			return w;
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator+(const vector4_c<T>& rhs) const
	{
		return vector4_c<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator-(const vector4_c<T>& rhs) const
	{
		return vector4_c<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator*(const vector4_c<T> rhs) const
	{
		return vector4_c<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator/(const vector4_c<T>& rhs) const
	{
		return vector4_c<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator+=(const vector4_c<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator-=(const vector4_c<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator*=(const vector4_c<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator/=(const vector4_c<T>& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	/**
	 * Equality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @note Test of equality is based of threshold EPSILON value. To be two
	 * values equal, must satisfy this condition | lhs.x - rhs.y | < EPSILON,
	 * same for y-coordinate, z-coordinate, and w-coordinate.
	 */
	bool operator==(const vector4_c<T>& rhs) const
	{
		return std::fabs(x - rhs.x) < EPSILON && std::fabs(y - rhs.y) < EPSILON && std::fabs(z - rhs.z) < EPSILON
				&& std::fabs(w - rhs.w) < EPSILON;
	}

	/**
	 * Inequality test operator
	 * @param rhs Right hand side argument of binary operator.
	 * @return not (lhs == rhs) :-P
	 */
	bool operator!=(const vector4_c<T>& rhs) const
	{
		return !(*this == rhs);
	}

	/**
	 * Unary negate operator
	 * @return negated vector
	 */
	vector4_c<T> operator-() const
	{
		return vector4_c<T>(-x, -y, -z, -w);
	}


	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator+(T rhs) const
	{
		return vector4_c<T>(x + rhs, y + rhs, z + rhs, w + rhs);
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator-(T rhs) const
	{
		return vector4_c<T>(x - rhs, y - rhs, z - rhs, w - rhs);
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator*(T rhs) const
	{
		return vector4_c<T>(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T> operator/(T rhs) const
	{
		return vector4_c<T>(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	/**
	 * Addition operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator+=(T rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		w += rhs;
		return *this;
	}

	/**
	 * Subtraction operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator-=(T rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		w -= rhs;
		return *this;
	}

	/**
	 * Multiplication operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator*=(T rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	/**
	 * Division operator
	 * @param rhs Right hand side argument of binary operator.
	 */
	vector4_c<T>& operator/=(T rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	/**
	 * Get length of vector.
	 * @return lenght of vector
	 */
	T length() const
	{
		return (T) std::sqrt(x * x + y * y + z * z + w * w);
	}

	/**
	 * Normalize vector
	 */
	void normalize()
	{
		T s = length();
		x /= s;
		y /= s;
		z /= s;
		w /= s;
	}

	/**
	 * Return square of length.
	 * @return length ^ 2
	 * @note This method is faster then length(). For comparison
	 * of length of two vector can be used just this value, instead
	 * of more expensive length() method.
	 */
	T lengthSq() const
	{
		return x * x + y * y + z * z + w * w;
	}

	/**
	 * Linear interpolation of two vectors
	 * @param fact Factor of interpolation. For translation from position
	 * of this vector to vector r, values of factor goes from 0.0 to 1.0.
	 * @param r Second Vector for interpolation 
	 * @note However values of fact parameter are reasonable only in interval
	 * [0.0 , 1.0], you can pass also values outside of this interval and you
	 * can get result (extrapolation?)
	 */
	vector4_c<T> lerp(T fact, const vector4_c<T>& r) const
	{
		return (*this) + (r - (*this)) * fact;
	}

	//-------------[ conversion ]-----------------------------

	/**
	 * Conversion to pointer operator
	 * @return Pointer to internally stored (in management of class vector4_c<T>)
	 * used for passing vector4_c<T> values to gl*4[fd] functions.
	 */
	operator T*()
	{
		return (T*) this;
	}

	/**
	 * Conversion to pointer operator
	 * @return Constant Pointer to internally stored (in management of class vector4_c<T>)
	 * used for passing vector4_c<T> values to gl*4[fd] functions.
	 */
	operator const T*() const
	{
		return (const T*) this;
	}

	operator vector3_c<T>&()
	{
		return reinterpret_cast<vector3_c<T>&>(*this);
	}

	/**
	 * Gets 3D vector. Note that the output is divided by w coordinate to apply projection
	 * transform. If the w coordinate is equal to zero, the result is not divided.
	 * @return (x/w, y/w, z/w) iff w != 0 otherwise (x,y,z)
	 */
	vector3_c<T> xyz() const
	{
		if (w == 0 || w == 1)
			return vector3_c<T>(x,y,z);

		const T invW = 1.0 / w;
		return vector3_c<T>(x * invW, y * invW, z * invW);
	}


};

	


#endif

