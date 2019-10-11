# Makefile

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g
LIBS=-lm
tester: tester.o io.o wave.o
	$(CC) -O io.o wave.o

tester.o: tester.c io.h wave.h
	$(CC) $(CFLAGS) -c tester.c $(LIBS)

# Links together files needed to create executable
render_tone: render_tone.o wave.o io.o
	$(CC) -o render_tone render_tone.o wave.o io.o

#Links files together to create test target
render_song: render_song.o wave.o io.o
	$(CC) -o render_song render_song.o wave.o io.o

#Links files together to create test target
render_echo: render_echo.o wave.o io.o
	$(CC) -o render_echo render_echo.o wave.o io.o

# Compiles mainFile.c to create mainFile.o
wave.o: wave.c wave.h io.h
	$(CC) $(CFLAGS) -c wave.c $(LIBS)

#Compiles io.o
io.o: io.c wave.h io.h
	$(CC) $(CFLAGS) -c io.c $(LIBS)

# Compiles functions.c to create functions.o
render_tone.o: render_tone.c wave.h io.h
	$(CC) $(CFLAGS) -c render_tone.c $(LIBS)


# Compiles functions.c to create functions.o
render_song.o: render_song.c wave.h io.h
	$(CC) $(CFLAGS) -c render_song.c $(LIBS)

render_echo.o: render_echo.c wave.h io.h
	$(CC) $(CFLAGS) -c render_echo.c $(LIBS)

# Removes all object files and executables,
# so we can start fresh
clean:
	rm -f *.o render_song render_tone render_echo
