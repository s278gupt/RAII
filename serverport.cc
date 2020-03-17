#include "cell_info.h"
#include "exception.h"
#include "serverport.h"
#include "player.h"
using namespace std;

serverPort::serverPort(Player* owner, int r, int c): Cell{r, c}, owner{owner} {}

CellInfo serverPort::getInfo() const {
	return CellInfo{r, c, nullptr, owner, CellType::SERVERPORT};
}

void serverPort::set_link(LinkComponent*) {};

void serverPort::accept(LinkComponent* movingLink, Player* movingPlayer) {
	if (this->owner == movingPlayer) {
		 throw InvalidMove{"Cannot move link into your server port"};
	} else {
		owner->download(movingLink);
	}
}

void serverPort::validateCreateAbility() {
	throw InvalidMove("Cannot create ability on server port");
}

Cell *serverPort::createAbility(char name, Player *owner) {
	validateCreateAbility();
	return nullptr;
}
