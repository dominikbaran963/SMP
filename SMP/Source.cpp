#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

struct element {
	char symbol;
	vector<char> preferencies;
	element(char symbol, vector<char> preferencies) {
		this->symbol = symbol;
		this->preferencies = preferencies;
	} // jeden konstruktor przyjmuje symbol elementu i vector jego preferencji
	element(char symbol, int amount) {
		int symbolCharValue, p1, p2, temp;
		this->symbol = symbol;
		if (symbol >= 48 && symbol <= 57)
			symbolCharValue = 48;
		else
			symbolCharValue = 65; //jak symbol jest litera to bedzie generowal cyfry i na odwrot
		for (int i = 0; i < amount; i++)
			preferencies.push_back(i + symbolCharValue); //najpierw generuje po kolei a potem miesza
		for (int i = 0; i < preferencies.size(); i++) {
			do {
				p1 = rand() % preferencies.size();
				p2 = rand() % preferencies.size();
			} while (p1 == p2);
			temp = preferencies[p1];
			preferencies[p1] = preferencies[p2];
			preferencies[p2] = temp;
		}

	} // drugi konstruktor przyjmuje symbol i ilosc preferencji a potem je losowe generuje
	void printPreferencies() {
		cout << symbol << ": ";
		for (int i = 0; i < preferencies.size(); i++)
			cout << preferencies[i]<<", ";
		cout << endl;
	}
};

void smp() {
	vector<element*>set1;
	vector<element*>set2;
	int amount;
	char symbol;
	cout << "ilosc elementow: ";
	cin >> amount;
	for (int i = 0; i < amount; i++) {
		set1.push_back(new element(static_cast<char>(65 + i), amount));
		set2.push_back(new element(static_cast<char>(48 + i), amount));
	}
	for (int i = 0; i < amount; i++)
		set1[i]->printPreferencies();
	cout << endl;
	for (int i = 0; i < amount; i++)
		set2[i]->printPreferencies();
}

int main() {
	srand(time(NULL));
	smp();
	return 0;
}