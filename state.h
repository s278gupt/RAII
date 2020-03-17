#ifndef _STATE_H_
#define _STATE_H_

class Player;

struct state {
	int r,c;
	Player* owner;
	bool downloaded;
};

#endif
