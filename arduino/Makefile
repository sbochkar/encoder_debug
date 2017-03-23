IDIR = ./inc

CC = avr-gcc
OC = avr-objcopy
DL = avrdude


MMCU = atmega328p

CFLAGS = -I$(IDIR)
CFLAGS += -Os -DF_CPU=16000000UL -mmcu=$(MMCU)

ODIR = obj

#_DEPS = pid.h
_DEPS = endat.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ = main.o pid.o
_OBJ = main.o endat.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 
	$(OC) -O ihex -R .eeprom $@ $(join $@, .hex)

dl:
	$(DL) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:main.hex

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~