#ifndef _CELL_INFO_H
#define _CELL_INFO_H

class Player;
class LinkComponent;
enum class CellType { NORMAL, SERVERPORT, FIREWALL, HOUSE, FIREWALL2X, HOUSE2X };

// This info struct has the purpose of grouping important information about cells

struct CellInfo {
	int r,c;
	LinkComponent* link;
	Player* player;
	CellType type;
};

#endif
