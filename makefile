
CFLAGS = -Wall -w -g -I $(INCLUDE_DIR) 
OPTS = -DSTRATEGY=3 -DNRQUICKLISTS=32 -DDEBUG=1
INCLUDE_DIR = src/include
BUILD_DIR = build	
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
EXEC = xmem

xmem: makefile $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	gcc $(CPFLAGS)  -c  $<
		
.PHONY: clean
clean:
	rm -rf $(OBJ) memtest.o 
	rm -rf xmem

