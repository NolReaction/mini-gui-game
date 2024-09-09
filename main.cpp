#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

string stringConverter(int guessedNumber) {
	auto s = to_string(guessedNumber);
	return s;
}

class CreateNewText : public sf::Drawable {
public:
	CreateNewText(const string& content, const sf::Font& font, sf::Color color, unsigned int size,
		float posX, float posY)
	{
		text.setString(content);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(posX, posY);
	}

	CreateNewText(unsigned int guessedNumber, const sf::Font& font, sf::Color color, unsigned int size,
		float posX, float posY)
	{
		string s = stringConverter(guessedNumber);
		text.setString(s);
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(posX, posY);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(text, states);
	}

private:
	sf::Text text;
};

int main() {

	unsigned int min = 0;
	unsigned int max = 1000;
	unsigned int guessedNumber = (min + max) / 2;

	unsigned int windowWidth = 800;
	unsigned int windowHeight = 800;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), L"Guess The Number");

	// Добавляем шрифт
	sf::Font font;
	if (!font.loadFromFile("font/ALGER.TTF")) {
		return -1;
	}

	// Добавляем иконку игры
	sf::Image icon;
	if (!icon.loadFromFile("image/crypto64.png")) {
		return -1;
	}
	// Чтобы иконка появилась в окне
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Начальные надписи
	CreateNewText helloMessage("HELLO, GUESS THE NUMBER 0 - 1000",
		font, sf::Color::White, 40, 60, 300);
	CreateNewText enterMessage("PRESS ENTER",
		font, sf::Color::White, 40, 275, 400);

	// Надписи после нажатия Enter
	CreateNewText yourNumberIsMessage("YOUR NUMBER IS:",
		font, sf::Color::White, 40, 250, 300);
	CreateNewText guessedNumberMessage(guessedNumber,
		font, sf::Color::White, 40, 375, 400);

	// Кнопки > < (больше и меньше)
	sf::RectangleShape greaterButton(Vector2f(50, 50)); // Кнопка >;
	greaterButton.setFillColor(sf::Color::Green);
	greaterButton.setPosition(275, 400);

	sf::RectangleShape lessButton(Vector2f(50, 50)); // Кнопка <;
	lessButton.setFillColor(sf::Color::Red);
	lessButton.setPosition(500, 400);

	// Текст для кнопок
	sf::Text greaterText(">", font, 30);
	greaterText.setFillColor(Color::Black);
	greaterText.setPosition(greaterButton.getPosition().x + 10, greaterButton.getPosition().y);

	sf::Text lessText("<", font, 30);
	lessText.setFillColor(Color::Black);
	lessText.setPosition(lessButton.getPosition().x + 10, lessButton.getPosition().y);


	bool change = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (!change && event.key.code == sf::Keyboard::Enter) {
					change = true;
				}
			}

			if (change && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
			{
				Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

				if (greaterButton.getGlobalBounds().contains(mousePos)) {
					// Нажата кнопка >
					min = guessedNumber + 1;
					guessedNumber = (min + max) / 2;
					guessedNumberMessage = CreateNewText(guessedNumber, font, sf::Color::White, 40, 375, 400);
				}
				else if (lessButton.getGlobalBounds().contains(mousePos)) {
					// Нажата кнопка <
					max = guessedNumber - 1;
					guessedNumber = (min + max) / 2;
					guessedNumberMessage = CreateNewText(guessedNumber, font, sf::Color::White, 40, 375, 400);
				}
			}
			
		}

		window.clear();

		if (!change) {
			window.draw(helloMessage);
			window.draw(enterMessage);
		}
		else {
			window.draw(yourNumberIsMessage);
			window.draw(guessedNumberMessage);
			window.draw(greaterButton);
			window.draw(greaterText);
			window.draw(lessButton);
			window.draw(lessText);
		}

		window.display();
	}
	return 0;
}