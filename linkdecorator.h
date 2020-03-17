#ifndef _LINKDECORATOR_H
#define _LINKDECORATOR_H
#include <string>
#include "linkcomponent.h"
#include "link_type.h"

class Player;
class CellInfo;
class NormalCellComponent;
class state;

class LinkDecorator : public LinkComponent {
    protected:
        LinkComponent *component;
    public:
        LinkDecorator(LinkComponent *component);
        virtual ~LinkDecorator() = 0;

        int getStrength() const override;
        char get_name() override;
        int get_row() const override;
        int get_col() const override;
        state getState() override;
        bool is_visible() const override;
        bool downloaded() const override;
        linktype get_my_type() const override;
        Player *getOwner() const override;
	    bool is_movable() const override;
        
        void set_row(int) override;
        void set_col(int) override;
        void set_visibility(bool) override;
        void setStrength(int) override;
        
        void download() override;
        CellInfo move(std::string direction) override;
        std::string display_link(Player* active_player) override; //displays link to the opponent based on visibility
        void battle(LinkComponent *currentLink, NormalCellComponent *disputedCell) override;
};

#endif
