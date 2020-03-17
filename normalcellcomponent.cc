#include <string>
#include "normalcellcomponent.h"
#include "cell.h"
#include "firewall.h"
#include "exception.h"
#include "cell_info.h"
#include "house.h"
using namespace std;

NormalCellComponent::NormalCellComponent(int r, int c): Cell{r, c} {}

Cell *NormalCellComponent::createAbility(char name, Player *owner) {
    if (name == 'F') {
        CellInfo info = this->getInfo();

        // check if the cell is empty
        if (info.link) {
            throw InvalidMove("Cannot place firewall on non-empty cell!");
        }

        // check if the cell is a firewall owned by the same player
        if (info.player == owner) {
            throw InvalidMove("Cannot set a Firewall on your own Firewall!");
        }
	// check if cell is sahehouse
	if (info.type == CellType::HOUSE || info.type == CellType::HOUSE2X){
		throw InvalidMove{"A firewall cannot be constructed on a safehouse!"};
	}
        return (new Firewall{this, owner});
    }
    else if (name == 'H') {
        CellInfo info = this->getInfo();

        // check if cell is empty
       	if (info.link) {
	    	throw InvalidMove{"A safehouse must be an empty cell!"};
    	}

        // check if cell is firewall
        if (info.type == CellType::FIREWALL || info.type == CellType::FIREWALL2X) {
            throw InvalidMove{"A safehouse cannot be constructed on a firewall"};
        }

	    return new House{this, owner};
    }
   
    else {
        string s(1, name);
        throw InvalidMove(s + " is not a valid ability");
    }
}

NormalCellComponent::~NormalCellComponent() {};
