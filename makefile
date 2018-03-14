
#Pour compiler dans le terminal: g++ -o iogame main.cpp -lSDLmain -lSDL

#files

S_FILES=main.cpp

#OutPut
EXEC=myGame

#Built settings
CC=g++

#SDL OPTIONS
CC_SDL=-lSDL `sdl-config --cflags --libs` -lSDL_mixer

all:Build

Build:
	$(CC) $(S_FILES) -o $(EXEC) $(CC_SDL)

build_run: Build
	$(EXEC)

clean:
	rm -rf 

