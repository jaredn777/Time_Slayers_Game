#pragma once
#include "header.h"
#include "menus.h"
#include "character.h"
#include "bullit.h"
#include "TitleScreen.h"
#include "Enemy.h"
class game : public screenInstance
{
public:
	game(void);
	~game();
	void player(void);
	void loadMap();
	void jumpLogic();
	void posUpdate();
	void gunLogic();
	void checkBot();
	virtual int Run(sf::RenderWindow &App);

private:
	Bullet BulletArray[50];
	Player PlayerCharacter;
	sf::Texture bTexture;
	sf::Sprite bimage;
	sf::Vector2i map[100][100];
	sf::Vector2i loadCounter = sf::Vector2i(0, 0);
	sf::Texture tileTexture;
	sf::Sprite tiles;
	int maxHeight;
	int groundHeight;
	int Bullitindex = 0;
};

game::game(void)
{
	//*****PUT ALL THE GLOBAL VALUES IN HERE*****

	//Generating the screen and window
	//sf::Vector2i screenDimensions(800, 250);
	
	//Initially loads the background
	if (!bTexture.loadFromFile("tempBackground.png")) {
		std::cout << "Background failed to load!" << std::endl;
	}

	//Sets the background to the loaded image
	bimage.setTexture(bTexture);

	//Constant for ground height
	groundHeight = 300;
}

game::~game() {

 }

void game::player(void) {
	//Generates the player
	Player kLlam;
	kLlam.setPos({ 300,400 });
	PlayerCharacter = kLlam;

}

void game::loadMap() {
	
	std::ifstream openfile("mapz.txt");

	if (openfile.is_open()) {
		std::string tileLocation;
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		while (!openfile.eof()) {
			std::string str;
			openfile >> str;
			char x = str[0], y = str[2];

			if (!isdigit(x) || !isdigit(y)) {
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			
			}
			else {
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
			
			}

			if (openfile.peek() == '\n') {
				loadCounter.x = 0;
				loadCounter.y++;

			}
			else {
				loadCounter.x++;

			}
		}
		loadCounter.y++;

	}


}

void game::checkBot() {
	std::ifstream openfiles("newmap.txt");
	std::vector<int> tempmap;

	std::vector<sf::Vector2i>tilez;
	std::vector<std::vector<int>>colMap;

	float playerbottom, playerleft, playerright, playertop;

	colMap.clear();
	if (openfiles.is_open()) {
		while (!openfiles.eof()) {
			std::string str, value;
			std::getline(openfiles, str);
			std::stringstream stream(str);

			while (std::getline(stream, value, ' ')) {
				if (value.length() > 0) {
					int a = atoi(value.c_str());
					tempmap.push_back(a);

				}
			}
			colMap.push_back(tempmap);
			tempmap.clear();

		}

	}

	playerbottom = PlayerCharacter.GetPos().y + 20;
	playerleft = PlayerCharacter.GetPos().y;
	playerright = PlayerCharacter.GetPos().x + 20;
	playertop = PlayerCharacter.GetPos().y;

	sf::Vector2i topLeft(sf::Vector2i((int)playerleft / 32, (int)playertop / 32));
	sf::Vector2i topRight(sf::Vector2i((int)playerright / 32, (int)playertop / 32));
	sf::Vector2i bottomLeft(sf::Vector2i((int)playerleft / 32, (int)playerbottom / 32));
	sf::Vector2i bottomRight(sf::Vector2i((int)playerright / 32, (int)playerbottom / 32));

	tilez.clear();

	tilez.push_back(topLeft);
	if (std::find(tilez.begin(), tilez.end(), topRight) == tilez.end())
		tilez.push_back(topRight);
	if (std::find(tilez.begin(), tilez.end(), bottomLeft) == tilez.end())
		tilez.push_back(bottomLeft);
	if (std::find(tilez.begin(), tilez.end(), bottomRight) == tilez.end())
		tilez.push_back(bottomRight);

	sf::Vector2f positions;
	positions.x = PlayerCharacter.GetPos().x;
	positions.y = PlayerCharacter.GetPos().y;
	for (int i = 0; i < tilez.size(); i++) {
		if (colMap[tilez[i].y][tilez[i].x] == 1) {
			std::cout << "cakeday\n";
			//groundHeight = PlayerCharacter.retY() - 64;
			PlayerCharacter.setPos({ positions.x, positions.y });
			break;
		}
		else {
			groundHeight = 300;
		}
	}

}


