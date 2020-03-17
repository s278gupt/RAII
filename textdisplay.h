#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>
#include "observer.h"
#include "subject.h"

class Player;

class TextDisplay: public Observer {
	Player* player_1;
	Player* player_2;
	std::vector<std::vector<char>> thegrid;
	int turn = 0;
	public:
	void set_turn(int turn);
	TextDisplay(Player* player_1, Player* player_2);
	void notify(Subject& whoNotified) override;
    friend std::ostream& operator<<(std::ostream& out, TextDisplay& td);
};

#endif
