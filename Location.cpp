#include "Locations.h"
#include "Menu.h"

Location::Location(Area input, Player &PCIn) : here(input), PC(PCIn) {}

void Location::getCommand(string input)
{
	if (input == "actions") {
		if (Menu::getDisplayActions() == false)
			displayActions();
	} else if (input == "observe") {
		display(areaToString(here));
		cout << '\n';
		displayDescription();
	} else if ((input == "wait until day") || (input == "wait until night"))
		processWait(input);
	else {
		if (processCommand(input) == ERROR) {
			displayUnknownCommand();
		}
	}
}

bool Location::IsDay = true;

// Put a space before all displayed actions.
void Location::displayActions()
{
	stringstream output;
	output << "Your possible actions are:\n observe\n" << getActions() << (IsDay ? " wait until night\n" : " wait until day\n") << " menu\n save\n quit\n";
	display(output.str());
}

void Location::displayUnknownCommand()
{
	if (Menu::getDisplayActions())
		display("Whatever that is, you can't do it.\n");
	else
		display("Whatever that is, you can't do it.  Try using the \"actions\" command.\n");
}

void Location::processWait(string input)
{
	if (input == "wait until day") {
		if (IsDay == false) {
			IsDay = true;
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
		cout << "Error: processWait() was forced to handle an unknown input.\n";
}

string Location::saveLocationData()
{
	stringstream output;
	output << IsDay << '\n' << ENDMARKER << '\n';
	return output.str();
}

void Location::loadLocationData(string input)
{
	stringstream strstr(input);
	strstr >> IsDay;
	
	strstr.ignore(1);
	LOADDATACHECK("Location")	
}
