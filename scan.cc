#include "linkdecorator.h"
#include "linkcomponent.h"
#include "scan.h"
using namespace std;

Scan::Scan(LinkComponent *component): LinkDecorator{component} {
	set_visibility(true);
}

void Scan::set_visibility(bool visible) {
	component->set_visibility(visible);
}

Scan::~Scan() {}
