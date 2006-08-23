#pragma once

#include <cmath>
#include <cassert>

class Vector2D
{
public:
	double x;
	double y;

public:
	inline Vector2D( void )
		: x(0), y(0)
	{
	}

	inline Vector2D( const Vector2D &vec )
		: x(vec.x), y(vec.y)
	{
	}

	inline Vector2D( const Vector2D *vec )
		: x(vec->x), y(vec->y)
	{
	}

	inline Vector2D( const double fX, const double fY )
		: x(fX), y(fY)
	{
	}

	inline Vector2D operator + ( const Vector2D &vec ) const
	{
		Vector2D result;

		result.x = this->x + vec.x ;
		result.y = this->y + vec.y;

		return result;
	}

	inline Vector2D operator - ( const Vector2D &vec ) const
	{
		Vector2D result;

		result.x = this->x - vec.x;
		result.y = this->y - vec.y;

		return result;
	}

	inline Vector2D operator * ( const double f ) const
	{
		Vector2D result;

		result.x = this->x * f;
		result.y = this->y * f;

		return result;
	}

	inline Vector2D operator * ( const Vector2D &vec ) const
	{
		Vector2D result;

		result.x = this->x * vec.x;
		result.y = this->y * vec.y;

		return result;
	}

	inline Vector2D operator / ( const double f ) const
	{
		Vector2D result;

		result.x = this->x / f;
		result.y = this->y / f;

		return result;
	}

	inline Vector2D operator / ( const Vector2D &vec ) const
	{
		Vector2D result;

		result.x = this->x / vec.x;
		result.y = this->y / vec.y;

		return result;
	}

	inline bool operator == ( const Vector2D &vec ) const
	{
		return (this->x == vec.x && this->y == vec.y);
	}

	inline bool operator != ( const Vector2D &vec ) const
	{
		return (this->x != vec.x || this->y != vec.y);
	}

	inline double operator [] ( int i ) const
	{
		assert( i < 2 );

		return *(&x+i);
	}

	inline double dotProduct( const Vector2D &vec ) const
	{
		return ( this->x*vec.x + this->y*vec.y );
	}

	inline double lenght(  ) const
	{
		return sqrt(this->x*this->x + this->y*this->y);
	}

	inline void normalize( )
	{
		double fLenght = sqrt(this->x*this->x + this->y*this->y);

		// Funciona para zero mas nao faz nada
		if( fLenght > 1e-08 )
		{
			double fLenghtInversion = 1.0 / fLenght;
			this->x *= fLenghtInversion;
			this->y *= fLenghtInversion;
		}
	}

	inline void invertDirection()
	{
		this->x *= -1;
		this->y *= -1;		
	}

public: // Constantes
	static const Vector2D ZERO;
	static const Vector2D UNIT_X;
	static const Vector2D UNIT_Y;
	static const Vector2D NEGATIVE_UNIT_X;
	static const Vector2D NEGATIVE_UNIT_Y;
};
