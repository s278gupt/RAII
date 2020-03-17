#include "download.h"
#include "linkcomponent.h"
#include "player.h"
#include "linkdecorator.h"
using namespace std;

Download::Download(LinkComponent* component, Player* player): LinkDecorator{component} {
	player->download(component);
}

Download::~Download() {}
