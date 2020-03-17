#ifndef _HOUSE_H
#define _HOUSE_H
#include "normalcelldecorator.h"

class Player;
class NormalCellComponent;
class LinkComponent;
class CellInfo;

class House: public NormalCellDecorator {
	Player* owner;
	public:
		House(NormalCellComponent* component, Player* player);
		void accept(LinkComponent* movingLink, Player* movingPlayer) override;
		CellInfo getInfo() const override;
};

#endif
