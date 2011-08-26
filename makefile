
FLAGS = -Wall -w -g -I $(SOURCE_DIR)/include 
OPTS = -DSTRATEGY=1 -DNRQUICKLISTS=32 -DDEBUG=1

BIN_DIR := bin
SOURCE_DIR := src
LIBXMEM := $(SOURCE_DIR)/libxmem

SOURCES := $(wildcard $(LIBXMEM)/*.c)
OBJS := $(patsubst %.c,%.o,$(SOURCES))

all: libxmem memtest

memtest: libxmem
	gcc $(FLAGS) $(OPTS) -c $(SOURCE_DIR)/memtest.c -o $(SOURCE_DIR)/memtest.o 
	gcc $(OBJS) $(BIN_DIR)/libxmem.a $(SOURCE_DIR)/memtest.o -o $(BIN_DIR)/xmem

libxmem: $(OBJS)
	libtool -static $^ -o $(BIN_DIR)/libxmem.a

%.o: %.c
	gcc $(FLAGS) $(OPTS) -o $@ -c $<

clean:
	rm -rf $(SOURCE_DIR)/*.o $(LIBXMEM)/*.o $(BIN_DIR)/libxmem.a $(BIN_DIR)/xmem 

