#include "cell_info.h"
#include "firewall.h"
#include "link_type.h"
#include "normalcelldecorator.h"
#include "linkcomponent.h"
#include "player.h"
using namespace std;

Firewall::Firewall(NormalCellComponent *component, Player *owner): NormalCellDecorator{component, component->getRow(), component->getCol()}, owner{owner} {}

void Firewall::accept(LinkComponent* movingLink, Player* movingPlayer) {
    // if movingPlayer is opponent and movingLink is a virus
    if (owner != movingPlayer) {
        if (movingLink->get_my_type() == linktype::virus) {
            // movingPlayer downloads the movingLink
            movingPlayer->download(movingLink);
        } else {
            component->accept(movingLink, movingPlayer);
        }
        // reveal opponent link
        movingLink->set_visibility(true);
    } else {
        CellInfo info = component->getInfo();
        // check if the firewall is wrapped onto the opponent firewall
        if (info.player) { 
            if (movingLink->get_my_type() == linktype::virus) {
                // movingPlayer downloads the movingLink
                movingPlayer->download(movingLink);
            } else {
                component->accept(movingLink, movingPlayer);
            }
            // reveal opponent link
            movingLink->set_visibility(true);
        } else {
            component->accept(movingLink, movingPlayer);
        }
    }
}

CellInfo Firewall::getInfo() const {
    CellInfo info = component->getInfo();

    if (info.type == CellType::NORMAL) {
        return CellInfo{info.r, info.c, info.link, owner, CellType::FIREWALL};
    } else {
        return CellInfo{info.r, info.c, info.link, owner, CellType::FIREWALL2X};
    }
}
