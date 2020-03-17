#ifndef _NORMALCELL_H
#define _NORMALCELL_H
#include "normalcellcomponent.h"

class LinkComponent;
class CellInfo;
class Player;

class NormalCell : public NormalCellComponent {
	LinkComponent* link; // the link that is on this cell, may be nullptr
    public:
	NormalCell(LinkComponent* link, int r, int c);
    void set_link(LinkComponent* newLink) override;
	CellInfo getInfo() const override;
	LinkComponent* get_link() const;
	void accept(LinkComponent* movingLink, Player* movingPlayer) override;
};

#endif
