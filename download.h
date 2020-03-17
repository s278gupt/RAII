#ifndef _DOWNLOAD_H
#define _DOWNLOAD_H
#include "linkdecorator.h"

class Player;
class LinkComponent;

class Download: public LinkDecorator {
	public:
		Download(LinkComponent* component, Player* player);
		~Download();
};

#endif
