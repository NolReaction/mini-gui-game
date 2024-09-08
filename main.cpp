#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

int main() {
	
	srand(time(0));
	int guessNum = rand() % 101;
	cout << "Guessed number: " << guessNum << endl;


}