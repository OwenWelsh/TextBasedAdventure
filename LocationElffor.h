#ifndef ELFFOR_H
#define ELFFOR_H

#include "Globals.h"
#include "Utilities.h"
#include "Location.h"

class ElfforRegion : public Location {
	STANDARDREGIONDECLARATIONS
protected:
	ElfforRegion(Area input, Player &PCIn) : Location(input, PCIn) {}
	static bool SwordRetrieved;
};

class ElfforMyHouseInterior : public ElfforRegion {
	STANDARDLOCATIONDECLARATIONS
public:
	ElfforMyHouseInterior(Player &PCIn) : ElfforRegion(ELFFORMYHOUSEINTERIOR, PCIn) {}
private:
	void processWait(string input);
};

class ElfforMyHouse : public ElfforRegion {
	STANDARDLOCATIONDECLARATIONS
public:
	ElfforMyHouse(Player &PCIn) : ElfforRegion(ELFFORMYHOUSE, PCIn) {}
};

class ElfforTownGate : public ElfforRegion {
	STANDARDLOCATIONDECLARATIONS
public:
	ElfforTownGate(Player &PCIn) : ElfforRegion(ELFFORTOWNGATE, PCIn) {}
};

class ElfforTavern : public ElfforRegion {
	STANDARDLOCATIONDECLARATIONS
public:
	ElfforTavern(Player &PCIn) : ElfforRegion(ELFFORTAVERN, PCIn) {}
};

class ElfforTavernInterior : public ElfforRegion {
	STANDARDLOCATIONDECLARATIONS
public:
	ElfforTavernInterior(Player &PCIn) : ElfforRegion(ELFFORTAVERNINTERIOR, PCIn) {}
private:
	void processWait(string input);
	static bool ConversationHad;
};

#endif