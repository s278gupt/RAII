#ifndef _CELL_H
#define _CELL_H
#include "subject.h"

class LinkComponent;
class Player;

class Cell: public Subject {
	protected:
		int r, c;
	public:
	Cell(int r, int c);
	int getRow() const;
	int getCol() const;
	virtual void set_link(LinkComponent*) = 0; //will set the link to equal the argument after neccessary checks have been done by the function below
	virtual void accept(LinkComponent* movingLink, Player* movingPlayer) = 0;
	virtual Cell *createAbility(char name, Player *owner) = 0;
	virtual ~Cell();
};

#endif
