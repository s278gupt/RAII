#ifndef _POLARIZE_H
#define _POLARIZE_H
#include <string>
#include "linkdecorator.h"
#include "link_type.h"

class Player;
class LinkComponent;

class Polarize : public LinkDecorator {
	public:
	Polarize(LinkComponent *component);
	linktype get_my_type() const;
	std::string display_link(Player* player);
	~Polarize();
};

#endif
