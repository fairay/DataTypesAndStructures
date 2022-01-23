CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic

app.exe: main.o functions.o cdio_sparse.o cdio_matrix.o
	$(CC) -o $@ $^
	

main.o: main.c head.h
	$(CC) $(CFLAGS) -c $<

functions.o: functions.c head.h
	$(CC) $(CFLAGS) -c $<

cdio_sparse.o: cdio_sparse.c head.h
	$(CC) $(CFLAGS) -c $<
	
cdio_matrix.o: cdio_matrix.c head.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	*.exe *.o