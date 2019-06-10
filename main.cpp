// test1.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

//#include <iostream>
//#include<string>
#include "Board.h"

double Dziel(double, double);

using namespace std;

int main()
{
	//std::cout << "Hello World!\n";
	/*double b=2;
	try
	{
		b=Dziel(10, 0);
	}
	catch (string w)
	{
		cout << "Wyjatek: " << w;
	}
	cout << b;*/
	Board b;
	b.game();
}



/*int main()
{
	try
	{
		Dziel(10, 0);
	}
	catch (string w)
	{
		cout << "Wyjatek: " << w;
	}
}*/
double Dziel(double a, double b) //funkcja zwraca iloraz a / b
{
	if (b == 0) {
		string wyjatek = "dzielenie przez zero!";
		throw wyjatek;
	}
	return a / b;
}