#include "cell_info.h"
#include "cell.h"
#include "player.h"
#include "linkcomponent.h"
#include "exception.h"
#include "state.h"
#include "normalcell.h"
#include "normalcellcomponent.h"
using namespace std;

NormalCell::NormalCell(LinkComponent* link, int r, int c): NormalCellComponent{r, c}, link{link} {}

CellInfo NormalCell::getInfo() const  {
	return CellInfo{r, c, link, nullptr, CellType::NORMAL};
}

void NormalCell::set_link(LinkComponent* newLink) {
	this->link = newLink;
	if (link){
		link->set_row(r);
		link->set_col(c);
	}
}
LinkComponent* NormalCell::get_link() const {
	return link;
}
void NormalCell::accept(LinkComponent* movingLink, Player* movingPlayer) {
	if (this->link == nullptr) {
		set_link(movingLink);
	} else {
		// check if the current link has been downloaded and remove it
		state linkState = (this->link)->getState();
		if(linkState.downloaded && linkState.r == this->r && linkState.c == this->c) {
			set_link(nullptr);
			notifyObservers();
			set_link(movingLink);
		} else if (movingPlayer->is_my_link(link->get_name())) {
			throw InvalidMove("Cannot battle your own link!");
		} else {
			movingLink->battle(link, this);
		}
	}

	notifyObservers();
}
