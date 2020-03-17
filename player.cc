#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "exception.h"
#include "player.h"
#include "linkcomponent.h"
#include "linkdecorator.h"
#include "link.h"
using namespace std;

Player::Player(char c): c{c} {}

void Player::player_init(string links, string ability_string) {
	//Initialize Links
	int links_length = links.length();
	for (int i = 0; i < links_length; i += 2) {
		this->links[c + i / 2] = new Link(c + i / 2, links[i + 1] - '0' , -1, -1, links[i] == 'D' ? linktype::data : linktype::virus, this);
	}

	//Initialize Abilities
	istringstream abilityStream{ability_string};	
	char s;
	for (int j = 0; j < 5; ++j){
		abilityStream >> s;
		this->abilities.emplace_back(pair<bool, char>(false, s));
	}
}

string Player::show_abilities(){
	// Return string of abilities
	string s;
	stringstream ss{s};
	for(int i = 0; i < 5; ++i){
		ss << i+1 << " " <<  abilities[i].second << ": ";
		!abilities[i].first ? ss << "Not Used" : ss << "Used";
		ss << "\n";
	}
	return ss.str();
}	
void Player::download(LinkComponent* link) {
	if (link->get_my_type() == linktype::data) {
		updata();
	}
	else {
		upvirus();
	}
	link->download();
}	
int Player::ability_count(){
	//Returns number of unused abilities left
	int count = 0;
	for(int i = 0; i < 5; ++i){
		if (!abilities[i].first){
			count++;
		}
	}
	return count;
}

LinkComponent* Player::get_link(char name) {
	return links[name];
}

bool Player::is_my_link(char name) {
	return links.count(name);
}

int Player::get_datacount() {
	return data_downloaded;
}

int Player::get_viruscount() {
	return viruses_downloaded;
}
void Player::updata() {
	++data_downloaded;
}
void Player::upvirus() {
	++viruses_downloaded;
}

Player::~Player() {
	for (char k = c; k < c + 8; ++k) {
		delete links[k];
	}
}

bool Player::abilityUsed(int a) {
	return abilities[a].first;
}

char Player::getAbilityName(int index) {
	return abilities[index].second;
}
void Player::set_link(LinkComponent* newLink, char oldLink) {
	links[oldLink] = newLink;
}

void Player::useAbility(int a, LinkComponent* theLink) {
	if (abilityUsed(a - 1)) {
		throw InvalidMove("Ability has already been used!");
	}

	char ability = abilities[a - 1].second;
	Player* owner = theLink->getOwner();
	owner->set_link(theLink->createAbility(ability, theLink, this), theLink->get_name());
	abilities[a - 1].first = true;
}

void Player::setAbilityUsed(int index) {
	abilities[index].first = true;
}

int Player::getPlayerId() {
	if (c == 'a') {
		return 1;
	} else {
		return 2;
	}
}

