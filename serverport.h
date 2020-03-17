#ifndef _SERVERPORT_H
#define _SERVERPORT_H
#include "cell.h"

class LinkComponent;
class Player;


class serverPort: public Cell{
	Player* owner; //the owner of the server port, will come in handy when a link tries to move here
	public:
	serverPort(Player* owner, int r, int c);
	void set_link(LinkComponent*) override;
	CellInfo getInfo() const override;
	void accept(LinkComponent* movingLink, Player* movingPlayer) override;
	Cell *createAbility(char name, Player *owner) override;
	void validateCreateAbility();
};

#endif
