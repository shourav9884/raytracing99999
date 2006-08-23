#pragma once

#include "ColorRGBf.h"
#include "Image.h"
#include "Vector2D.h"

class Material
{
private:
	// Diffusa
	ColorRGBf diffuseColor;
	Image *diffuseMap;

	// Specular
	ColorRGBf specularColor;
	float specularLevel;
	double glossiness;
	float soften;
	Image *specularMap;

	// Ambiental
	ColorRGBf ambientColor;
	Image *ambientMap;

	// Reflexao
	float reflect;

	// Refracao
	float refract;
	float indexOfRefraction;

private:
	inline void initBaseAttributes()
	{
		this->specularLevel = 1.0f;
		this->glossiness = 1.0;
		this->soften = 1.0f;
		this->reflect = 0.0f;
		this->refract = 0.0f;
		this->indexOfRefraction = 1.0f;

		this->diffuseMap = NULL;
		this->specularMap = NULL;
		this->ambientMap = NULL;
	}

public:
	Material( void );
	Material( const ColorRGBf& aDiffuseColor, const ColorRGBf& aSpecularColor, const ColorRGBf& aAmbientColor);
	~Material( void );

	inline ColorRGBf &getDiffuseColor()
	{
		return this->diffuseColor;
	}

	inline void setDiffuseColor( const ColorRGBf &aColor )
	{
		this->diffuseColor = aColor;
	}

	inline ColorRGBf getDiffuseResult( Vector2D &aTextureUVCoordinates )
	{
		if( this->diffuseMap == NULL )
		{
			return this->diffuseColor;
		}
		else
		{
			ColorRGBub tempColor = this->diffuseMap->getPixel(static_cast<float>(aTextureUVCoordinates.x), static_cast<float>(aTextureUVCoordinates.y));
			return tempColor.toColorRGBf( );
		}
	}

	inline void setDiffuseMap( Image *aDiffuseMap )
	{
		this->diffuseMap = aDiffuseMap;
	}

	inline ColorRGBf &getSpecularColor()
	{
		return this->specularColor;
	}

	inline void setSpecularColor( const ColorRGBf &aColor )
	{
		this->specularColor = aColor;
	}

	inline ColorRGBf getSpecularResult( Vector2D &aTextureUVCoordinates )
	{
		if( this->specularMap == NULL )
		{
			return this->specularColor;
		}
		else
		{
			ColorRGBub tempColor = this->specularMap->getPixel(static_cast<float>(aTextureUVCoordinates.x), static_cast<float>(aTextureUVCoordinates.y));
			return tempColor.toColorRGBf( );
		}
	}

	inline void setSpecularMap( Image *aSpecularMap )
	{
		this->specularMap = aSpecularMap;
	}

	inline ColorRGBf &getAmbientColor()
	{
		return this->ambientColor;
	}

	inline void setAmbientColor( const ColorRGBf &aColor )
	{
		this->ambientColor = aColor;
	}

	inline ColorRGBf getAmbientResult( Vector2D &aTextureUVCoordinates )
	{
		if( this->ambientMap == NULL )
		{
			return this->ambientColor;
		}
		else
		{
			ColorRGBub tempColor = this->ambientMap->getPixel(static_cast<float>(aTextureUVCoordinates.x), static_cast<float>(aTextureUVCoordinates.y));
			return tempColor.toColorRGBf( );
		}
	}

	inline void setAmbientMap( Image *aAmbientMap )
	{
		this->ambientMap = aAmbientMap;
	}

	inline float getReflect() const
	{
		return this->reflect;
	}

	inline void setReflect(float aReflect)
	{
		this->reflect = aReflect;
	}

	inline float getSpecularLevel() const
	{
		return this->specularLevel;
	}

	inline void setSpecularLevel(float aSpecularLeve)
	{
		this->specularLevel = aSpecularLeve;
	}

	inline double getGlossiness() const
	{
		return this->glossiness;
	}

	inline void setGlossiness(double aGlossiness)
	{
		this->glossiness = aGlossiness;
	}

	inline float getSoften() const
	{
		return this->soften;
	}

	inline void setSoften(float aSoften)
	{
		this->soften = aSoften;
	}

	inline float getRefract()
	{
		return this->refract;
	}

	inline void setRefract( float aRefract )
	{
		this->refract = aRefract;
	}

	inline float getIndexOfRafraction( )
	{
		return this->indexOfRefraction;
	}

	inline void setIndexOfRefraction( float aIndexOfRefraction )
	{
		this->indexOfRefraction = aIndexOfRefraction;
	}
};
