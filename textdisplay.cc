#include "textdisplay.h"
#include "cell_info.h"
#include "linkcomponent.h"
#include "player.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(Player* player_1, Player* player_2): player_1{player_1}, player_2{player_2}{
	for (int i = 0; i < 8; ++i) {
		thegrid.emplace_back(vector<char>(8, '.'));
	}
}

void TextDisplay::notify(Subject& whoNotified) {
	CellInfo info = whoNotified.getInfo();
	int row = info.r;
	int col = info.c;
	CellType type = info.type;
	Player *player = info.player;

	if (type == CellType::SERVERPORT) {
		thegrid[row][col] = 'S';
	} else if (type == CellType::FIREWALL) {
		if (player->getPlayerId() == 1) {
			thegrid[row][col] = 'm';
		} else {
			thegrid[row][col] = 'w';
		}
	} else if (type == CellType::HOUSE) {
		if (player->getPlayerId() == 1) {
			thegrid[row][col] = 'k';
		} else {
			thegrid[row][col] = 't';
		}
	}
	else {
		if (info.link) {
			thegrid[row][col] = info.link->get_name();
		}
		else {
			thegrid[row][col] = '.';
		}
	}
}

ostream& operator<<(ostream& out, TextDisplay& td) {
	Player* active_player = td.turn % 2 == 0 ? td.player_1 : td.player_2;
	// Player 1 Display
	out << "Player 1:" << endl;
	out << "Downloaded: " << td.player_1->get_datacount() << "D" << ", " << td.player_1->get_viruscount() << "V" << endl;
	out << "Abilities: " << td.player_1->ability_count() << endl;
	for (char c = 'a'; c < 'e'; ++c) {
		out << td.player_1->get_link(c)->display_link(active_player);
		out << "   ";
	}
	out << endl;
	for (char c = 'e'; c < 'i'; ++c) {
		out << td.player_1->get_link(c)->display_link(active_player);
		out << "   ";
	}
	out << endl;

	// Board Display
	out << "========" << endl;
	for (auto row: td.thegrid) {
		for (auto c: row) {
			out << c;
		}
		out << endl;
	}
	out << "========" << endl;

	// Player 2 Display
	out << "Player 2:" << endl;
	out << "Downloaded: " << td.player_2->get_datacount() << "D" << ", " << td.player_2->get_viruscount() << "V" << endl;
	out << "Abilities: " << td.player_2->ability_count() << endl;
	for (char c = 'A'; c < 'E'; ++c) {
		out << td.player_2->get_link(c)->display_link(active_player);
		out << "   ";
	}
	out << endl;
	for (char c = 'E'; c < 'I'; ++c) {
		out << td.player_2->get_link(c)->display_link(active_player);
		out << "   ";
	}
	out << endl;
	return out;
}

void TextDisplay::set_turn(int turn) {
	this->turn = turn;
}
