
FLAGS = -W -g

all: xmem

xmem: xmem.c memtest.c
	gcc $(FLAGS) -c xmem.c memtest.c
	gcc $(FLAGS) xmem.o memtest.o -o memtest

clean:
	rm *.o memtest
