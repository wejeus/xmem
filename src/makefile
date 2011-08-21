
FLAGS = -Wall -w -g
OPTS = -DSTRATEGY=1 -DNRQUICKLISTS=32 -DDEBUG

all: debug libxmem memtest.c
	gcc $(FLAGS) $(OPTS) -c memtest.c
	gcc libxmem.o memtest.o -o memtest


libxmem: debug libxmem_quickfit.c libxmem.c
	gcc $(FLAGS) $(OPTS) -c libxmem_quickfit.c libxmem.c
	# maybe need to link in libxmem_quickfit here..

debug: debug.c
	gcc $(FLAGS) $(OPTS) -c debug.c

clean:
	rm *.o memtest
