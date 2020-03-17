#include <vector>
#include <iostream>
#include <string>
#include "game.h"
#include "player.h"
#include "cell_info.h"
#include "linkcomponent.h"
#include "cell.h"
#include "textdisplay.h"
#include "serverport.h"
#include "normalcell.h"
#include "exception.h"
#include "graphicsdisplay.h"
#include "state.h"
using namespace std;

void Game::change_turn() {
	++turn;
	if (gd){ gd->change_turn(thegrid);}
}

void Game::writeToGraphics(string s){
	if (gd){gd->writeString(s);}
}

void Game::appendStringToGraphics(string s){
	if (gd){gd->appendString(s);}
}

int Game::who_won(){
	if (player_1->get_datacount() >= 4 ||
			player_2->get_viruscount() >= 4){
		return 1;
	}
	else if (player_1->get_viruscount() >= 4 ||
			player_2->get_datacount() >= 4){
		return 2;
	}
	else{
		return 0;
	}
}

void Game::game_init(string links_1, string links_2, string ability_1, string ability_2, bool graphics) {
	thegrid = vector<vector<Cell*>>(8, vector<Cell*>(0));
	player_1 = new Player{'a'};
	player_1->player_init(links_1, ability_1);
	player_2 = new Player{'A'};
	player_2->player_init(links_2, ability_2);
	td = new TextDisplay{player_1, player_2};

	if (graphics){
		gd = new GraphicsDisplay{player_1, player_2};
		gd->writeFirstStr();
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i == 0 && j == 3 ) || (i == 0 && j == 4)) {
				thegrid[i].emplace_back(new serverPort{player_1, i, j});
			}
			else if ((i == 7 && j == 3) || (i == 7 && j == 4)) {
				thegrid[i].emplace_back(new serverPort{player_2, i, j});
			}
			else {
				thegrid[i].emplace_back(new NormalCell{nullptr, i, j});
			}
			thegrid[i][j]->attach(td);
			thegrid[i][j]->attach(gd);
		}
	}

	for (int i = 3; i < 5; ++i) {
		thegrid[1][i]->set_link(player_1->get_link('d' + i - 3));
		thegrid[6][i]->set_link(player_2->get_link('D' + i - 3));
	}
	for(int j = 0; j < 3; ++j) {
		thegrid[0][j]->set_link(player_1->get_link('a' + j));
	}
	for(int j = 5; j < 8; ++j) {
		thegrid[0][j]->set_link(player_1->get_link('f' + j - 5));
	}
	for (int j = 0; j < 3; ++j) {
		thegrid[7][j]->set_link(player_2->get_link('A' + j));
	}
	for(int j = 5; j < 8; ++j) {
		thegrid[7][j]->set_link(player_2->get_link('F' + j - 5));
	}

	// Notifies all observers
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			thegrid[i][j]->notifyObservers();
		}
	}

}

void Game::move_link(char name, string direction){
	Player* active_player = turn % 2 == 0 ? player_1 : player_2;

	LinkComponent *MovingLink = nullptr;
	
	// Check if player is trying to move its own Link
	if (!active_player->is_my_link(name)){
		MovingLink = (turn % 2 == 0 ? player_2 : player_1)->get_link(name);
		if (!MovingLink->is_movable()){
			throw InvalidMove("Not your link");
		}
		active_player = turn % 2 == 0 ? player_2 : player_1;
	}
	else{
		MovingLink = active_player->get_link(name);
	}


	// Check if player is trying to move downloaded link
	if(MovingLink->downloaded()) {
		throw InvalidMove("This link has been downloaded!");
	}

	// Get new cell info
	CellInfo newcell_info = MovingLink->move(direction);
	Cell* oldCell = thegrid.at(MovingLink->get_row()).at(MovingLink->get_col());

	// Check that new cell coordinates are valid
	if (newcell_info.c < 0 || newcell_info.c > 7) {
		throw InvalidMove("Invalid coordinates");		
	} else if (newcell_info.r < 0 || newcell_info.r > 7) {
		if (newcell_info.r < 0 && active_player == player_2) {
			player_2->download(MovingLink);
		} else if (newcell_info.r > 7 && active_player == player_1) {
			player_1->download(MovingLink);
		} else {
			throw InvalidMove("Invalid coordinates");
		}
	} else {
		Cell* newCell = (thegrid.at(newcell_info.r)).at(newcell_info.c);
		newCell->accept(MovingLink, active_player);
	}
	
	// Deletes old cell's LinkComponent and notifies observers
	oldCell->set_link(nullptr);
	oldCell->notifyObservers();
	
}

