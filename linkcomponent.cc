#include <string>
#include "linkcomponent.h"
#include "linkboost.h"
#include "exception.h"
#include "download.h"
#include "polarize.h"
#include "control.h"
#include "scan.h"
#include "booststrength.h"
using namespace std;

LinkComponent::~LinkComponent() {}

LinkDecorator *LinkComponent::createAbility(char name, LinkComponent *link, Player* player) {
	if (name == 'L') {
        // LinkBoost
        if (link->getOwner() != player) {
            throw InvalidMove("Cannot LinkBoost opponent's link!");
        } else {
            return (new LinkBoost{link});
        }
    } else if (name == 'S') {
        // Scan
        if (link->getOwner() == player) {
            throw InvalidMove("Cannot Scan your own link!");
        } else {
            return new Scan{link};
        }
    } else if (name == 'D') {
        // Download
        return new Download{link, player};
    } else if (name == 'P') {
        // Polarize
	    return new Polarize{link};
    } else if (name == 'C') {
	    // Control
	    return new Control{link};
    } else if (name == 'B') {
        // BoostStrength
        return new BoostStrength{link};
    } else {
        string s(1, name);
        throw InvalidMove(s + " is not a valid ability");
    }
}
