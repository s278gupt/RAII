#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <vector>
#include "cell.h"
#include "window.h"
#include "observer.h"
#include "subject.h"
#include "player.h"

class GraphicsDisplay: public Observer {
	Xwindow window{800, 800};
	int gridSize = 500; // pixel size of grid
	int grid_x = 25; //x-coordinate start of grid
	int grid_y = 150; //y-coordinate start of grid

	int textbox_x = grid_x+gridSize+5;

	Player* player_1;
	Player* player_2;
	int turn = 1;

	std::string text;
	
	void drawTextBox();
	void drawCell(int r, int c, int colour, int offset = 2);
	void drawCellBorder(int r, int c, int colour); //draws a border on an EMPTY cell
	public:

	void redrawLinks(const std::vector<std::vector<Cell*>>& grid);
	GraphicsDisplay(Player* player_1, Player* player_2);
	void notify(Subject& whoNotified) override;
	void setLink(CellInfo info);

	void writeFirstStr();
	void appendString(std::string s); //Writes more string into the textbox
	void writeString(std::string s, int line = 1); //Writes a string into the textbox

	void change_turn(const std::vector<std::vector<Cell*>>& grid);
	void updatePlayerInfo();
};

#endif
