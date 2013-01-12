#include "Locations.h"

/*	To add a new location:
 *		-add it's name to the Area enum in Globals.h
 *		-add it to the definision of areaToString() to string in Utilities.cpp
 *		-add a prototype to Locations.h
 *		-define a starting description and the processCommand(), displayDescription(), and getActions() functions in Locations.cpp
 *		-add the functionality to go to that area to the bodies of processCommand() and getActions() for the classes of the adjacent areas in Locations.cpp
 *		-add it as a case in locationMaker() in Game.cpp
 */

/*
 *		Town Center
 */

string TownCenter::description = "The center of town.  There are no people to be seen.  ";

void TownCenter::displayDescription()
{
	string output = description;
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status TownCenter::processCommand(string input, Player &PC)
{
	if (input == "go to Town Hall")
		PC.setCurrentLocation(TOWNHALL);
	else if (input == "go to Thief's House")
		PC.setCurrentLocation(THIEFSHOUSE);
	else
		return ERROR;
	return OK;
}

string TownCenter::getActions(Player &PC)
{
	return " go to Town Hall\n go to Thief's House\n";
}

string TownCenter::saveData()
{
	stringstream output;
	output << description << '\n' << ENDMARKER << '\n';
	return output.str();
}

void TownCenter::loadData(string input)
{
	stringstream strstr(input);
	getline(strstr, description);
	
	LOADDATACHECK("TownCenter");
}

/* 
 *		Town Hall
 */

string TownHall::description = "The town hall.  It is locked and abandoned.  ";
bool TownHall::DoorUnlocked = false;

void TownHall::displayDescription()
{
	string output = description;
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status TownHall::processCommand(string input, Player &PC)
{
	if (input == "go to Town Center")
		PC.setCurrentLocation(TOWNCENTER);
	else if (input == "unlock door") {
		if (DoorUnlocked == true) {
			display("The door is already unlocked.\n");
		} else if (PC.isInInventory(LOCKPICK)) {
			DoorUnlocked = true;
			display("The door has been unlocked, although the lockpick broke in the process.\n");
			description = "The town hall.  It is abandoned, but you have unlocked the door.  ";
			PC.removeFromInventory(LOCKPICK);
		} else {
			display("But you have nothing with which to unlock the door...\n");
		}
	}
	else if (input == "enter Town Hall") {
		if (DoorUnlocked)
			PC.setCurrentLocation(TOWNHALLLOBBY);
		else {
			display("The door is locked and won't budge.\n");
		}
	} else
		return ERROR;
	return OK;
}

string TownHall::getActions(Player &PC)
{
	string output;
	if ((DoorUnlocked == false) && (PC.isInInventory(LOCKPICK)))
		output += " unlock door\n";
	if (DoorUnlocked == true)
		output += " enter Town Hall\n";
	output += " go to Town Center\n";
	return output;
}

string TownHall::saveData()
{
	stringstream output;
	output << DoorUnlocked << '\n' << description << '\n' << ENDMARKER << '\n';
	return output.str();
}

void TownHall::loadData(string input)
{
	stringstream strstr(input);
	strstr >> DoorUnlocked;
	
	strstr.ignore(1);
	getline(strstr, description);
	
	LOADDATACHECK("TownHall")
}

/*
 *		Town Hall Lobby
 */

string TownHallLobby::description = "The lobby of the abandoned town hall.  An old treasury chest lies in the corner.  ";
bool TownHallLobby::TreasuryChestSearched = false;

void TownHallLobby::displayDescription()
{
	string output = description;
	output += (IsDay ? "It is daytime.\n" : "It is nighttime.\n");
	display(output);
}

status TownHallLobby::processCommand(string input, Player &PC)
{
	if (input == "leave Town Hall")
		PC.setCurrentLocation(TOWNHALL);
	else if (input == "search treasury chest") {
		if (TreasuryChestSearched)
			display("You've already searched the treasury chest.  It's empty now, you greedy son-of-an-orc.\n");
		else {
			display("When the dust settles, you find a sack of gold.\n");
			TreasuryChestSearched = true;
			PC.addToInventory(SACKOFGOLD);
			description = "The lobby of the abandoned town hall.  An old treasury chest lies opened and empty in the corner.  ";
		}
	} else
		return ERROR;
	return OK;
}

string TownHallLobby::getActions(Player &PC)
{
	string output;
	if (TreasuryChestSearched == false)
		output += " search treasury chest\n";
	output += " leave Town Hall\n";
	return output;
}

string TownHallLobby::saveData()
{
	stringstream output;
	output << TreasuryChestSearched << '\n' << description << '\n' << ENDMARKER << '\n';
	return output.str();
}

void TownHallLobby::loadData(string input)
{
	stringstream strstr(input);
	strstr >> TreasuryChestSearched;
	
	strstr.ignore(1);
	getline(strstr, description);
	
	LOADDATACHECK("TownHallLobby")
}

/*
 *		Thief's House
 */

string ThiefsHouse::description = "The residence of the local thief.  ";

void ThiefsHouse::displayDescription()
{
	string output = description;
	output += (IsDay ? "It is daytime, and the thief appears to be home.\n" : "It is nighttime, and thief appears to be out thieving, as the house is empty.\n");
	display(output);
}

status ThiefsHouse::processCommand(string input, Player &PC)
{
	if (input == "go to Town Center")
		PC.setCurrentLocation(TOWNCENTER);
	else if (input == "enter house") {
		if (IsDay) {
			display("Well that wasn't particularly bright of you.  The thief killed you for breaking into his house.\n");
			PC.killPlayer();
		} else
			PC.setCurrentLocation(THIEFSHOUSEINTERIOR);
	} else 
		return ERROR;
	return OK;
}

string ThiefsHouse::getActions(Player &PC)
{
	return " enter house\n go to Town Center\n";
}

string ThiefsHouse::saveData()
{
	stringstream output;
	output << description << '\n' << ENDMARKER << '\n';
	return output.str();
}

void ThiefsHouse::loadData(string input)
{
	stringstream strstr(input);
	getline(strstr, description);
	
	LOADDATACHECK("ThiefsHouse")
}

/*
 *		Thief's House Interior
 */

string ThiefsHouseInterior::description = "Inside the residence of the local thief.  He has left some lockpicks on the table.  ";
bool ThiefsHouseInterior::ThiefSawYou = false;

void ThiefsHouseInterior::displayDescription()
{
	string output = description;
	output += (IsDay ? "It is daytime.  It's a miracle the thief hasn't killed you yet.\n" : "It is nighttime.\n");
	display(output);
}

status ThiefsHouseInterior::processCommand(string input, Player &PC)
{
	if (input == "take lockpick") {
		PC.addToInventory(LOCKPICK);
		display("You take a lockpick from the table.\n");
	} else if (input == "leave house") {
		if (ThiefSawYou) {
			display("The thief must have seen you in his house, because he was waiting outside to ambush you.  He killed you.\n");
			PC.killPlayer();
		} else
			PC.setCurrentLocation(THIEFSHOUSE);
	} else
		return ERROR;
	return OK;
}

string ThiefsHouseInterior::getActions(Player &PC)
{
	return " take lockpick\n leave house\n";
}

void ThiefsHouseInterior::processWait(string input)
{
	if (input == "wait until day") {
		if (IsDay == false) {
			IsDay = true;
			ThiefSawYou = true;
			cout << "You wait until the sun rises.\n";
		} else
			cout << "But it already is day...\n";
	}
	else if (input == "wait until night") {
		if (IsDay == true) {
			IsDay = false;
			cout << "You wait until the sun sets.\n";
		} else
			cout << "But it is already night...\n";
	}
	else
		cout << "Error: processWait() in ThiefsHouseInterior was forced to handle an unknown input.\n";
}

string ThiefsHouseInterior::saveData()
{
	stringstream output;
	output << ThiefSawYou << '\n' << description << '\n' << ENDMARKER << '\n';
	return output.str();
}

void ThiefsHouseInterior::loadData(string input)
{
	stringstream strstr(input);
	strstr >> ThiefSawYou;
		
	strstr.ignore(1);
	getline(strstr, description);
	
	LOADDATACHECK("ThiefsHouseInterior")
}
