#include <avr/io.h>
#include <stdint.h>

#include <endat.h>

#include <util/delay.h>

void config_endat() {

	/* Configure Timer for clock generation */
	// Configure the clock source to be system clock.
	//TCCR0B |= _BV(CS00);

	// Set CTC mode & Toggle OCRA pin when compare event happens.
	TCCR0A = _BV(WGM01) | _BV(COM0A0);

	// OCR0A is 8-bit. 16MHz CPU clock.
	OCR0A = 79;	

	// Configure PORTD6 pin for clock output. In effect, enable clk signal.
	DDRD |= _BV(DDD6);

	// Configure PORTB5 as DATA pin
	DDRB |= _BV(DDB5);

}

int recieve_position(void) {

	uint8_t clk_level = 1;
	uint8_t i;

	// Configure the clock source to be system clock.
	TCCR0B |= _BV(CS00);

	for(i=0; i<2*NUM_STATES; i++) {

		// Clock event is when TIFR0 is set
		// State machine transitions are on from high to low level.
		while(!bit_is_set(TIFR0, OCF0A));

		if (clk_level) {

			if (i == 2*2) {
				PORTB |= _BV(PORTB5);

			} else if (i >= 2*8){
				
				PORTB &= ~_BV(PORTB5);
			}

			clk_level = 0;
		} else {
			clk_level = 1;
		}
		
		TIFR0 |= _BV(OCF0A);
	}
	// Stop the timer counter
	TCCR0B &= ~_BV(CS00);
	// Reset the counter
	TCNT0 = 0x00;

	// Reset Clock pin to high as initial condition.
	if (!bit_is_set(PIND, PIND6)) {
		TCCR0B |= _BV(FOC0A);
	}
}