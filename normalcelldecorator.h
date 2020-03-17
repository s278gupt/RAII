#ifndef _NORMALCELLDECORATOR_H
#define _NORMALCELLDECORATOR_H
#include "normalcellcomponent.h"

class LinkComponent;
class Player;

class NormalCellDecorator : public NormalCellComponent {
    protected:
        NormalCellComponent *component;
    public:
        NormalCellDecorator(NormalCellComponent *component, int r, int c);
        void set_link(LinkComponent* newLink) override;
        CellInfo getInfo() const override;
        void accept(LinkComponent* movingLink, Player* movingPlayer) override;
		LinkComponent* get_link() const override;
        virtual ~NormalCellDecorator() = 0;
};

#endif
