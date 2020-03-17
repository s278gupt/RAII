#ifndef _ABILITY_INFO_H
#define _ABILITY_INFO_H
#include <string>

struct AbilityInfo {
	int r,c;
	std::string name;
};

#endif
// this is intended as a structure to give the abilities the information they need to execute the commands. Note that not all of these are revelan for all abilities.
// For example, the firewall would only use r and c etc...
