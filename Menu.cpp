#include "Menu.h"

Menu::Menu() {
   // initialize myValue
   myValue = "Please choose one of the following items:";
   myValue += "\n a - Show all movies";
   myValue += "\n b - Show actors in a movie";
   myValue += "\n c - Show movies an actor was in";
   myValue += "\n q - quit";
   myValue += "\n --> ";
   // initialize myValidChoices
   myValidChoices.insert('a');
   myValidChoices.insert('b');
   myValidChoices.insert('c');
   myValidChoices.insert('q');
}

string Menu::asString() const {
	return myValue;
}

void Menu::print(ostream& out) const {
	out << asString();
}

// easier to use than calling find() each time.
bool Menu::containsChoice(char choice) const {
	set<char>::iterator it = myValidChoices.find(choice);
	return (it != myValidChoices.end());
}

