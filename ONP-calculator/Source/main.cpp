#include "Application.h"

// to do:
// Przerobic liste (Struktura osobno przedstawiona jako T) +
// Interface uzytkownika + 
// Klasa aplikacja +
// Operator przenoszacy i konstruktor przenoszacy 
// Dodaæ plik readme
// Google test (Github) - test jednostkowe

// Zapytaæ o przestrzenie nazw
// Powtorzyc F10 i F11

int main()
{

    Application app;
	double result;

	for (;;)
	{
		app.take();
		result = app.solution();
		cout << "solution: " << result << endl;
		cout << "Do you want to solve another equation? (y/n)" << endl;

		char ch;
		std::cin.get(ch);
		std::cin.ignore();

		ch = std::tolower(ch);

		while (std::strchr("yn", ch) == NULL)
		{
			cout << "Please enter 'y' or 'n" << endl;
			std::cin.get(ch);
			std::cin.ignore();
			ch = std::tolower(ch);
		}

		if (ch == 'n')
		{
			cout << "Goodbye" << endl;
			std::exit(0);
		}
	}

    return 0;
}

/*
* std::vector<std::string> vec;
        vec.push_back("3+4*2/(1-5)^2");
        vec.push_back("7+1*(2*3+4/5)");
        vec.push_back("(1+2)*4+5-3");
        vec.push_back("12+2*(3*4+10/5)");
*/