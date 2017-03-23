#include <avr/io.h>
#include <util/delay.h>

#include <endat.h>


int main (void)
{

	config_endat();

	while(1) {

		_delay_ms(10);
		recieve_position();
	}
}