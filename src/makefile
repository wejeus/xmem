
FLAGS = -Wall -w -g -I include 
OPTS = -DSTRATEGY=1 -DNRQUICKLISTS=32 -DDEBUG=1

SOURCES = libxmem/*.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))

all: debug libxmem memtest

memtest: libxmem.o
	gcc memtest.o -o xmem

libxmem: $(OBJS)
	@echo START LIBXMEM
	gcc $?

$(OBJS): $(SOURCES)
	@echo Now compiling: $@
	gcc $(FLAGS) $(OPTS) -o libxmem/$< -c $@

debug: debug.c
	gcc $(FLAGS) $(OPTS) -c debug.c

clean:
	rm -rf *.o libxmem/*.o memtest

