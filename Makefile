CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = RAIInet
OBJECTS = main.o cell.o game.o player.o textdisplay.o serverport.o normalcellcomponent.o subject.o linkcomponent.o observer.o exception.o graphicsdisplay.o window.o normalcell.o normalcelldecorator.o link.o linkdecorator.o linkboost.o firewall.o download.o polarize.o control.o house.o scan.o booststrength.o
DEPEND = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
