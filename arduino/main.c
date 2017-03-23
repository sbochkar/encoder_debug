#include <avr/io.h>
#include <util/delay.h>

#include <avr/io.h>

#include <endat.h>


int main (void)
{


	config_endat();

	uint8_t i;
	uint8_t test = 0;
	while(1)

		for(i=0;i<10;i++){
			test++;
		}
		TCCR0B &= ~(_BV(CS00)|_BV(CS01)|_BV(CS02));
		//recieve_position();

}