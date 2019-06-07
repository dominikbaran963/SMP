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
			symbolCharValue = 65;
		else
			symbolCharValue = 48; //jak symbol jest litera to bedzie generowal cyfry i na odwrot
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
		cout << symbol << ":  ";
		for (int i = 0; i < preferencies.size(); i++) {
			cout << preferencies[i];
			if (i != preferencies.size() - 1)
				cout << ", ";
		}
		cout << endl;
	}
};
int factorial(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	else return n * factorial(n - 1);
}
vector<vector<element*> >generatePermutations(vector<element*>set) {
	int n = set.size();
	int fac = factorial(n);
	int temp1, temp2, temp3, it, perIt = 0;
	int* permutations = new int[n];
	vector<vector<element*> >setPermutations;
	vector<element*> tempVector;
	setPermutations.push_back(set);
	if (n > 0)
		perIt++;
	for (int i = 0; i < n; i++) {
		permutations[i] = i;
	}
	for (int i = 0; i < fac - 1; i++) {
		it = 0;
		temp1 = -1;
		temp2 = -1;
		for (int j = 0; j < n - 1; j++) {
			if (permutations[j] < permutations[j + 1])
				if (j > temp1)
					temp1 = j;
		}
		for (int k = 0; k < n; k++) {
			if (permutations[temp1] < permutations[k])
				if (k > temp2)
					temp2 = k;
		}
		perIt++;
		temp3 = permutations[temp1];
		permutations[temp1] = permutations[temp2];
		permutations[temp2] = temp3;
		temp1++;
		for (int j = temp1; it < (n - temp1) / 2; j++) {
			temp3 = permutations[j];
			permutations[j] = permutations[n - 1 - it];
			permutations[n - 1 - it] = temp3;
			it++;
		}
		for (int j = 0; j < n; j++)
			tempVector.push_back(set[permutations[j]]);
		setPermutations.push_back(tempVector);
		tempVector.clear();
	}
	cout << endl << "Wygenerowano " << perIt << " permutacji" << endl << endl;
	return setPermutations;
}

void zad2_match(vector<element*>& set1, vector<element*>& set2, bool choice, char TABmatch[][2], int current) //przyporzadkowuje element zbioru B do danego elementu zbioru A
{
    for(int i=0;i<set2.size();i++)
    {
        bool check=true;
        TABmatch[current][1]=set1[current]->preferencies[i];
        for(int j=0;j<set1.size();j++)
        {
            if(TABmatch[current][1]==TABmatch[j][1] && current!=j)
            {
                char temp=TABmatch[current][1];
                if(choice)  // dla opcji wzgledem A i B
                {
                    for(int k=0;k<set2.size();k++)
                    {
                        if(set2[k]->symbol==temp)
                        {
                            for(int l=0;l<set1.size();l++)
                            {
                                if(set2[k]->preferencies[l]==TABmatch[current][0])
                                {
                                    zad2_match(set1,set2,choice,TABmatch, j);
                                    break;
                                }
                                else if(set2[k]->preferencies[l]==TABmatch[j][0])
                                {
                                    check=false;
                                    break;
                                }
                            }
                        }
                    }
                }
                else    check=false;
            }
        }
        if(check) break;
    }
}
void zad2_permutation(vector<element*>& set1, vector<element*>& set2, char TABwinning[][2], int &winning_points, bool choice)   //oblicza przyporzadkowanie dla danej permutacji
{
    int points=0;
    char TABmatch[set1.size()][2];
    for(int i=0; i<set1.size();i++)//przyporzadkowanie dla kazdego elementu
    {
        TABmatch[i][0]=set1[i]->symbol;
        zad2_match(set1,set2,choice,TABmatch, i);
    }
    /*for(int i=0;i<set1.size();i++)
        cout<<TABmatch[i][0]<<": "<<TABmatch[i][1]<<endl;
        */
    for(int i=0;i<set1.size();i++)// liczenie punktow
    {
        for(int j=0;j<set2.size();j++)
        {
            if(TABmatch[i][1]==set1[i]->preferencies[j])    points+=set2.size()-j-1;
            if(choice)  // dla optymalizacji wzgledem A i B)
            {
                if(set2[j]->symbol==TABmatch[i][1])
                {
                    for(int k=0;k<set1.size();k++)
                    {
                        if(set2[j]->preferencies[k]==TABmatch[i][0])    points+=set1.size()-k-1;
                    }
                }
            }
        }

    }

    if(points>winning_points)//ustawienie najbardziej optymalnego polaczenia
    {
        winning_points=points;
        for(int i=0;i<set1.size();i++)
        {
            TABwinning[i][0]=TABmatch[i][0];
            TABwinning[i][1]=TABmatch[i][1];
        }

    }
    //cout<<endl<<"Uzyskane punkty: "<<points<<endl;

}

