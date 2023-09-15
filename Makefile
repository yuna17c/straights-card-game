CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = straights
OBJECTS = card.o deck.o player.o computer.o human.o main.o controller.o round.o subject.o view.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
