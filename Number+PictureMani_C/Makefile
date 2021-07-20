CC=gcc
OBJS=main.o q1Functions.o pictureManipulation.o printMatrix.o q2Functions.o numberGame.o
EXEC=prog
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@

main.o: main.c pictureManipulation.h numberGame.h
numberGame.o: numberGame.c numberGame.h printMatrix.h q2Functions.h
pictureManipulation.o: pictureManipulation.c printMatrix.h \
 pictureManipulation.h q1Functions.h
printMatrix.o: printMatrix.c printMatrix.h
q1Functions.o: q1Functions.c q1Functions.h
q2Functions.o: q2Functions.c q2Functions.h



clean: 
	rm -f $(EXEC) $(OBJS)
	
