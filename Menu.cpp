#include "Menu.h"

bool Menu::DisplayDescription = true;
bool Menu::DisplayActions = false;

Menu::Menu(Player &input) : PC(input) {}

string Menu::saveData()
{
	stringstream output;
	output << DisplayDescription << ' ' << DisplayActions << '\n' << ENDMARKER << '\n';
	return output.str();
}

void Menu::loadData(string input)
{
	stringstream strstr(input);
	strstr >> DisplayDescription >> DisplayActions;
	
	strstr.ignore(1);
	LOADDATACHECK("Menu")	
}

void Menu::pauseMenu()
{
	int selection = 0;
	do {
		display("Main menu:\n 1. View inventory\n 2. Options\n 0. Exit\n");
		selection = getSelection();
		switch (selection) {
			case 0:
				break;
			case 1:
				inventoryMenu();
				break;
			case 2:
				optionsMenu();
				break;
			default:
				display("Invalid selection.  Try again.\n");
		}
		cout << '\n';
	} while (selection != 0);
}

void Menu::inventoryMenu()
{
	int selectionNum;
	string selectionString;
	const string selections = " 1. See all items.\n 2. Examine item.\n 3. Remove item.\n 0. Return to main menu.\n";
	
	cout << "\nInventory:\n" << PC.inventoryToString();
	if (! PC.emptyInventory())
		cout << '\n';

	while (! PC.emptyInventory()) {
		display(selections);
		selectionNum = getSelection();
		switch (selectionNum) {
			case 1:
				cout << "\nInventory:\n" << PC.inventoryToString();
				break;
			case 2:
				display("Which item do you want to examine?\n");
				getline(cin, selectionString);
				if (PC.isInInventory(selectionString)) {
					Item temp = PC.getItem(selectionString);
					stringstream output;
					output << "\nName:  " << temp.getName() << '\n';
					if (temp.isUnique())
						output << "(unique)\n";
					output << temp.getDescription() << '\n';
					display(output.str());
				} else
					display("No such item in the inventory.\n");
				break;
			case 3:
				display("Which item do you want to remove?\n");
				getline(cin, selectionString);
				if (PC.isInInventory(selectionString)) {
					if ((PC.getItem(selectionString)).isUnique())
						display("You can't remove that item from your inventory.\n");
					else {
						string output = "Are you sure you want to remove ";
						output += selectionString;
						output += " from your inventory? (1. Yes.  0. No)\n";
						display(output);
						int tempSelection = getSelection();
					
						if (tempSelection == 1) {
							PC.removeFromInventory(selectionString);
							output = selectionString;
							output += " removed.\n";
							display(output);
						} else
							display("Item not removed.\n");
					break;
					}
				} else
					display("No such item in the inventory.\n");
			case 0:
				break;
			default:
				cout << "Invalid selection.  Try again.\n";
		}
		
		if (selectionNum != 0)
			cout << '\n';
		else
			break;
	}
}

void Menu::optionsMenu()
{
	int selection;
	cout << '\n';
	while (true) {
		stringstream output;
		output << "Options menu:\n 1. Always display area discription after moving:  " << OnOff(DisplayDescription)
			<< "\n 2. Always display actions on a new turn:  " << OnOff(DisplayActions)
			<< "\n 3. Show item descriptions in inventory screen:  " << OnOff(UtilitiesOptions::getDisplayItemDescriptions())
			<< "\n 4. Set screen dimensions:  " << UtilitiesOptions::getScreenWidth() << 'x' << UtilitiesOptions::getScreenHeight()
			<< "\n 0. Return to main menu.\n";
		display(output.str());
		selection = getSelection();
		switch (selection) {
			case 0:
				break;
			case 1:
				DisplayDescription = (DisplayDescription ? false : true);
				if (DisplayDescription)
					display("\nDescriptions will now always be displayed upon moving.\n");
				else
					display("\nDescriptions will now only be displayed when the \"observe\" command is entered.\n");
				break;
			case 3:
				UtilitiesOptions::setDisplayItemDescriptions(UtilitiesOptions::getDisplayItemDescriptions() ? false : true);
				if (UtilitiesOptions::getDisplayItemDescriptions())
					display("\nThe inventory screen will now show item descriptions.\n");
				else
					display("\nThe inventory screen will now only show item names and quantities.\n");
				break;
			case 2:
				DisplayActions = (DisplayActions ? false : true);
				if (DisplayActions)
					display("\nActions will now always be displayed at the beginning of a turn.\n");
				else
					display("\nActions will now only be displayed when the \"actions\" command is entered.\n");
				break;
			case 4:
				int input;
				cout << "\nEnter screen width:\n";
				input = getSelection();
				if (input < 80)
					cout << "Screen width too short.\n";
				else
					UtilitiesOptions::setScreenWidth((unsigned int) input);
				cout << "Enter screen height:\n";
				input = getSelection();
				if (input < 24)
					cout << "Screen height too short.\n";
				else
					UtilitiesOptions::setScreenHeight((unsigned int) input);
				cout << "Screen dimensions set to " << UtilitiesOptions::getScreenWidth() << 'x' << UtilitiesOptions::getScreenHeight() << ".\n";
				break;
			default:
				cout << "Invalid selection.  Try again.\n";
		}
		if (selection != 0)
			cout << '\n';
		else
			break;
	}
}
