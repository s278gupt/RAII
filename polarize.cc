#include <sstream>
#include "linkdecorator.h"
#include "polarize.h"
#include "link_type.h"
#include "player.h"
#include "linkcomponent.h"
using namespace std;

Polarize::Polarize(LinkComponent *component): LinkDecorator{component} {};

linktype Polarize::get_my_type() const{
	linktype prev_type = component->get_my_type();
	if (prev_type == linktype::data){ return linktype::virus;}
	else if (prev_type == linktype::virus){ return linktype::data;}
	else{ return prev_type;}
}

string Polarize::display_link(Player* player){
	ostringstream out{};
	string type = get_my_type() == linktype::data ? "D" : "V";
	out << getStrength();
	ostringstream out_1{};
	out_1 << get_name();
	string name = out_1.str();
	string strength = out.str();
	if (player->is_my_link(get_name())){
		return name + ": " + type + strength;
	}
	else {
		if (is_visible()) {
			return name + ": " + type + strength;
		}
		else{ return name + ": ?";}
	}
}

Polarize::~Polarize() {}
