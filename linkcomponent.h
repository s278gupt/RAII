#ifndef _LINKCOMPONENT_H
#define _LINKCOMPONENT_H
#include <string>
#include "link_type.h"

class Player;
class CellInfo;
class NormalCellComponent;
class state;
class LinkDecorator;

class LinkComponent {	
	public:
	virtual char get_name() = 0;
	virtual int get_row() const = 0;
	virtual int get_col() const = 0;
	virtual state getState() = 0;
	virtual linktype get_my_type() const = 0;
	virtual bool is_visible() const = 0;
	virtual bool downloaded() const = 0;
	virtual int getStrength() const = 0;
	virtual Player *getOwner() const = 0;
	virtual bool is_movable() const = 0;

	virtual void set_row(int) = 0;
	virtual void set_col(int) = 0;
	virtual void set_visibility(bool) = 0;
	virtual void setStrength(int) = 0;

	// Factory method to create Link Abilities
	LinkDecorator *createAbility(char name, LinkComponent *link, Player* player);
	virtual std::string display_link(Player* active_player) = 0; //displays link to the opponent based on visibility
	virtual void download() = 0;
	virtual CellInfo move(std::string direction) = 0;
	virtual void battle(LinkComponent *currentLink, NormalCellComponent *disputedCell) = 0; // movingLink calls this to battle the link in an occupied Cell
	virtual ~LinkComponent() = 0;
};

#endif
