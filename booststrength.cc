#include "booststrength.h"
#include "linkdecorator.h"
#include "linkcomponent.h"
using namespace std;

BoostStrength::BoostStrength(LinkComponent *component): LinkDecorator{component} {
    component->setStrength(component->getStrength() + 1);
}

BoostStrength::~BoostStrength() {}
