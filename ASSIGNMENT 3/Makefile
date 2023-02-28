a3:	main.o init.o animals.o customers.o sched.o clinic.o
	gcc -g -o a3 main.o init.o animals.o customers.o sched.o clinic.o

main.o: main.c defs.h
	gcc -c main.c

init.o: init.c defs.h
	gcc -g -c init.c

animals.o: animals.c defs.h
	gcc -g -c animals.c

customers.o: customers.c defs.h
	gcc -g -c customers.c
       
sched.o: sched.c defs.h
	gcc -g -c sched.c
	
clinic.o: clinic.c defs.h
	gcc -g -c clinic.c
