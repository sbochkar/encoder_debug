#include <avr/io.h>
#include <util/delay.h>

#define ENC_SEND_POS 0x07
#define ENC_SEL_MEM 0x0E
#define ENC_REC_PARM 0x1C
#define ENC_SEND_PARM 0x23
#define ENC_REC_RST 0x2A
#define ENC_SEND_TST 0x15
#define ENC_REC_TST 0x31
#define TEST 0x2B

#define BLINK_DELAY_MS 1
#define CLOCK_PERIOD_US 2

#define CLK_PIN PORTB1
#define DAT PORTB3

#define CMD_LEN 6

#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_STATES 18


volatile int state_id;
int (*ss[NUM_STATES])(void);
//SS[0] = ;

int test_funk(void){
	return 1;
}


int main (void)
{
	// Configure the clock source to be system clock.
	TCCR0B = _BV(CS00);

	// Set CTC mode.
	// Toggle OCRA pin when compare event happens.
	TCCR0A = _BV(WGM01) | _BV(COM0A0);

	// Enable Compare A interrupt.
	//TIMSK0 = _BV(OCIE0A);

	// OCR0A is 8-bit. Set to 100 for toggling 100kHz clock.
	OCR0A = 79;

	DDRD = _BV(DDD6);


	state_id = 0;
	int i;
	for(i=0; i<NUM_STATES; i++) {
		ss[i] = test_funk;
	}
	// Configure flasing LED
	DDRB |= _BV(DDB5);

	//sei();

	int half_clk = 0;
	int state = 0;
	while(1){

		if (bit_is_set(TIFR0, OCF0A)) {
			if (half_clk) {

				if (state == 2) {
					PORTB |= _BV(PORTB5);

				} else if (state == 8){
					
					PORTB &= ~_BV(PORTB5);
					state = 0;
				}



				half_clk = 0;
				state++;
			} else {
				half_clk = 1;
			}
			
			TIFR0 |= _BV(OCF0A);
		}
	}
}

//				(*ss[state_id])();
//				state_id++;
//				if (state_id == NUM_STATES){
//					state_id = 0;
//				}

ISR(TIMER0_COMPA_vect)
{
	//(*ss[state_id])();
	state_id++;
	if (state_id == NUM_STATES){
		state_id = 0;
	}

	PORTB ^= _BV(PORTB5);
	reti();
}
