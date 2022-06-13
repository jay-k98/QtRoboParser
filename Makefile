CC=g++
CFLAGS=-Wall -Wextra
LDFLAGS=-lm

qtroboparser : main.o qtroboevent.o parser.o socketconnection.o util.o
				cc -o qtroboparser Main.o QtRoboEvent.o Parser.o SocketConnection.o Util.o -lstdc++

main.o : Main.cpp Parser.h QtRoboEvent.h SocketConnection.h
		cc -c Main.cpp -lstdc++

qtroboevent.o : QtRoboEvent.cpp QtRoboEvent.h
				cc -c QtRoboEvent.cpp -lstdc++

parser.o : Parser.cpp Parser.h QtRoboEvent.h Util.h
				cc -c Parser.cpp -lstdc++

socketconnection.o : SocketConnection.cpp SocketConnection.h
				cc -c SocketConnection.cpp -lstdc++

util.o : Util.cpp Util.h
		cc -c Util.cpp -lstdc++

clean :
		rm main.o qtroboevent.o parser.o socketconnection.o