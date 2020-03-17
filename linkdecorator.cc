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
#include "linkdecorator.h"
using namespace std;

LinkDecorator::LinkDecorator(LinkComponent *component): component{component} {}

LinkDecorator::~LinkDecorator()  { delete component;}

void LinkDecorator::set_row(int row) {
	component->set_row(row);
}

void LinkDecorator::set_col(int col) {
	component->set_col(col);
}

char LinkDecorator::get_name() {
	return component->get_name();
}

int LinkDecorator::get_row() const{
	return component->get_row();
}

int LinkDecorator::get_col() const{
	return component->get_col();
}

int LinkDecorator::getStrength() const {
    return component->getStrength();
}

state LinkDecorator::getState() {
	return component->getState();
}

Player *LinkDecorator::getOwner() const {
    return component->getOwner();
}

CellInfo LinkDecorator::move(string direction){
	return component->move(direction);
}

void LinkDecorator::download() {
	component->download();
}

bool LinkDecorator::downloaded() const {
	return component->downloaded();
}

linktype LinkDecorator::get_my_type() const {
	return component->get_my_type();
}

// the argument player signifies the player whose turn it is  so that the link is displayed accordingly
string LinkDecorator::display_link(Player* player) { 
	return component->display_link(player);
}

void LinkDecorator::battle(LinkComponent *currentLink, NormalCellComponent *disputedCell) {
	component->battle(currentLink, disputedCell);
}

bool LinkDecorator::is_visible() const {
	return component->is_visible();
}

void LinkDecorator::set_visibility(bool visible) {
	component->set_visibility(visible);
}

bool LinkDecorator::is_movable() const {
	return component->is_movable();
}

void LinkDecorator::setStrength(int strength) {
	return component->setStrength(strength);
}

