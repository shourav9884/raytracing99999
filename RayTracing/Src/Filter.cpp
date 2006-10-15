#include "Filter.h"

#include <cmath>
using namespace std;

Filter::Filter( int aMaskSize, int aWidth, int aHeight )
: width(aWidth), height(aHeight)
{
	// Aloca buffer que será utilizado para computar o DoF
	this->bufferDoF = new ColorAmount[aWidth*aHeight];

	// Inicializa buffer
	for( int i = 0 ; i < this->width*this->height; i++ )
	{
		this->bufferDoF[i].color = ColorRGBf(0.0,0.0,0.0);
		this->bufferDoF[i].amount = 0;
	}

	// Inicializa o array que contem a quantidade de pixels que um CoC de raio CoCRay
	// possui
	for( int CoCRay = 0; CoCRay <= this->CoCMaxRay; CoCRay++)
	{
		// Variável temporaria
		int pixelsAmountInCoC = 0;

		// Varre o "Quadrado de Confusao"
		for( int x = -CoCRay; x <= CoCRay; x++ )
		{
			for( int y = -CoCRay; y <= CoCRay; y++ )
			{
				int pointDistance = x*x + y*y;

				// Checa se ponto está dentro do CoC
				if( pointDistance <= CoCRay*CoCRay )
				{
					pixelsAmountInCoC += 1;
				}
			}
		}

		// Atualiza array
		this->pixelsAmountInCoCWithRay[CoCRay] = pixelsAmountInCoC;
	}
}

void Filter::filterDoF( FrameBuffer* aFrameBuffer, float aDoFFocusedDistance, float aDoFLensAperture, float aDoFProjectionPlanedistance , float aZNear, float aZFar)
{
	int imageSize = this->width * this->height;

	// Distancia focada
	float P = aDoFFocusedDistance;
	// Abertura da lente
	float E = aDoFLensAperture;
	// Distancia do plano de projecao
	float VP = aDoFProjectionPlanedistance;
	// Distancia focal da lente
	//float F = 1.0f/(1.0f/P + 1.0f/VP);
	float F = (P * VP)/(P + VP);

	for( int x = 0; x < this->width; x++ )
	{
		for( int y = 0; y < this->height; y++ )
		{	
			// Distancia do pixel
			float D = aFrameBuffer->zBuffer[x + y*this->width];

			// Distancia da imagem do pixel
			float VD = (F*D)/(D-F);

			// Diametro do circulo de confusao do pixel
			float CoCDiameter = (abs(VD - VP) * E/VD);

			this->uniformDistribution( CoCDiameter, P, x, y, aFrameBuffer, this->bufferDoF, aZNear, aZFar);
		}
	}

	for( int i = 0; i < imageSize; i++ )
	{
		aFrameBuffer->colorBuffer[i] = this->bufferDoF[i].color/this->bufferDoF[i].amount;

		// Reseta buffer temporário
		this->bufferDoF[i].color = ColorRGBf(0.0,0.0,0.0);
		this->bufferDoF[i].amount = 0;
	}
}

void Filter::uniformDistribution( float aCoCDiameter, float aFocusedDistance, int aXPixel, int aYPixel, FrameBuffer* aSrcBuffer , Filter::ColorAmount* aDstBuffer, float aZNear, float aZFar)
{
	// Raio do CoC
	int CoCRay = (int)(aCoCDiameter/2);

	// Garante que o raio do CoC tenha um tamanho maximo de this->CoCMaxRay
	if( CoCRay > this->CoCMaxRay )
		CoCRay = this->CoCMaxRay;

	// Intensidade da cor distribuida
	ColorRGBf tempIntensity = aSrcBuffer->colorBuffer[aXPixel + aYPixel * this->width]/static_cast<float>(this->pixelsAmountInCoCWithRay[CoCRay]);
	// Peso da cor (para tirar a media aritmetica ponderada)
	float tempWeight = (1.0f/this->pixelsAmountInCoCWithRay[CoCRay]);

	float centerDistance = aSrcBuffer->zBuffer[aXPixel + aYPixel * this->width];
	int CoCRayPow = CoCRay*CoCRay;

	// Percorre o "Quadrado de confusao"
	for( int x = -CoCRay; x <= CoCRay; x++ )
	{
		for( int y = -CoCRay; y <= CoCRay; y++ )
		{			
			int tempX = x + aXPixel;
			int tempY = y + aYPixel;

			// Indice do array (posicao do pixel)
			int tempDesloc = tempX + (tempY * this->width);

			if( tempX >= 0 && tempX < this->width && tempY >= 0 && tempY < this->height )
			{
				// Trata só os pixels que estiverem dentro do CoC
				if( (x*x + y*y) <= CoCRayPow )
				{
					// Fator que tenta corrigir o problema de objetos longes desfocados
					// embacarem as bordas de objetos focados. Quanto mais um pixels estiver proximo
					// da distancia focada, menos ele sofrerá influência do espalhamento
					// dos dos CoC do background
					float borderDistance = aSrcBuffer->zBuffer[tempDesloc];
					float focusedFactor = 1.0f;
					if( centerDistance > borderDistance )
					{
						if( borderDistance > aFocusedDistance )
							//deltaDistance = abs((borderDistance - aFocusedDistance)/(aZFar - aFocusedDistance));
							focusedFactor = 1.0f - (borderDistance - aFocusedDistance)/(aZFar - aFocusedDistance);
						else
							//deltaDistance = abs((borderDistance - aFocusedDistance)/(aZNear - aFocusedDistance));
							focusedFactor = 1.0f - (aFocusedDistance - borderDistance)/(aFocusedDistance - aZNear);
					}

					// Pinta os pixels dentro do CoC
					aDstBuffer[tempDesloc].color = aDstBuffer[tempDesloc].color + tempIntensity * focusedFactor;
					aDstBuffer[tempDesloc].amount += tempWeight * focusedFactor;
				}
			}
		}
	}
}
