#include "normalcelldecorator.h"
#include "normalcellcomponent.h"
#include "linkcomponent.h"
#include "player.h"
#include "cell_info.h"
using namespace std;

NormalCellDecorator::NormalCellDecorator(NormalCellComponent *component, int r, int c): NormalCellComponent{r,c}, component{component} {};

void NormalCellDecorator::set_link(LinkComponent* newLink) {
    component->set_link(newLink);
}

CellInfo NormalCellDecorator::getInfo() const {
    return component->getInfo();
}

void NormalCellDecorator::accept(LinkComponent* movingLink, Player* movingPlayer) {
    component->accept(movingLink, movingPlayer);
}

LinkComponent* NormalCellDecorator::get_link() const {
	return component->get_link();
}

NormalCellDecorator::~NormalCellDecorator() { delete component; }
