CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic

app.exe: main.o test.o maze_func.o arr_st_func.o list_st_func.o free_mem_func.o 
	$(CC) -o $@ $^
	

main.o: main.c head.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c head.h
	$(CC) $(CFLAGS) -c $<

maze_func.o: maze_func.c head.h
	$(CC) $(CFLAGS) -c $<

free_mem_func.o: free_mem_func.c head.h
	$(CC) $(CFLAGS) -c $<
	
list_st_func.o: list_st_func.c head.h
	$(CC) $(CFLAGS) -c $<
	
arr_st_func.o: arr_st_func.c head.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	*.exe *.o