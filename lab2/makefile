СС = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic

# .exe
app.exe: sort.o test.o cdio.o file.o functions.o main.o 
	$(CC) -o $@ $^

debug.exe: main_d.o cdio_d.o
	$(CC) -o $@ $^ -g3
	
test.exe: test.o cdio.o functions.o
	$(CC) -o $@ $^

bat_test.exe: bat_test.o cdio.o functions.o
	$(CC) -o $@ $^


# .o
main.o: main.c head.h
	$(CC) $(CFLAGS) -c $<
	
cdio.o: cdio.c head.h
	$(CC) $(CFLAGS) -c $<

functions.o: functions.c head.h
	$(CC) $(CFLAGS) -c $<

file.o: file.c head.h
	$(CC) $(CFLAGS) -c $<

sort.o: sort.c head.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c head.h
	$(CC) $(CFLAGS) -c $<

	
#clear files
clear:
	rm *.o *.exe
