#include "TimeCounter.h"

#include <ctime>

double TimeCounter::getDeltaTime( )
{
	// Quantidade de clocks decorridos desde o inicio da aplicacao ate o INICIO deste passo (ou fim do passo anterior)
	static long clocksBeforePass = 0;
	// Quantidade de clocks decorridos desde o inicio da aplicacao ate o FIM deste passo
	long clocksAfterPass = clock();

	double deltaTime = ((double)(clocksAfterPass - clocksBeforePass)) / CLK_TCK;

	clocksBeforePass = clocksAfterPass;

	return deltaTime;
}
