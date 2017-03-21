#define ENC_SEND_POS 0x07
#define ENC_SEL_MEM 0x0E
#define ENC_REC_PARM 0x1C
#define ENC_SEND_PARM 0x23
#define ENC_REC_RST 0x2A
#define ENC_SEND_TST 0x15
#define ENC_REC_TST 0x31

#define CMD_LEN 6

#include <avr/io.h>
#include <util/delay.h>


void send_cmd(unsigned int msg) {


	/* set pin 5 of PORTB for output*/
	DDRB |= _BV(DDB3);
	DDRB |= _BV(DDB4);


	unsigned int msg;
	msg = TEST;

	while(1) {
		clock_pulse();
		clock_pulse();

		int i;
		for(i=CMD_LEN-1; i>=0; i--) {

			PORTB &= ~_BV(CLK);
			if ((msg>>i)&0x1) {
				PORTB |= _BV(DAT);
			} else {
				PORTB &= ~_BV(DAT);
			}
			_delay_us(CLOCK_PERIOD_US);

			PORTB |= _BV(CLK);
			_delay_us(CLOCK_PERIOD_US);
		}

		PORTB &= ~_BV(DAT);
		for(i=0; i<10; i++) {
			clock_pulse();
		}

		_delay_us(100);		
//		PORTB |= _BV(CLK);
//		PORTB |= _BV(DAT);
//		_delay_us(CLOCK_PERIOD_US);
//
//		PORTB &= ~_BV(CLK);
//		PORTB &= ~_BV(DAT);
//		_delay_us(CLOCK_PERIOD_US);
//
//		PORTB |= _BV(CLK);
//		_delay_us(CLOCK_PERIOD_US);
//
//		PORTB &= ~_BV(CLK);
//		_delay_us(CLOCK_PERIOD_US);
	}






//	clock_pulse();
//	clock_pulse();
//
//	for(int i=CMD_LEN-1; i>=0; i--) {
//
//		clr_pin(CLK_PIN);
//		(msg>>i)&0x1 ? set_pin(SDA_PIN) : clr_pin(SDA_PIN);
//		usleep(10);
//
//		set_pin(CLK_PIN);
//		usleep(10);
//	}
//
//	for(int i=0; i<10; i++) {
//		clock_pulse();
//	}

}

inline void clock_pulse(void) {

	PORTB &= ~_BV(CLK);
	_delay_us(CLOCK_PERIOD_US);
	PORTB |= _BV(CLK);
	_delay_us(CLOCK_PERIOD_US);
}