void zad2(vector<element*>& set1, vector<element*>& set2)
{
	cout<<endl<<"Skojarzenia optymalne dla:"<<endl;
	cout<<"[1] - zbior A"<<endl;
	cout<<"[2] - zbior B"<<endl;
	cout<<"[3] - zbior A i B"<<endl;
	cout<<"Prosze wybrac:";
	int choice;
	cin>>choice;
    int size=0; //rozmiar tablicy z rozwiazaniem
	int winning_points=0;
    int max_points=(set2.size()-1)*set1.size();
    char TABwinning[10][2];

    //wybor wzgledem czego bedzie optymalne rozwiazanie
	if(choice==1) //wzgledem A
    {
        vector < vector<element*> >permutations = generatePermutations(set1);
        for(int i=0;i<permutations.size();i++)
            zad2_permutation(permutations[i], set2, TABwinning, winning_points, false);
        size=set1.size();
    }
    else if(choice==2) //wzgledem B
    {
        vector < vector<element*> >permutations = generatePermutations(set2);
        for(int i=0;i<permutations.size();i++)
            zad2_permutation(permutations[i], set1, TABwinning, winning_points, false);
        size=set2.size();
    }
    else if(choice==3) //wzgledem A i B
    {
        max_points+=max_points;
        zad2_permutation(set1,set2,TABwinning, winning_points, true);
        size=set1.size();
    }


    for(int i=0;i<size;i++) //sortowanie wyniku
    {
        for(int j=0;j<size;j++)
        {
            if(TABwinning[i][0]<TABwinning[j][0])
            {
                int temp0=TABwinning[i][0];
                int temp1=TABwinning[i][1];
                TABwinning[i][0]=TABwinning[j][0];
                TABwinning[i][1]=TABwinning[j][1];
                TABwinning[j][0]=temp0;
                TABwinning[j][1]=temp1;
            }
        }
    }
    cout<<endl<<"Najbardziej optymalne przyporzadkowanie:"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<TABwinning[i][0]<<": "<<TABwinning[i][1]<<endl;
    }
    cout<<endl<<"punkty: "<<winning_points<<endl;
    cout<<endl<<"maksymalna ilosc punktow: "<<max_points<<endl;
}

void getInput(vector<element*>& set1, vector<element*>& set2) {
	int amount1, amount2, preferenciesSize;
	char symbol;
	cout << "ilosc elementow 1: ";
	cin >> amount1;
	cout << "ilosc elementow 2: ";
	cin >> amount2;
	if (amount1 == amount2)
		preferenciesSize = amount1;
	else if (amount1 > amount2)
		preferenciesSize = amount1;
	else
		preferenciesSize = amount2;
	for (int i = 0; i < amount1; i++) {
		set1.push_back(new element(static_cast<char>(65 + i), preferenciesSize));
	}
	for (int i = 0; i < amount2; i++) {
		set2.push_back(new element(static_cast<char>(48 + i), preferenciesSize));
	}
	for (int i = 0; i < set1.size(); i++) {
		set1[i]->printPreferencies();
	}
	cout << endl;
	for (int i = 0; i < set2.size(); i++) {
		set2[i]->printPreferencies();
	}

}
void smp() {
	vector<element*>set1;
	vector<element*>set2;
	getInput(set1, set2);

    /*vector < vector<element*> >permutations = generatePermutations(set1);
	for (int i = 0; i < permutations.size(); i++) {
		for (int j = 0; j < permutations[i].size(); j++)
        {
			cout << permutations[i][j]->symbol<<": ";
        }
		cout << endl;
	}*/

    zad2(set1,set2);
}

int main() {
	srand(time(NULL));
	smp();
	return 0;
}


