CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic
RM = rm

app.exe: main.o test.o tree_func.o avl_func.o hash_func.o
	$(CC) -o $@ $^
	

main.o: main.c head.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c head.h
	$(CC) $(CFLAGS) -c $<

tree_func.o: tree_func.c head.h
	$(CC) $(CFLAGS) -c $<

avl_func.o: avl_func.c head.h
	$(CC) $(CFLAGS) -c $<

hash_func.o: hash_func.c head.h
	$(CC) $(CFLAGS) -c $<
	
clean:
	$(RM) *.exe *.o