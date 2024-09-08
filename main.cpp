#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

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

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(text, states);
	}

private:
	sf::Text text;
};

int main() {

	// guessNum - наше рандомное число
	srand(time(0));
	int guessNum = rand() % 101;
	// Вывод числа в консоль
	cout << "Guessed number: " << guessNum << endl;

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

	CreateNewText helloMessage("HELLO",
		font, sf::Color::White, 40, 400, 400);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		// Отрисовываем текст через метод draw()
		window.draw(helloMessage);

		window.display();
	}
	return 0;
}