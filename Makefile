CC = g++
PROG = omni
INC = -I/usr/local/include -I/usr/include/jsoncpp
#INC= alloaudio allocore allocv alloGLV alloutil
#INC_PARAMS=$(foreach d, $(INC), -I../AlloSystem/build/include/$d)

#HEADERS = Cube.h RotationAngle.h Numbers.h Object.h Shape.h
SOURCES = $(PROG).cpp al_OmniStereo.cpp
PROG2 = room
SOURCES2 = $(PROG2).cpp al_OmniStereo.cpp

cubemap : $(HEADERS) $(SOURCES)
	$(CC) $(INC) $(SOURCES) -L/usr/local/lib -lalloutil -lallocore -lallocv -lGL -lGLU -lglut -lGLEW -lapr-1 -lpthread -ljsoncpp -lportaudio -lfreeimage -o $(PROG)

room : $(SOURCES2)
	g++ -g $(INC) $(SOURCES2) -L/usr/local/lib -lalloutil -lallocore -lallocv -lSDL -lGL -lGLU -lglut -lGLEW -lm -lapr-1 -lpthread -ljsoncpp -lportaudio -lfreeimage -o $(PROG2)


run:
	make room
	./$(PROG2)

clean :
	rm $(PROG)
