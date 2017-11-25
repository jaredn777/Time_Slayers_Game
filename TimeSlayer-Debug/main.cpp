/* 
	If you don't know what this is by now
	this is going to be a long project.
*/
#pragma once
#include "header.h"
#include "menus.h"
#include "character.h"
#include "bullit.h"
#include "TitleScreen.h"
#include "game.h"
#include "endScreen.h"
#include "winScreen.h"
#include "wsc2.h"
using std::endl;
using std::string;

int main() {

	std::vector<screenInstance*> Screens;
	int screen = 0;

	sf::RenderWindow App(sf::VideoMode(1366, 768, 64), "GAYMEE");

	App.setMouseCursorVisible(false);

	title s0;
	Screens.push_back(&s0);
	game s1;
	Screens.push_back(&s1); 
	endScreen s2;
	Screens.push_back(&s2);
	winScreen s3;
	Screens.push_back(&s3);
	winScreen2 s4;
	Screens.push_back(&s4);




	while (screen >= 0) {
		screen = Screens[screen]->Run(App);
	}
}