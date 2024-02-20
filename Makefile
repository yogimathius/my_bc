BIN=my_bc
CC=gcc
SRC=src/my_bc.c src/main.c
INC=inc/

all:
	$(CC) $(CFLAGS) -I$(INC) $(SRC) -o $(BIN)

clean:
	rm -f $(OBJ)
fclean:
	rm -f $(OBJ) $(BIN)
re: fclean all
