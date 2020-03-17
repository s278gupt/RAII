#ifndef _NORMALCELLCOMPONENT_H
#define _NORMALCELLCOMPONENT_H
#include "cell.h"

class Player;
class LinkComponent;

class NormalCellComponent: public Cell {
	public:
	// Factory method to create Cell Abilities
	Cell *createAbility(char name, Player *owner) override;
	virtual LinkComponent* get_link() const = 0;
	NormalCellComponent(int r, int c);
	virtual ~NormalCellComponent();
};

#endif
