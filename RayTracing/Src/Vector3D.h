#pragma once

#include <cmath>

#include <cassert>

class Vector3D
{	
public: // Constantes
	static const Vector3D ZERO;
	static const Vector3D UNIT_X;
	static const Vector3D UNIT_Y;
	static const Vector3D UNIT_Z;
	static const Vector3D NEGATIVE_UNIT_X;
	static const Vector3D NEGATIVE_UNIT_Y;
	static const Vector3D NEGATIVE_UNIT_Z;

public:
	double x;
	double y;
	double z;

public:
	inline Vector3D( void )
		: x(0), y(0), z(0)
	{
	}

	inline Vector3D( const Vector3D &vec )
		: x(vec.x), y(vec.y), z(vec.z)
	{
	}

	inline Vector3D( const Vector3D *vec )
		: x(vec->x), y(vec->y), z(vec->z)
	{
	}

	inline Vector3D( const double fX, const double fY, const double fZ )
		: x(fX), y(fY), z(fZ)
	{
	}

	inline Vector3D operator + ( const Vector3D &vec ) const
	{
		Vector3D result;

		result.x = this->x + vec.x ;
		result.y = this->y + vec.y;
		result.z = this->z + vec.z;

		return result;
	}

	inline Vector3D operator - ( const Vector3D &vec ) const
	{
		Vector3D result;

		result.x = this->x - vec.x;
		result.y = this->y - vec.y;
		result.z = this->z - vec.z;

		return result;
	}

	inline Vector3D operator * ( const double f ) const
	{
		Vector3D result;

		result.x = this->x * f;
		result.y = this->y * f;
		result.z = this->z * f;

		return result;
	}

	inline Vector3D operator * ( const Vector3D &vec ) const
	{
		Vector3D result;

		result.x = this->x * vec.x;
		result.y = this->y * vec.y;
		result.z = this->z * vec.z;

		return result;
	}

	inline Vector3D operator / ( const double f ) const
	{
		Vector3D result;

		result.x = this->x / f;
		result.y = this->y / f;
		result.z = this->z / f;

		return result;
	}

	inline Vector3D operator / ( const Vector3D &vec ) const
	{
		Vector3D result;

		result.x = this->x / vec.x;
		result.y = this->y / vec.y;
		result.z = this->z / vec.z;

		return result;
	}

	inline bool operator == ( const Vector3D &vec ) const
	{
		return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
	}

	inline bool operator != ( const Vector3D &vec ) const
	{
		return (this->x != vec.x || this->y != vec.y || this->z != vec.z);
	}

	inline double operator [] ( int i ) const
	{
		assert( i < 3 );

		return *(&x+i);
	}

	inline double dotProduct( const Vector3D &vec ) const
	{
		return ( this->x*vec.x + this->y*vec.y + this->z*vec.z );
	}

	inline double lenght(  ) const
	{
		return sqrt(this->x*this->x + this->y*this->y);
	}

	inline Vector3D crossProduct( const Vector3D &aVector ) const
	{
		Vector3D result;

		result.x = this->y*aVector.z - this->z*aVector.y;
		result.y = this->z*aVector.x - this->x*aVector.z;
		result.z = this->x*aVector.y - this->y*aVector.x;

		return result;
	}

	inline void normalize( )
	{
		double fLenght = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);

		// Funciona para zero mas nao faz nada
		if( fLenght > 1e-08 )
		{
			double fLenghtInversion = 1.0 / fLenght;
			this->x *= fLenghtInversion;
			this->y *= fLenghtInversion;
			this->z *= fLenghtInversion;
		}
	}

	inline Vector3D getNormalized( )
	{
		Vector3D result = (*this);
		result.normalize();
		
		return result;
	}

	inline void invertDirection()
	{
		this->x *= -1;
		this->y *= -1;
		this->z *= -1;
	}

	inline Vector3D getinvertedDirection()
	{
		Vector3D result = (*this);
		result.invertDirection();

		return result;
	}
	
};