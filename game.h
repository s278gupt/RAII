#ifndef _GAME_H
#define _GAME_H
#include <vector>
#include <string>
#include <iostream>

class AbilityInfo;
class TextDisplay;
class Player;
class Cell;
class GraphicsDisplay;

class Game{
	Player* player_1;
	Player* player_2;
	int turn = 0;
	std::vector<std::vector<Cell*>> thegrid;
	TextDisplay* td = nullptr; //the text display for the grid
	GraphicsDisplay* gd = nullptr; // graphics display of the grid
	
	public:
	void activateAbility(int ability, int r, int c);
	void activateAbility(int ability, char link);
	void move_link(char name, std::string direction);
	int who_won();
	void writeToGraphics(std::string s);
	void appendStringToGraphics(std::string s);
	void ability(Player* player, int id, AbilityInfo information);
	void game_init(std::string links_1 = "V1V2V3V4D1D2D3D4" , std::string links_2 = "V1V2V3V4D1D2D3D4", std::string ability_1 = "LFDSP", std::string ability_2 = "LFDSP", bool graphics = false);
	void change_turn();
	std::string show_abilities();
	friend std::ostream& operator<<(std::ostream&, Game& game);
	~Game();
};

#endif
