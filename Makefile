# Makefile

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g
LIBS=-lm

# Links together files needed to create executable
render_tone: render_tone.o wave.o io.o
	$(CC) -o render_tone render_tone.o wave.o io.o $(LIBS)

#Links files together to create executable
render_song: render_song.o wave.o io.o
	$(CC) -o render_song render_song.o wave.o io.o $(LIBS)

#Links files together to create executable
render_echo: render_echo.o wave.o io.o 
	$(CC) -o render_echo render_echo.o wave.o io.o $(LIBS)

# Compiles wave.c to create wave.o
wave.o: wave.c wave.h io.h
	$(CC) $(CFLAGS) -c wave.c $(LIBS)

#Compiles io.o
io.o: io.c wave.h io.h
	$(CC) $(CFLAGS) -c io.c $(LIBS)

# Compiles render_tone.c to create render_tone.o
render_tone.o: render_tone.c wave.h io.h
	$(CC) $(CFLAGS) -c render_tone.c $(LIBS)


# Compiles render_song.c to create render_tone.o
render_song.o: render_song.c wave.h io.h
	$(CC) $(CFLAGS) -c render_song.c $(LIBS)

#Compiles render_echo.c to create render_echo.o
render_echo.o: render_echo.c wave.h io.h
	$(CC) $(CFLAGS) -c render_echo.c $(LIBS)

# Removes all object files and executables,
# so we can start fresh
clean:
	rm -f *.o *.wav render_song render_tone render_echo tester
