#ifndef _BOOSTSTRENGTH_H
#define _BOOSTSTRENGTH_H
#include "linkdecorator.h"

class LinkComponent;

class BoostStrength : public LinkDecorator {
    public:
    BoostStrength(LinkComponent *component);
    ~BoostStrength();
};

#endif
