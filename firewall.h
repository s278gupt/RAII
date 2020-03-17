#ifndef _FIREWALL_H
#define _FIREWALL_H
#include "normalcelldecorator.h"

class Player;
class CellInfo;
class NormalCellComponent;

class Firewall : public NormalCellDecorator {
    Player *owner;
    public:
    Firewall(NormalCellComponent *component, Player *owner);
    void accept(LinkComponent* movingLink, Player* movingPlayer) override;
    CellInfo getInfo() const override;
};

#endif
