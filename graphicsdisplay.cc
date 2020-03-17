#include <string>
#include <sstream>
#include <vector>
#include "graphicsdisplay.h"
#include "window.h"
#include "player.h"
#include "subject.h"
#include "cell.h"
#include "cell_info.h"
#include "linkcomponent.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(Player* player_1, Player* player_2): 
player_1{player_1}, player_2{player_2}{
	//Warmup
	for (int i = 0; i < 8; i++){
		window.fillRectangle(0, 0, gridSize, gridSize, Xwindow::White);
	}

	window.fillRectangle(0, 0, window.getWidth(),
		       	window.getHeight(), Xwindow::Ivory);
	
	// Draw grid rectangle
	window.fillRectangle(grid_x, grid_y, gridSize, gridSize, Xwindow::Gainsboro);
	
	//test colours:
	for (int i = 0; i < 7; i++){
		//window.fillRectangle(i*50, i*50, 50, 50, i);
	}

	// Draw gridlines
	for (int i = 0; i <= 8; i++){
		window.drawLine(grid_x, gridSize*i/8+grid_y,
			       	gridSize+grid_x, gridSize*i/8+grid_y);
		window.drawLine(gridSize*i/8+grid_x, grid_y,
			       	gridSize*i/8+grid_x, gridSize+grid_y);
		if (i != 0){
			stringstream ss{};
			ss << i-1;
			window.drawBigString(grid_x-15, grid_y + gridSize*i/8-gridSize/16,
					ss.str(), Xwindow::Black);
			window.drawBigString(grid_x + gridSize*i/8-gridSize/16, grid_y-15,
					ss.str(), Xwindow::Black);
		}
	}
	window.fillRectangle(grid_x, grid_y-3, gridSize, 3, Xwindow::CornflowerBlue);
	window.fillRectangle(grid_x, gridSize+grid_y, gridSize, 3, Xwindow::PaleVioletRed);

	// Draw text box
	drawTextBox();

	// Write Players
	window.drawBigString(grid_x+gridSize/2, 25,
		       	"Player 1", Xwindow::Black);
	window.drawBigString(grid_x+gridSize/2, grid_y+gridSize+25,
		       	"Player 2", Xwindow::Black);

	// Write Player Info:
		// Player 1:
	window.drawBigString(grid_x+2*gridSize/3, 50, "Downloaded", Xwindow::Black);
	window.drawBigString(grid_x+2*gridSize/3, 65, "Data: ", Xwindow::Black);
	window.drawBigString(grid_x+2*gridSize/3, 80, "Virus: ", Xwindow::Black);
	window.drawBigString(grid_x+gridSize/4, 50, "Abilities: ", Xwindow::Black);

		// Player 2:
	window.drawBigString(grid_x+2*gridSize/3, grid_y+gridSize+50,
		"Downloaded", Xwindow::Black);	
	window.drawBigString(grid_x+2*gridSize/3, grid_y+gridSize+65,
			"Data: ", Xwindow::Black);
	window.drawBigString(grid_x+2*gridSize/3, grid_y+gridSize+80,
			"Virus: ", Xwindow::Black);
	window.drawBigString(grid_x+gridSize/4, grid_y+gridSize+50,
			"Abilities: ", Xwindow::Black);
		
}

void GraphicsDisplay::writeFirstStr(){
	string FirstMsg;
	stringstream ss{FirstMsg};
	ss << "Welcome to RAIInet!";
	ss << "\nCommands Are: ";
	ss << "\nmove <A> <dir>";
	ss << "\nabilities";
	ss << "\nability <N>";
	ss << "\nboard";
	ss << "\nsequence <file>";
	ss << "\nquit";
	ss << "\nIt is Player 1's turn";

	writeString(ss.str());
}

void GraphicsDisplay::drawTextBox(){
	window.fillRectangle(textbox_x, 0,
			window.getWidth()-textbox_x, window.getHeight());
}

void GraphicsDisplay::drawCell(int r, int c, int colour, int offset){
	int y_start = grid_y + gridSize*r/8 + offset;
	int x_start = grid_x + gridSize*c/8 + offset;
	window.fillRectangle(x_start, y_start, 
			gridSize/8+2-2*offset, gridSize/8+2-2*offset, colour);


}

void GraphicsDisplay::drawCellBorder(int r, int c, int colour){	
	drawCell(r, c, colour, 0);
	drawCell(r, c, Xwindow::Gainsboro, 3);
}

void GraphicsDisplay::writeString(string s, int line){
	if (line == 1){
		drawTextBox();
	}
	text = s;
	int line_counter = line;
	stringstream ss{s};
	string to;
	while(getline(ss, to, '\n')){
		window.drawBigString(textbox_x+5, 
				16*line_counter, to, Xwindow::WebGreen);
		line_counter++;
	}
}

