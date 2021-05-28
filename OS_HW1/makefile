CC = gcc
CFLAGS  = -Wall

SRC1 = A.c \
      mystrlib.c


OBJ1 =   $(SRC1:.c=.o)

EXEC1 =  verA

SRC2 = argsxorstr.c \
      mystrlib.c

OBJ2 =   $(SRC2:.c=.o)

EXEC2 =  argsxorstr

SRC3 = B.c \
      mystrlib.c

OBJ3 =   $(SRC3:.c=.o)

EXEC3 =  verB

SRC4 = xorstr.c \
      mystrlib.c

OBJ4 =   $(SRC4:.c=.o)

EXEC4 =  xorstr

SRC5 = C.c \
      mystrlib.c

OBJ5 =   $(SRC5:.c=.o)

EXEC5 =  verC

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(EXEC1) $(OBJ1)

$(EXEC2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(EXEC2) $(OBJ2)
	
$(EXEC3): $(OBJ3)
	$(CC) $(CFLAGS) -o $(EXEC3) $(OBJ3)

$(EXEC4): $(OBJ4)
	$(CC) $(CFLAGS) -o $(EXEC4) $(OBJ4)
	
$(EXEC5): $(OBJ5)
	$(CC) $(CFLAGS) -o $(EXEC5) $(OBJ5)	

clean:
	rm -f $(OBJ1) $(EXEC1)
	rm -f $(OBJ2) $(EXEC2)
	rm -f $(OBJ3) $(EXEC3)
	rm -f $(OBJ4) $(EXEC4)
	rm -f $(OBJ5) $(EXEC5)


re: clean all

.PHONY: all clean fclean re