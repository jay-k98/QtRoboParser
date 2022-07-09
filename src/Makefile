CC=g++
CFLAGS=-Wall -Wextra
LDFLAGS=-lm

Main : Main.o QtRoboEvent.o Parser.o SocketConnection.o Buffer.o Sender.o ReceiverThread.o SenderThread.o Crc.o

Main.o : Main.cpp Parser.h QtRoboEvent.h SocketConnection.h

QtRoboEvent.o : QtRoboEvent.cpp QtRoboEvent.h

Parser.o : Parser.cpp Parser.h QtRoboEvent.h

SocketConnection.o : SocketConnection.cpp SocketConnection.h

Buffer.o : Buffer.cpp Buffer.h QtRoboEvent.h

Sender.o : Sender.cpp Sender.h QtRoboEvent.h Buffer.h Crc.h

ReceiverThread.o : ReceiverThread.cpp ReceiverThread.h Parser.h QtRoboEvent.h SocketConnection.h Buffer.h

SenderThread.o : SenderThread.cpp SenderThread.h Buffer.h SocketConnection.h Sender.h

Crc.o : Crc.cpp Crc.h

clean :
		rm Main.o QtRoboEvent.o Parser.o SocketConnection.o Buffer.o Sender.o ReceiverThread.o SenderThread.o Crc.o Main