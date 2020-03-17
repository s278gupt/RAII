#include "house.h"
#include "linkcomponent.h"
#include "exception.h"
#include "normalcellcomponent.h"
#include "normalcelldecorator.h"
#include "player.h"
#include "cell_info.h"
using namespace std;

House::House(NormalCellComponent* component, Player* owner): NormalCellDecorator{component, component->getRow(), component->getCol()}, owner{owner} {}

void House::accept(LinkComponent* movingLink, Player* player) {
	if (movingLink->getOwner() == owner) {
		if (get_link()) {
			throw InvalidMove{"A link is already in this cell"};
		}
		else {
			set_link(movingLink);
		}
	}
	else {
		throw InvalidMove{"You cannot move a link in this cell!"};
	}
}

CellInfo House::getInfo() const {
	CellInfo info = component->getInfo();

	if (info.type == CellType::NORMAL) {
		return CellInfo{info.r, info.c, info.link, owner, CellType::HOUSE};
	} else {
		return CellInfo{info.r, info.c, info.link, owner, CellType::HOUSE2X};
	}
}
