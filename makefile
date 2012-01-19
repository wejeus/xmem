
CFLAGS = -Wall -w -g
OPTS = -DSTRATEGY=4 -DNRQUICKLISTS=3 -DDEBUG=1
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXEC = xmem

.PHONY: clean

all: xmem

xmem: $(OBJS)
	gcc $(CFLAGS) $(OPTS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) $(OPTS)  -c  $<
	
clean:
	rm -rf $(OBJS) memtest.o 
	rm -rf xmem

