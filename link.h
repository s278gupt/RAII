#ifndef _LINK_H
#define _LINK_H
#include <string>
#include "linkcomponent.h"
#include "link_type.h"

class Player;
class CellInfo;
class NormalCellComponent;
class state;

class Link : public LinkComponent {
    char name;
	int strength;
	bool visibility = false;
	bool is_downloaded = false;
	int r,c;
	linktype type; // look at the file link_type.h for more info
	Player* owner;

    public:
        Link(char name, int strength, int r, int c, linktype type, Player* owner);
        
		int getStrength() const override;
		char get_name() override;
        int get_row() const override;
		int get_col() const override;
        state getState() override;
		bool is_visible() const override;
		bool downloaded() const override;
		linktype get_my_type() const override;
		bool is_movable() const override;
        Player *getOwner() const override;

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
