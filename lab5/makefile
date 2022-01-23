CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic
RM = rm

app.exe: main.o serving_machine.o test.o list_func.o queue_list.o queue_arr.o
	$(CC) -o $@ $^
	

main.o: main.c head.h
	$(CC) $(CFLAGS) -c $<

serving_machine.o: serving_machine.c head.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c head.h
	$(CC) $(CFLAGS) -c $<

list_func.o: list_func.c head.h
	$(CC) $(CFLAGS) -c $<
	
queue_list.o: queue_list.c head.h
	$(CC) $(CFLAGS) -c $<
	
queue_arr.o: queue_arr.c head.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.exe *.o