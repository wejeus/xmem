
CFLAGS = -Wall -w -g
OPTS = -DSTRATEGY=2 -DNRQUICKLISTS=32 -DDEBUG=1
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXEC = xmem

all: xmem

xmem: $(OBJS)
	gcc $(CFLAGS) $(OPTS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) $(OPTS)  -c  $<
		
.PHONY: clean
clean:
	rm -rf $(OBJS) memtest.o 
	rm -rf xmem