void game::jumpLogic() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (!(PlayerCharacter.isJump()) && PlayerCharacter.retY() > maxHeight) {
			PlayerCharacter.setJump(true);
		}

		if (PlayerCharacter.isJump()) {
			//std::cout << "Curr Height: " << PlayerCharacter.retY() << " Max Height: " << maxHeight << std::endl;
			if (PlayerCharacter.retY() > maxHeight) {
				PlayerCharacter.move({ 0, -PlayerCharacter.getMoveSpeed() * 10 });
			}
			else
			{
				PlayerCharacter.setJump(false);
			}
		}
	}

}

void game::posUpdate() {

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		PlayerCharacter.move({ PlayerCharacter.getMoveSpeed(),0 });

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		PlayerCharacter.move({ -PlayerCharacter.getGravity(),0 });

	}

	//Basically gravity pulling the block down if it's not jumping and is above the ground height
	if ((PlayerCharacter.retY() < groundHeight) && (!PlayerCharacter.isJump())) {
		PlayerCharacter.move({ 0 , PlayerCharacter.getGravity() });

	}

}

void game::gunLogic() {
	

	BulletArray[Bullitindex].shot = false;
 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		sf::Vector2f HipPosition;
 		HipPosition.x = PlayerCharacter.GetPos().x + 55;
		HipPosition.y = PlayerCharacter.GetPos().y + 32;
		BulletArray[Bullitindex].setPosition(HipPosition);
		BulletArray[Bullitindex].shot = true;
	

	}
		BulletArray[Bullitindex].move(1.0, 0);
	


}

