EXE = main
ALL = main.o deque.o fight.o run.o
LIBS = -lpthread
CC = gcc -Wall

all:	$(EXE)

main:	$(ALL)
	$(CC) -o main $(ALL) $(LIBS)
          
main.o:	main.c defs.h
	$(CC) -c main.c
	
deque.o:	deque.c defs.h
	$(CC) -c deque.c

fight.o:          fight.c defs.h
	          $(CC) -c fight.c

run.o:	run.c defs.h
	$(CC) -c run.c
		
clean:
	rm -f $(EXE) $(ALL)
