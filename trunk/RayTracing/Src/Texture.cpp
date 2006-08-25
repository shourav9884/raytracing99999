#include "Texture.h"

Texture::Texture( const char *aFileName, InterpolationType aInterpolationType )
: image( aFileName ), interpolationType(aInterpolationType)
{
}

Texture::~Texture(void)
{
}