int game::Run(sf::RenderWindow &App)
{

	sf::Event Event;
	sf::View view;
	player();
	bool Running = true;
	bool isFalling = false;
	PlayerCharacter.setPos({ 300,250 });
	PlayerCharacter.setSprite("MainCharacter2.png");



	//sf::Thread mapGen(&game::loadMap, this);
	//sf::Thread jump(&game::jumpLogic, this);
	//sf::Thread update(&game::posUpdate, this);
	//sf::Thread gunL(&game::gunLogic, this);
	//sf::Thread cBot(&game::checkBot, this);

	//loadMap();
	
	int totalKilled = 0;
	
	//sound buffers
	sf::SoundBuffer Gat2, Death1,Death2,Death3,Death4,Death5,Death6;
	Gat2.loadFromFile("Gat2.wav");
	Death1.loadFromFile("DEATHNOISE1.wav");
	Death3.loadFromFile("DEATHNOISE3.wav");
	Death4.loadFromFile("PlayerDeathNoise.wav");
	Death5.loadFromFile("DEATHNOISE4.wav");
	Death6.loadFromFile("DeathNOISE5.wav");
	//sounds
	sf::Sound Sound2, DeathSound1,DeathSound3,DeathSound4,DeathSound5,DeathSound6;
	//set sound buffers
	Sound2.setBuffer(Gat2);
	DeathSound1.setBuffer(Death1);
	DeathSound3.setBuffer(Death3);
	DeathSound4.setBuffer(Death4);
	DeathSound5.setBuffer(Death5);
	DeathSound6.setBuffer(Death6);
	srand(time(NULL));

	//ENEMY CODE
	const int numberofenemies = 20;
	Enemy *EnemyArray = new Enemy[numberofenemies];
	int ii = 0;
	float enemypositionsdifference ;
	float initialEnemyPosition = 1000;
	for (ii; ii < numberofenemies; ii++)
	{
		enemypositionsdifference = rand() % 1000 + 50;

		initialEnemyPosition += enemypositionsdifference;
		EnemyArray[ii].setPos({ initialEnemyPosition,250 });
		EnemyArray[ii].setSprite("EnemySprite.png");
		//EnemyArray[ii].setMoveSpeed((float).01);
	}
	ii = 0;
	
	


	 maxHeight = PlayerCharacter.maxJump();
	while (App.isOpen()) {

		
		//jump.launch();
		jumpLogic();
		//update.launch();
		posUpdate();
		//gunL.launch();
		gunLogic();
		//cBot.launch();

    ///////////ENEMY/////////////////////////////////////////////////
	///////////ENEMY/////////////////////////////////////////////////
	///////////ENEMY/////////////////////////////////////////////////
		//enemy move function
		for (ii; ii <numberofenemies; ii++)
		{
			if (EnemyArray[ii].GetHealth() == false)
			{
				continue;
			}
			EnemyArray[ii].move({(float) -.1, 0 });
		}
		ii = 0;

		//BULLET HIT DETECTION
		for (ii; ii < numberofenemies; ii++)
		{
			if (EnemyArray[ii].GetHealth() == false)
			{
				continue;
			}
			if (BulletArray[Bullitindex].getGlobalBounds().intersects(EnemyArray[ii].GetSprite().getGlobalBounds()))
			{

				//deathnoise code
				int deathnoiserand = rand() % 3 + 1;

				if (deathnoiserand == 1)
				{
					DeathSound1.play();
				}
				else if (deathnoiserand == 2)
				{
					DeathSound3.play();
				}
				else if (deathnoiserand == 3)
				{
					DeathSound5.play();
				}
			/*	else if (deathnoiserand == 4)
				{
					DeathSound6.play();
				}
				*/
				//deathnoise code end

				EnemyArray[ii].SetHealth(false);
				EnemyArray[ii].~Enemy();
				BulletArray[Bullitindex].~Bullet();
				Bullitindex++;
				totalKilled++;
			

			}
		}
		ii = 0;

		//PLAYER HIT DETECTION

		for (ii; ii < numberofenemies; ii++)
		{
			
			if (EnemyArray[ii].GetHealth() == false)
			{
				continue;
			}
			//player touches enemy
			if (PlayerCharacter.GetSprite().getGlobalBounds().intersects(EnemyArray[ii].GetSprite().getGlobalBounds()))
			{
				Running = false;
				view.reset(sf::FloatRect(0, 0, 1366, 768));
				App.setView(view);

				return 2;
			}
		}
		ii = 0;





		///////////ENEMYEND/////////////////////////////////////////////////
		///////////ENEMYEND/////////////////////////////////////////////////
		///////////ENEMYEND/////////////////////////////////////////////////

		while (App.pollEvent(Event)) {
			switch (Event.type)
			{
			case sf::Event::Closed:
				//Kills all threads
				//mapGen.terminate();
				//jump.terminate();
				//gunL.terminate();
				//update.terminate();
				App.close();
				Running = false;
				this->~game();
				return -1;

				//Closes the window if ESC is pressed
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape) {
					//Kills all threads
					/*mapGen.terminate();
					jump.terminate();
					gunL.terminate();
					update.terminate();
*/
					//Resets the viewpoint
					view.reset(sf::FloatRect(0, 0, 1366, 768));
					App.setView(view);
					Running = false;
					return 0;
				}

			case sf::Event::KeyReleased:
				if (Event.key.code == sf::Keyboard::Space)
				{
					Sound2.play();
				}
				
				if (Event.key.code == sf::Keyboard::Up) 
				{
					PlayerCharacter.setJump(false);
				}

			}

		}

		if (PlayerCharacter.isJump()) {
			PlayerCharacter.move({ 0, -PlayerCharacter.getMoveSpeed() });
		}

		//Basically gravity pulling the block down if it's not jumping and is above the ground height
		if ((PlayerCharacter.retY() < groundHeight) && (!PlayerCharacter.isJump())) {
			PlayerCharacter.move({ 0 , PlayerCharacter.getGravity() });

		}
		//COPIED GRAVITY FUNCTION ABOVE BUT FOR ENEMIES

		for (ii; ii <numberofenemies; ii++)
		{
			if (EnemyArray[ii].GetHealth() == false)
			{
				continue;
			}
			
			if ((EnemyArray[ii].retY() < groundHeight))
			{
				EnemyArray[ii].move({ 0 , EnemyArray[ii].getGravity() });

			}
		}
		ii = 0;


		

		view.reset(sf::FloatRect(0, 0, 640, 416));
		view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));




		sf::Vector2f position;
		position.x = PlayerCharacter.GetPos().x - 320;
		//position.y = PlayerCharacter.GetPos().y;

		if (position.x < 0)
			position.x = 0;
		if (position.y < 0)
			position.y = 0;

		view.reset(sf::FloatRect(position.x, 0, 640, 416));


		App.clear();
		if (totalKilled == numberofenemies && PlayerCharacter.GetPos().x >= 7650) {
			view.reset(sf::FloatRect(0, 0, 1366, 768));
			App.setView(view);
			Running = false;
			return 4;
		}
		else if (PlayerCharacter.GetPos().x >= 7650) {
			view.reset(sf::FloatRect(0, 0, 1366, 768));
			App.setView(view);
			Running = false;
			return 3;
		}

		App.draw(bimage);
		PlayerCharacter.drawTo(App);


		App.draw(BulletArray[Bullitindex]);
		for (ii; ii < numberofenemies; ii++)
		{
		
			if (EnemyArray[ii].GetHealth() == true)
			{

				EnemyArray[ii].drawTo(App);

			
			}
			
		}
		ii = 0;
		
	
		App.setView(view);

		

	/*	for (int i = 0; i < loadCounter.x; i++) {
			for (int j = 0; j < loadCounter.y; j++) {
				if (map[i][j].x != -1 && map[i][j].y != -1) {
					tiles.setPosition(i * 32, j * 32);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
					App.draw(tiles);
				}
			}
		}
*/

		App.display();
	}
	//Never reaching this point normally, but just in case, exit the application
	return -1;

}