void GraphicsDisplay::appendString(string s){
	text = text+"\n=-=-=-=-=-=-=-=-=\n"+s;
	writeString(text);
}	


void GraphicsDisplay::notify(Subject& whoNotified){
	updatePlayerInfo();
	CellInfo info = whoNotified.getInfo();
	if (info.type == CellType::SERVERPORT){
		drawCell(info.r, info.c, Xwindow::WebGreen);
	}
	else{ setLink(info);}

	if (info.type == CellType::FIREWALL || info.type == CellType::FIREWALL2X){
		drawCellBorder(info.r, info.c, Xwindow::Red);
		int colour = 0;
		if (info.type == CellType::FIREWALL2X){ colour = Xwindow::Red;}
		else if (info.player->getPlayerId() == 1){ colour = Xwindow::CornflowerBlue;}
		else{ colour = Xwindow::PaleVioletRed;}
		drawCell(info.r, info.c, colour, 20);
	}
	else if (info.type == CellType::HOUSE || info.type == CellType::HOUSE2X){
		drawCellBorder(info.r, info.c, Xwindow::Black);
		int colour = 0;
		if (info.type == CellType::HOUSE2X){ colour = Xwindow::Black;}
		else if (info.player->getPlayerId() == 1){ colour = Xwindow::CornflowerBlue;}
		else {colour = Xwindow::PaleVioletRed;}
		drawCell(info.r, info.c, colour, 20);
	}
}


void GraphicsDisplay::setLink(CellInfo info){
	if (info.link){
		// Draw link circle
		int x_coord = grid_y + gridSize*(info.r+1)/8-gridSize/16;
		int y_coord = grid_x + gridSize*(info.c+1)/8-gridSize/16;
		string s;
		stringstream ss{s};
		ss << info.link->get_name();
		string type = info.link->display_link(turn % 2 == 0 ? player_2 : player_1);
		string link_type = (type.substr(type.length()-2)).substr(0, 1);

		int border_colour;
		if (link_type == "V"){ border_colour = Xwindow::Red;}
		else if (link_type == "D"){ border_colour = Xwindow::WebGreen;}
		else{ border_colour = Xwindow::Black;}

		window.fillCircle(y_coord, x_coord, 36, border_colour);

		if (player_1->is_my_link(info.link->get_name())){
			window.fillCircle(y_coord, x_coord, 32, Xwindow::CornflowerBlue);
		}
		else{
			window.fillCircle(y_coord, x_coord, 32, Xwindow::PaleVioletRed);
		}
		window.drawString(y_coord-2, x_coord+10, type.substr(type.length() - 2));
		window.drawString(y_coord-1, x_coord-2, ss.str());
		
	}
	else{
		drawCell(info.r, info.c, Xwindow::Gainsboro);
	}	
}

void GraphicsDisplay::redrawLinks(const vector<vector<Cell*>>& grid){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			CellInfo info = grid[i][j]->getInfo();
			if (info.link){
				setLink(info);
			}
		}
	}
}
	
void GraphicsDisplay::change_turn(const vector<vector<Cell*>>& grid){
	turn++;
	redrawLinks(grid);
	(turn % 2 == 0) ? writeString("Player 2 Turn") : writeString("Player 1 Turn");

}

void GraphicsDisplay::updatePlayerInfo(){
	for (int i = 0; i < player_1->get_datacount(); i++){
		window.fillCircle(grid_x+2*gridSize/3+10*(i+1)+40,
			       	61, 10, Xwindow::Green);
	}

	for (int i = 0; i < player_1->get_viruscount(); i++){
		window.fillCircle(grid_x+2*gridSize/3+10*(i+1)+50,
			       	76, 10, Xwindow::Red);
	}

	for (int i = 0; i < 5; i++){
		int colour1 = i < player_1->ability_count() ? Xwindow::Purple : Xwindow::White;
		int colour2 = i < player_2->ability_count() ? Xwindow::Purple : Xwindow::White;
		window.fillCircle(grid_x+gridSize/4+10*(i+1)+10, 61, 10, colour1);
		window.fillCircle(grid_x+gridSize/4+10*(i+1)+10, grid_y+gridSize+61,
				10, colour2);
	}

	for (int i = 0; i < player_2->get_datacount(); i++){
		window.fillCircle(grid_x+2*gridSize/3+10*(i+1)+40,
			       	grid_y+gridSize+61, 10, Xwindow::Green);
	}

	for (int i = 0; i < player_2->get_viruscount(); i++){
		window.fillCircle(grid_x+2*gridSize/3+10*(i+1)+50,
			       	grid_y+gridSize+76, 10,  Xwindow::Red);
	}


}

