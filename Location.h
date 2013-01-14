#ifndef LOCATION_H
#define LOCATION_H

/*	To add a new location:
 *		-add it's name to the Area enum in Globals.h (be sure to add it right before the AREAENDMARKER one, after all the previous areas)
 *		-add it to the definision of areaToString() to string in Utilities.cpp
 *		-add a prototype to the proper LocationXXXXX.h file
 *		-add it as a case in locationMaker() in Game.cpp
 *		-define the displayDescription(), processCommand(), getActions(), saveData(), and loadData() functions in the proper LocationXXXXX.cpp file
 *		-add the functionality to go to that area to the bodies of processCommand() and getActions() for the classes of the adjacent areas in the proper LocationXXXXX.cpp file
 *
 *	To add a new region:
 *		-add a prototype to the proper LocationXXXXX.h file
 *		-define its saveRegionData() and loadRegionData() functions in the proper LocationXXXXX.cpp file
 *		-add calls to the those save and load functions in the SAVEDATABODY and LOADDATABODY macros in Game.cpp
 */

#include "Globals.h"
#include "Utilities.h"
#include "Player.h"

// Standard declarations needed by a derived class of Location that will serve as the base class for the instantiable classes.
#define STANDARDREGIONDECLARATIONS \
public: \
	static string saveRegionData(); \
	static void loadRegionData(string input);

// Standard declarations needed by any instantiable Location derived class.
#define STANDARDLOCATIONDECLARATIONS \
public: \
	void displayDescription(); \
	status processCommand(string input); \
	string getActions(); \
	string saveData(); \
	void loadData(string input);

// Used when no special save body is needed
#define DEFAULTLOCATIONSAVEBODY \
	stringstream output; \
	output << ENDMARKER << '\n'; \
	return output.str();

// Used when no special load body is needed
#define DEFAULTLOCATIONLOADBODY \
	stringstream strstr(input); \
	LOADDATACHECK(areaToString(here)) \

class Location {
private:
	virtual status processCommand(string input) = 0; // Processes the user's input string to check it against actions unique to the area. Returns the area the player ends up in afterward.
	void displayUnknownCommand(); // Displays the error message for when an unknown command is entered.
	virtual void processWait(string input); // Called when the player waits until day or night. Can be overriden so that waiting has an effect on the area.
protected:
	const Area here;
	static bool IsDay;
	Player &PC;
	
	Location(Area input, Player &PCin); 
	virtual string getActions() = 0; // Displays all possible actions unique to the area. Each listed action should start with a space and end with a newline character.
public:
	Area getArea() const {return here;}
	void displayActions(); // Displays all possible actions, including those that aren't area specific.
	void getCommand(string input); // Takes input and uses the virtual processCommand function to process it. Returns the area the player ends up in after the command is processed.
	virtual void displayDescription() = 0; // Displays the area specific description. Each area should have its own static description variable.

	static string saveLocationData();
	static void loadLocationData(string input);
	virtual string saveData() = 0;
	virtual void loadData(string input) = 0;
};

#endif