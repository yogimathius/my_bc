BIN=my_bc
CC=gcc
SRC=src/my_bc.c src/main.c src/queue.c src/op.c src/stack.c
INC=inc/
CFLAGS = -Wall -Wextra -Werror


all:
	$(CC) $(CFLAGS) -I$(INC) $(SRC) -o $(BIN)

clean:
	rm -f $(OBJ)
fclean:
	rm -f $(OBJ) $(BIN)
re: fclean all
