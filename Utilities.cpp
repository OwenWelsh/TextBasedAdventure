#include "Utilities.h"

unsigned int UtilitiesOptions::screenWidth = 80;
unsigned int UtilitiesOptions::screenHeight = 24;
bool UtilitiesOptions::displayItemDescriptions = false;

string UtilitiesOptions::saveData()
{
	stringstream output;
	output << screenWidth << ' ' << screenHeight << ' ' << displayItemDescriptions << '\n' << ENDMARKER << '\n';
	return output.str();
}

void UtilitiesOptions::loadData(string input)
{	
	stringstream strstr(input);
	strstr >> screenWidth >> screenHeight >> displayItemDescriptions;
	
	char test;
	strstr >> test;
	if (test != ENDMARKER)
		cout << "Error: Something went wrong with UtilitiesOptions::loadData().\n";
}

string areaToString(Area input)
{
	switch (input) {
		case TOWNCENTER:			return "Town Center";
		case TOWNHALL:				return "Town Hall";
		case TOWNHALLLOBBY:			return "Town Hall Lobby";
		case THIEFSHOUSE:			return "Thief's House";
		case THIEFSHOUSEINTERIOR:	return "Thief's House Interior";
		default:
			cout << "Error: areaToString() received improper input.\n";
			return "";
	}
}

void display(string input, unsigned int width)
{
	const unsigned int screenWidth = (width == 0) ? UtilitiesOptions::getScreenWidth() : width;	
	unsigned int pos;
	string remainingOutput = input;
	
	while (remainingOutput.length() > screenWidth) { // While the output that remains to be printed is wider than the screen...
		pos = remainingOutput.find('\n');
		if ((pos >= 0) && (pos <= screenWidth)) { // Newline character found within the line to be printed out.  Printing out that part and the newline, then continuing.
			cout << remainingOutput.substr(0, pos + 1);
			remainingOutput.erase(0, pos + 1);
		} else {
			pos = remainingOutput.find_last_of(' ', screenWidth);
			if ((pos <= 0) || (pos >= screenWidth)) { // Handles the case where the first word of the line is longer than the width of the screens.
				cout << remainingOutput.substr(0, screenWidth);
				remainingOutput.erase(0, screenWidth);
				while ((remainingOutput[0] == ' ') && (remainingOutput.length() > 0))
					remainingOutput.erase(0, 1);
			} else { // Prints out words until one needs to be printed on the next line to avoid wrapping in the middle of the word and splitting it between two lines.
				cout << remainingOutput.substr(0, pos);
				remainingOutput.erase(0, pos);
				while ((remainingOutput[0] == ' ') && (remainingOutput.length() > 0))
					remainingOutput.erase(0, 1);
			}
			cout << '\n';
		}
	}
	cout << remainingOutput; // Prints out what's left once the string that remains to be printed is shorter than the width of the screen.
}

string truncateText(string name, int length, uint quantity)
{
	stringstream output;
	
	if (quantity == 1) {
		if (name.length() <= length)
			output << name;
		else
			output << name.substr(0, length - 3) << "...";
	} else {
		if (name.length() <= (length - (4 + digits(quantity)))) {
			output << name << " (x" << quantity << ")";
			
		} else
			output << name.substr(0, length - (7 + digits(quantity))) << "... (x" << quantity << ")";
	}
	
	return output.str();
}

int getSelection()
{
	int selection;
	string input;
	
	getline(cin, input);
	stringstream strstr(input);
	strstr >> selection;
	
	if (!strstr)
		return -99;
	
	return selection;
}

int stringComp(string leftComp, string rightComp)
{
	int i;
	for (i = 0; i < leftComp.length(); i++)
		leftComp[i] = tolower(leftComp[i]);
	for (i = 0; i < rightComp.length(); i++)
		rightComp[i] = tolower(rightComp[i]);
	
	int compLength = min(leftComp.length(), rightComp.length());
	for (i = 0; i < compLength; i++) {
		if (leftComp[i] < rightComp[i])
			return 1;
		else if (leftComp[i] > rightComp[i])
			return -1;
	}
	
	if (leftComp.length() < rightComp.length())
		return 1;
	else if (leftComp.length() > rightComp.length())
		return -1;
	else
		return 0;
}

uint digits(uint input)
{
	if (input == 0)
		return 1;
	else
		return ((int) log10(input)) + 1;
}
