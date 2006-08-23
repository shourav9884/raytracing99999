#include "Material.h"

Material::Material( void )
{
	this->initBaseAttributes();
}

Material::Material( const ColorRGBf& aDiffuseColor, const ColorRGBf& aSpecularColor, const ColorRGBf& aAmbientColor)
: diffuseColor(aDiffuseColor), specularColor(aSpecularColor), ambientColor(aAmbientColor)
{
	this->initBaseAttributes();
}


Material::~Material(void)
{
}
