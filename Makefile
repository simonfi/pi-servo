CC = gcc
LD = gcc
CFLAGS = -I/usr/xenomai/include -Isource
LDFLAGS = -L/usr/xenomai/lib -lnative -lxenomai

COMMON_OBJS = source/servo.o source/gpio.o

all: examples 

clean:
	@rm -f $(COMMON_OBJS) examples/*.o

examples: examples/move-servo-7

examples/move-servo-7: $(COMMON_OBJS) examples/move-servo-7.o
	$(LD) $(LDFLAGS) $(COMMON_OBJS) examples/move-servo-7.o -o $@
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

