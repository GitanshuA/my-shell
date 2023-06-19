myshell: comopts.o myshell.o mycp.o mymv.o myls.o mygrep.o myps.o help.o
	gcc comopts.o myshell.o mycp.o mymv.o myls.o mygrep.o myps.o help.o -lreadline -o myshell
	
comopts.o: comopts.c
	gcc comopts.c -c	

myshell.o: myshell.c
	gcc myshell.c -c

mycp.o: mycp.c
	gcc mycp.c -c

mymv.o: mymv.c
	gcc mymv.c -c

myls.o: myls.c
	gcc myls.c -c

mygrep.o: mygrep.c
	gcc mygrep.c -c

myps.o: myps.c
	gcc myps.c -c

help.o: help.c
	gcc help.c -c	

clean:
	rm *.o