string Game::show_abilities(){
	if (turn % 2) {
		return player_2->show_abilities();
	}
	else{
		return player_1->show_abilities();
	}
}
	

Game::~Game() {
	if (td) {
		delete td;
	}
	if (player_1) {
		delete player_1;
	}
	if (player_2) {
		delete player_2;
	}
	if (gd) {
		delete gd;
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			delete thegrid[i][j];
		}
	}
}

ostream& operator<<(ostream& out, Game& g) {
	g.td->set_turn(g.turn);
	return out << *(g.td);
}

void Game::activateAbility(int ability, int r, int c) {
	Player* active_player = turn % 2 == 0 ? player_1 : player_2;

	// check for valid r, c
	if (r < 0 || r > 7 || c < 0 || c > 7) {
		throw InvalidMove("Invalid cell coordinates. Please try again.");
	}

	// check if ability has been used
	if (active_player->abilityUsed(ability - 1)) {
		throw InvalidMove("Ability already used!");
	}

	// activate ability on cell at r,c
	char a = active_player->getAbilityName(ability - 1);
	Cell *newCell = thegrid.at(r).at(c)->createAbility(a, active_player);
	thegrid.at(r).at(c) = newCell;

	// update the used status of the ability
	active_player->setAbilityUsed(ability - 1);
	thegrid.at(r).at(c)->attach(td);
	if (gd){ thegrid.at(r).at(c)->attach(gd);}
	thegrid.at(r).at(c)->notifyObservers();
}

void Game::activateAbility(int ability, char link) {
	Player* active_player = turn % 2 == 0 ? player_1 : player_2;
	LinkComponent* theLink = nullptr;
	if(player_1->is_my_link(link)) {
		 theLink = player_1->get_link(link);
	}
	else if (player_2->is_my_link(link)) {
		 theLink = player_2->get_link(link);
	}
	else {
		throw InvalidMove{"Link name is not correct"};
	}

	// check correct link name
	if (active_player->getAbilityName(ability - 1) == 'L' && !active_player->is_my_link(link)) {
		throw InvalidMove("Incorrect link name! Try again.");
	}
	if (active_player->getAbilityName(ability - 1) == 'D' && active_player->is_my_link(link)) {
		throw InvalidMove{"Incorrect link name! Try again."};
	}
	
	// get the link's cell
	if (theLink->downloaded()) {
		throw InvalidMove{"This link has been downloaded!"};
	}
	Cell* oldCell = thegrid.at(theLink->get_row()).at(theLink->get_col());

	// create the link ability
	active_player->useAbility(ability, theLink);
	oldCell->set_link(player_1->is_my_link(link) ? player_1->get_link(link) : player_2->get_link(link));

	// check polarize condition
	if (active_player->getAbilityName(ability-1) == 'P' &&
		theLink->get_my_type() == linktype::data){
		if (oldCell->getInfo().type == CellType::FIREWALL){
			if (player_1->is_my_link(link)){
				theLink = player_1->get_link(link);
				if (oldCell->getInfo().player == player_2){
					player_2->download(theLink);
				}
			}
			else{ 
				theLink = player_2->get_link(link);
				if (oldCell->getInfo().player == player_1){
					player_1->download(theLink);
				}
			}
		}
		if (oldCell->getInfo().type == CellType::FIREWALL2X){
			if (player_1->is_my_link(link)){
				theLink = player_1->get_link(link);
				player_2->download(theLink);
			}
			else{
				theLink = player_2->get_link(link);
				player_1->download(theLink);
			}
		}
	}
	
	// update the old cell if the link has been downloaded
	state linkState = theLink->getState();
	if(linkState.downloaded) {
		oldCell->set_link(nullptr);
	}
	oldCell->notifyObservers();
	if (gd){ gd->redrawLinks(thegrid);}
}
