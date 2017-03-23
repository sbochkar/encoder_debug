#ifndef ENDAT_H
#define ENDAT_H

#define CMD_LEN 6
#define NUM_STATES 18

#define ENC_SEND_POS 0x07
#define ENC_SEL_MEM 0x0E
#define ENC_REC_PARM 0x1C
#define ENC_SEND_PARM 0x23
#define ENC_REC_RST 0x2A
#define ENC_SEND_TST 0x15
#define ENC_REC_TST 0x31
#define TEST 0x2B


void config_endat(void);
int recieve_position(void);

#endif /* ENDAT_H */