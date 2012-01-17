
CFLAGS = -Wall -w -g -I $(INCLUDE_DIR) 
OPTS = -DSTRATEGY=1 -DNRQUICKLISTS=32 -DDEBUG=1
INCLUDE_DIR = src/include
SRC = src/libxmem/*.c
OBJ = ${SRC:%.c=%.o}
EXEC = xmem

all: $(SRC) $(EXEC)

$(EXEC): $(OBJ)
	gcc $(CFLAGS) $(OPTS) $(OBJ) src/memtest.c -o $(EXEC)

%.c%.o: %.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC)/*.o

