#ifndef _CONTROL_H
#define _CONTROL_H
#include "linkdecorator.h"

class LinkComponent;

class Control : public LinkDecorator {
	public:
	Control(LinkComponent *component);
	bool is_movable() const override;
	~Control();
};

#endif
