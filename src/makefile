
FLAGS = -Wall -w -g
OPTS = -DSTRATEGY=1 -DNRQUICKLISTS=32 -DDEBUG=1
SOURCES = $(wildcard libxmem/*.c)
OBJS=$(SOURCES:.c=.o)

all: debug libxmem memtest.c
	gcc $(FLAGS) $(OPTS) -c memtest.c
	gcc $(OBJS) memtest.o -o memtest


libxmem: $(OBJS)
	gcc $(FLAGS) $(OPTS) -c $(SOURCES) 
	# maybe need to link in libxmem_quickfit here..

debug: debug.c
	gcc $(FLAGS) $(OPTS) -c debug.c

clean:
	touch phony.o libxmem/phony.o memtest
	rm *.o libxmem/*.o memtest
