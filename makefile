
FLAGS = -Wall -w -g -I $(SOURCE_DIR)/include 
OPTS = -DSTRATEGY=1 -DNRQUICKLISTS=32 -DDEBUG=1

BIN_DIR := bin
SOURCE_DIR := src
SOURCE_SUB_DIRS := $(SOURCE_DIR)/libxmem

SOURCES := $(wildcard $(SOURCE_SUB_DIRS)/*.c)
OBJS := $(patsubst %.c,%.o,$(SOURCES))

all: libxmem memtest

memtest: libxmem
	gcc $(FLAGS) $(OPTS) -c $(SOURCE_DIR)/memtest.c -o $(SOURCE_DIR)/memtest.o 
	gcc $(OBJS) $(SOURCE_DIR)/memtest.o -o $(BIN_DIR)/xmem

libxmem: $(OBJS)
	@echo $(SOURCES)
	@echo $@ done.

%.o: %.c
	gcc $(FLAGS) $(OPTS) -o $@ -c $<

clean:
	rm -rf $(SOURCE_DIR)/*.o $(SOURCE_SUB_DIRS)/*.o bin/xmem

