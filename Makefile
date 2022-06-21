CC=g++
CFLAGS=-Wall -Wextra
LDFLAGS=-lm

Main : Main.o QtRoboEvent.o Parser.o SocketConnection.o Util.o Buffer.o

Main.o : Main.cpp Parser.h QtRoboEvent.h SocketConnection.h

QtRoboEvent.o : QtRoboEvent.cpp QtRoboEvent.h

Parser.o : Parser.cpp Parser.h QtRoboEvent.h Util.h

SocketConnection.o : SocketConnection.cpp SocketConnection.h

Util.o : Util.cpp Util.h

Buffer.o : Buffer.cpp Buffer.h QtRoboEvent.h

clean :
		rm Main.o QtRoboEvent.o Parser.o SocketConnection.o Util.o Buffer.o qtroboparser