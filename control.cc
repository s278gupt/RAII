#include "linkdecorator.h"
#include "linkcomponent.h"
#include "control.h"
using namespace std;

Control::Control(LinkComponent *component): LinkDecorator{component} {}

bool Control::is_movable() const{
	return !component->is_movable();
}

Control::~Control() {}
