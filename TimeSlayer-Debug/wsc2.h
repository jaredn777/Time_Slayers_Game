#include "endScreen.h"

class winScreen2 : public title {
public:
	winScreen2();
	int Run(sf::RenderWindow &App);
private:
	bool gameOver;

};

winScreen2::winScreen2() {
	alpha_max = 3 * 255;
	alpha_div = 3;
	gameOver = false;

}

int winScreen2::Run(sf::RenderWindow &App) {

	//Add sounds if wanted
	sf::SoundBuffer ExitSelectSound;
	sf::Sound ExitSelect;
	ExitSelectSound.loadFromFile("ExitSound.wav");
	ExitSelect.setBuffer(ExitSelectSound);

	sf::Music shad;
	shad.openFromFile("SuccessMusic.wav");

	shad.setLoop(true);

	shad.play();
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 1000; j++)
		{
			for (int k = 0; k < 100; k++)
			{

			}

		}
	}


	gameOver = true;
	int menu = 0;
	int alpha = 0;
	sf::Texture GameOverImage;
	sf::Sprite Sprite, DeathScreen1;
	sf::Font Font;

	Font.loadFromFile("arial.ttf");
	GameOverImage.loadFromFile("winscreen.png");

	DeathScreen1.setTexture(GameOverImage);
	DeathScreen1.setScale(1366 / DeathScreen1.getLocalBounds().width, 768 / DeathScreen1.getLocalBounds().height);

	//Menue Option 1: Play Again(restarts the game)
	sf::Text Menu1;
	Menu1.setFont(Font);
	Menu1.setCharacterSize(20);
	Menu1.setString("Play Again?");
	Menu1.setPosition({ 280.f,160.f });

	//Menu option 2: Exit (Exits the game)
	sf::Text Menu2;
	Menu2.setFont(Font);
	Menu2.setCharacterSize(20);
	Menu2.setString("Exit");
	Menu2.setPosition({ 280.f, 220.f });



	sf::Event Event;

	if (gameOver) {
		alpha = alpha_max;

	}

	while (gameOver)
	{

		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed) {
				return -1;
			}
			if (Event.type == sf::Event::KeyPressed) {
				switch (Event.key.code) {
				case sf::Keyboard::Up:
					menu = 0;
					break;
				case sf::Keyboard::Down:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0) {
						gameOver = false;
						return 1;
						break;
					}
					else {

						return -1;
					}
					break;
				default:
					break;
				}

			}

		}

		if (alpha < alpha_max) {
			alpha++;

		}

		Sprite.setColor(sf::Color::Black);
		if (menu == 0) {
			Menu1.setFillColor(sf::Color::Red);
			Menu2.setFillColor(sf::Color::White);

		}
		else {
			Menu1.setFillColor(sf::Color::White);
			Menu2.setFillColor(sf::Color::Red);

		}

		App.clear();
		App.draw(DeathScreen1);
		App.draw(Sprite);

		App.draw(Menu1);
		App.draw(Menu2);

		App.display();
	}


}