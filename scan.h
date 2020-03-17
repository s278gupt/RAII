#ifndef _SCAN_H
#define _SCAN_H
#include "linkdecorator.h"

class LinkComponent;

class Scan : public LinkDecorator {
    public:
    Scan(LinkComponent *component);
    void set_visibility(bool) override;
    ~Scan();
};

#endif
