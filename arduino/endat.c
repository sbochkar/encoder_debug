#include <avr/io.h>
#include <stdint.h>

#include <endat.h>


void config_endat() {

	/* Configure Timer for clock generation */
	// Configure the clock source to be system clock.
	TCCR0B |= _BV(CS00);

	// Set CTC mode & Toggle OCRA pin when compare event happens.
	TCCR0A = _BV(WGM01) | _BV(COM0A0);

	// OCR0A is 8-bit. 16MHz CPU clock.
	OCR0A = 79;	

	// Configure PORTD6 pin for clock output. In effect, enable clk signal.
	DDRD |= _BV(DDD6);

	// Configure PORTB5 as DATA pin
	DDRB |= _BV(DDB5);
	PORTB = 0xFF;

}

int recieve_position(void) {

	uint8_t clk_level = 0;
	uint8_t state = 0;



	uint8_t i;
	uint8_t test = 0;
	for(i=0; i<25; i++){
		test++;
	}
//	int i;
//	for(i=CMD_LEN-1; i>=0; i--) {
//
//		// Clock event is when TIFR0 is set
//		if (bit_is_set(TIFR0, OCF0A)) {
//
//			// State machine transitions are on the rising ede.
//			if (clk_level) {
//
//				if (state == 2) {
//					PORTB |= _BV(PORTB5);
//
//				} else if (state == 8){
//					
//					PORTB &= ~_BV(PORTB5);
//					state = 0;
//				}
//
//
//
//				clk_level = 0;
//				state++;
//			} else {
//				clk_level = 1;
//			}
//			
//			TIFR0 |= _BV(OCF0A);
//		}
//	}
	// Configure the clock source to be system clock.
	TCCR0B &= ~_BV(CS00);

}