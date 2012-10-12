# modify the first two lines to fit your needs
# PROGRAM is the name of the final program
PROGRAM = bigint
# UNITS lists the base names of the .cpp files used in your program
UNITS   = test bigint

# here, put all of the header dependencies
bigint.o: bigint.h
test.o: bigint.h

CC      = clang++
CFLAGS  = -g -Wall
LDFLAGS = -g

OBJS    = $(UNITS:%=%.o)

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean all
.DEFAULT_GOAL = all

clean:
	rm -f $(OBJS) $(PROGRAM)
