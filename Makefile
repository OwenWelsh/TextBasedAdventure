run: Utilities.o Player.o Menu.o Location.o LocationElffor.o Game.o Main.o
	g++ -Wall -o $@ $^

dirty:
	g++ -o run Globals.h Utilities.h Utilities.cpp Item.h Player.h \
	Player.cpp Menu.h Menu.cpp Location.h Location.cpp LocationElffor.h \
	LocationElffor.cpp Locations.h Game.h Game.cpp Main.cpp

push:
	git push origin master

Utilities.o: Utilities.h Utilities.cpp

Player.o: Player.h Player.cpp

Menu.o: Menu.h Menu.cpp

Location.o: Location.h Location.cpp

LocationElffor.o: LocationElffor.h LocationElffor.cpp

Game.o: Menu.h Game.h Game.cpp

Main.o: Game.h Main.cpp

clean:
	-rm run *.o *~ *.h.gch
