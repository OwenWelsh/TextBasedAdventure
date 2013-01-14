#include "LocationElffor.h"

bool ElfforRegion::SwordRetrieved = false;

string ElfforRegion::saveRegionData()
{
	stringstream output;
	output << SwordRetrieved << '\n' << ENDMARKER << '\n';
	return output.str();
}

void ElfforRegion::loadRegionData(string input)
{
	stringstream strstr(input);
	strstr >> SwordRetrieved;
	
	strstr.ignore(1);
	LOADDATACHECK("ElfforRegion")
}

/*
 *		Elffor: my house (interior)
 */

void ElfforMyHouseInterior::displayDescription()
{
	string output = "The inside of your house.  It's small, but it's home.  ";
	if (! SwordRetrieved)
		output += "Your sword usually hangs on the wall, but it's missing, dust outlining where it used to be.  ";
	else
		output += "Dust outlines the spot on the wall where your sword usually hangs.  ";
	output += "There's a bed you can sleep in.  ";
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status ElfforMyHouseInterior::processCommand(string input)
{
	if (input == "leave")
		PC.setCurrentLocation(ELFFORMYHOUSE);
	else if (input == "sleep in bed") {
		if (IsDay) {
			display("You lie in bed in a state of half-sleep, dreaming vividly and just feeling very relaxed.  When you finally force yourself out a bed, night has arrived.\n");
			IsDay = false;
		} else {
			display("You get a good night's rest, waking up with boundless energy, ready to greet the new day.\n");
			IsDay = true;
		}
	} else
		return ERROR;
	return OK;
}

string ElfforMyHouseInterior::getActions()
{
	return " sleep in bed\n leave\n";
}

void ElfforMyHouseInterior::processWait(string input)
{
	if (input == "wait until day") {
		if (IsDay == false) {
			display("But why just wait when you can sleep in your comfy bed?\n");
		} else
			display("But it already is day...\n");
	}
	else if (input == "wait until night") {
		if (IsDay == true) {
			display("But why just wait when you can sleep in your comfy bed?\n");
		} else
			display("But it is already night...\n");
	}
	else
		cout << "Error: processWait() in ElfforMyHouseInterior was forced to handle an unknown input.\n";
}

string ElfforMyHouseInterior::saveData()
{
	DEFAULTLOCATIONSAVEBODY
}

void ElfforMyHouseInterior::loadData(string input)
{
	DEFAULTLOCATIONLOADBODY
}

/*
 *		Elffor: my house
 */

void ElfforMyHouse::displayDescription()
{
	string output = "Outside of your house.  It's a quaint little place.  You can see the tavern and the gate that leads out of town.  ";
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status ElfforMyHouse::processCommand(string input)
{
	if (input == "enter house")
		PC.setCurrentLocation(ELFFORMYHOUSEINTERIOR);
	else if (input == "go to tavern")
		PC.setCurrentLocation(ELFFORTAVERN);
	else if (input == "go to gate")
		PC.setCurrentLocation(ELFFORTOWNGATE);
	else
		return ERROR;
	return OK;
}

string ElfforMyHouse::getActions()
{
	return " enter house\n go to tavern\n go to gate\n";
}

string ElfforMyHouse::saveData()
{
	DEFAULTLOCATIONSAVEBODY
}

void ElfforMyHouse::loadData(string input)
{
	DEFAULTLOCATIONLOADBODY
}

/*
 *		Elffor: town gate
 */

void ElfforTownGate::displayDescription()
{
	string output =  "The gate that leads out of the town, left open to allow free passage.  There is a sign posted on the side of the gate.  You can see the tavern and your house.  ";
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status ElfforTownGate::processCommand(string input)
{
	if (input == "read sign") {
		display("WARNING:\nWild wolves have been spotted roaming outside of the town fence.  They will attack unprotected travelers.\
  If you are travelling alone, bring something to defend yourself with.\n");
		enterToContinue();
	} else if (input == "go to my house")
		PC.setCurrentLocation(ELFFORMYHOUSE);
	else if (input == "go to tavern")
		PC.setCurrentLocation(ELFFORTAVERN);
	else
		return ERROR;
	return OK;
}

string ElfforTownGate::getActions()
{
	return " read sign\n go to my house\n go to tavern\n";
}

string ElfforTownGate::saveData()
{
	DEFAULTLOCATIONSAVEBODY
}

void ElfforTownGate::loadData(string input)
{
	DEFAULTLOCATIONLOADBODY
}

/*
 *		Elffor: tavern
 */

void ElfforTavern::displayDescription()
{
	string output = "Outside of the local tavern, The Infernal Woods, a small building constructed of dark wood.  It's a modest place, but it's well-kept.\
  You can see your house and the gate that leads out of town.  ";
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status ElfforTavern::processCommand(string input)
{
	if (input == "enter tavern") {
		if (IsDay)
			PC.setCurrentLocation(ELFFORTAVERNINTERIOR);
		else
			display("The tavern door is locked.\n");
	} else if (input == "go to my house")
		PC.setCurrentLocation(ELFFORMYHOUSE);
	else if (input == "go to gate")
		PC.setCurrentLocation(ELFFORTOWNGATE);
	else
		return ERROR;
	return OK;
}

string ElfforTavern::getActions()
{
	return " enter tavern\n go to my house\n go to gate\n";
}

string ElfforTavern::saveData()
{
	DEFAULTLOCATIONSAVEBODY
}

void ElfforTavern::loadData(string input)
{
	DEFAULTLOCATIONLOADBODY
}

/*
 *		Elffor: tavern (interior)
 */

bool ElfforTavernInterior::ConversationHad = false;

void ElfforTavernInterior::displayDescription()
{
	stringstream output;
	if (IsDay) {
		output << "Inside The Infernal Woods.  Trent, the bartender, is " << (SwordRetrieved ? "standing behind the bar.  " : "waving at you, trying to attract your attention.  ");
		output << "Nina is sitting at the bar, sipping a brew.  ";
	} else
		output << "There's no one inside, as the place is closed.  ";
	output << (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output.str());
}

status ElfforTavernInterior::processCommand(string input)
{
	if (input == "leave")
		PC.setCurrentLocation(ELFFORTAVERN);
	else if (IsDay) {
		if (input == "talk to Trent") {
			if (SwordRetrieved) {
				display("\"Is life treating you well, friend?  I certainly hope it is.\"\n");
			} else {
				display("\"I'm glad you popped in!  You left something here last night.\"\n\nTrent hands you your sword.\n\n\"You going somewhere?  You'll be needing that, then.\
  I hear we've got wolves in our midst.\"\n");
				PC.addToInventory(RUSTYSWORD);
				SwordRetrieved = true;
				enterToContinue();
				display("\n\"Bah!  Wolves, you say?\" Nina shouts from her stool.  \"We haven't had a wolf problem in years, not since I showed them what's what!  The lad'll be fine!\"\n");
				enterToContinue();
				display("\n\"You need to get out of the tavern more, Nina.  These aren't the times they used to be.\"\n");
				enterToContinue();
				display("\nTrent turns to face you.  \"Either way, good to have your sword back, eh, friend?\"\n");
				enterToContinue();
			}
		} else if (input == "talk to Nina") {
			if (! SwordRetrieved)
				display("\"How ye be these days, lad?\"\n");
			else {
				if (! ConversationHad) {
					display("\"Trent's just a worry-wort.  You were quite the fighter in your day, if I recall correctly.\"\n");
					enterToContinue();
					display("\n\"Your recall isn't what it used to be, Nina.\"\n");
					enterToContinue();
					display("\n\"Are you doubting our boy's abilities, Trent?!\"\n");
					enterToContinue();
					display("\n\"I'm just saying you could do with a bet less of the ale, that's all...\"\n");
					enterToContinue();
					ConversationHad = true;
				} else
					display("\"Why, I'm sure you could take down a wolf with your bare hands, lad!\"\n");
			}
		} else
			return ERROR;
	} else
		return ERROR;
	return OK;
}

string ElfforTavernInterior::getActions()
{
	string output = " leave\n";
	if (IsDay)
		output += " talk to Trent\n talk to Nina\n";
	return output;
}

void ElfforTavernInterior::processWait(string input)
{
	if (input == "wait until day") {
		if (IsDay == false) {
			display("Trent walks in and gasps when he sees you.  \"How did you get in here?!...  Well, whatever, you're harmless enough.  Just don't scare me like that again.\"\n");
			IsDay = true;
		} else
			display("But it already is day...\n");
	}
	else if (input == "wait until night") {
		if (IsDay == true) {
			display("You stay until closing, at which point Trent leads you to the door.  \"Sorry, friend, but you can't stay here for the night.\"\n");
			enterToContinue();
			cout << '\n';
			PC.setCurrentLocation(ELFFORTAVERN);
			IsDay = false;
		} else
			display("But it is already night...\n");
	}
	else
		cout << "Error: processWait() in ElfforTavernInterior was forced to handle an unknown input.\n";
}

string ElfforTavernInterior::saveData()
{
	stringstream output;
	output << ConversationHad << '\n' << ENDMARKER << '\n';
	return output.str();
}

void ElfforTavernInterior::loadData(string input)
{
	stringstream strstr(input);
	strstr >> ConversationHad;
	
	strstr.ignore(1);
	LOADDATACHECK("ElfforTavernInterior")
}
