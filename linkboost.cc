#include "cell_info.h"
#include "exception.h"
#include "linkboost.h"
#include "linkcomponent.h"
#include "linkdecorator.h"
using namespace std;

LinkBoost::LinkBoost(LinkComponent *component): LinkDecorator{component} {};

CellInfo LinkBoost::move(string direction) {
        CellInfo moveSoFar = component->move(direction);

        if (direction == "up") {
                moveSoFar.r -= 1;
        } else if (direction == "down") {
                moveSoFar.r += 1;
        } else if (direction == "left") {
                moveSoFar.c -= 1;
        } else if (direction == "right") {
                moveSoFar.c += 1;
        } else {
                throw InvalidMove("Bad Direction");
        }

        return moveSoFar;
}

LinkBoost::~LinkBoost() {}
