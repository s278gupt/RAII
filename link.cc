#include <sstream>
#include <string>
#include "linkcomponent.h"
#include "link_type.h"
#include "player.h"
#include "cell_info.h"
#include "normalcellcomponent.h"
#include "exception.h"
#include "state.h"
#include "link.h"
using namespace std;

Link::Link(char name, int strength, int r, int c, linktype type, Player* owner): 
	name{name}, strength{strength}, r{r}, c{c}, type{type}, owner{owner}  {}

void Link::set_row(int row) {
	r = row;
}

void Link::set_col(int col) {
	c = col;
}

char Link::get_name() {
	return name;
}

int Link::get_row() const{
	return r;
}

int Link::get_col() const{
	return c;
}

int Link::getStrength() const {
    return strength;
}

state Link::getState()  {
	return state{r, c, owner, is_downloaded};
}

Player *Link::getOwner() const {
    return owner;
}

CellInfo Link::move(string direction){
	if (direction == "up"){
		return CellInfo{r-1, c, nullptr, nullptr, CellType::NORMAL};
	}
	else if (direction == "down"){
		return CellInfo{r+1, c, nullptr, nullptr, CellType::NORMAL};
	}
	else if (direction == "left"){
		return CellInfo{r, c-1, nullptr, nullptr, CellType::NORMAL};
	}
	else if (direction == "right"){
		return CellInfo{r, c+1, nullptr, nullptr, CellType::NORMAL};
	}
	else{
		throw InvalidMove("Bad Direction");
	}
}

void Link::download() {
	is_downloaded = true;
	visibility = true;
}

bool Link::downloaded() const {
	return is_downloaded;
}

linktype Link::get_my_type() const {
	return type;
}

// the argument player signifies the player whose turn it is  so that the link is displayed accordingly
string Link::display_link(Player* player) { 
	ostringstream out{};
	string type = get_my_type() == linktype::data ? "D" : "V";
	out << getStrength();
	ostringstream out_1{};
	out_1 << get_name();
	string name = out_1.str();
	string strength = out.str();
	if (player->is_my_link(this->name)) {
		return name + ": " + type + strength;
	}
	else {
		if (visibility) {
            return name + ": " + type + strength;
		}
		else {
			return name + ": " "?";
		}
	}
}

void Link::battle(LinkComponent *currentLink, NormalCellComponent *disputedCell) {
	if (getStrength() >= currentLink->getStrength()) {
		getOwner()->download(currentLink);
		disputedCell->accept(this, this->getOwner());
	} else {
		(currentLink->getOwner())->download(this);
	}
}

bool Link::is_visible() const {
	return visibility;
}

void Link::set_visibility(bool visible) {
	visibility = visible;
}

bool Link::is_movable() const {
	return false;
}

void Link::setStrength(int strength) {
	this->strength = strength;
}

