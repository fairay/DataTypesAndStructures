CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic
RM = rm

app.exe: main.o lgraph_func.o queue_arr.o path_func.o
	$(CC) -o $@ $^
	

main.o: main.c head.h
	$(CC) $(CFLAGS) -c $<

lgraph_func.o: lgraph_func.c head.h
	$(CC) $(CFLAGS) -c $<

path_func.o: path_func.c head.h
	$(CC) $(CFLAGS) -c $<

queue_arr.o: queue_arr.c head.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.exe *.o