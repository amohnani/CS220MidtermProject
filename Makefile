# Makefile

CC=gcc
CFLAGS=-std=c99 -lm  -pedantic -Wall -Wextra

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
	$(CC) $(CFLAGS) -c wave.c

#Compiles test_search_functions.o
io.o: io.c wave.h io.h
	$(CC) $(CFLAGS) -c io.c

# Compiles functions.c to create functions.o
render_tone.o: render_tone.c wave.h io.h
	$(CC) $(CFLAGS) -c render_tone.c


# Compiles functions.c to create functions.o
render_song.o: render_song.c wave.h io.h
	$(CC) $(CFLAGS) -c render_song.c

render_echo.o: render_echo.c wave.h io.h
	$(CC) $(CFLAGS) -c render_echo.c

# Removes all object files and executables,
# so we can start fresh
clean:
	rm -f *.o render_song render_tone render_echo
