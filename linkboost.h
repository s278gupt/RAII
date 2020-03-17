#ifndef _LINKBOOST_H
#define _LINKBOOST_H
#include <string>
#include "linkdecorator.h"

class LinkComponent;
class CellInfo;

class LinkBoost : public LinkDecorator {    
    public:
    LinkBoost(LinkComponent *component);
    CellInfo move(std::string direction) override;
    ~LinkBoost();
};

#endif
