#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "game.h"
#include "exception.h"
using namespace std;
void validate_abilities(string abilities) {
	if (abilities.length() != 5) {
		throw InvalidMove{"You must enter exacty 5 abilities!\n"};
	}
	map<char, int> my_map;
	vector<char> ability_list = {'L', 'D', 'F', 'S', 'P', 'C', 'B', 'H'};
	for (char c: ability_list) {
		my_map[c] = 0;
	}
	for (char c: abilities) {
		if (c != 'L' && c != 'D' && c != 'F' && c != 'S' && c != 'P' && c != 'C' && c != 'B' && c != 'H') {
			throw InvalidMove{"Invalid ability found: " + string(1, c) + "\n"};
		}
		++my_map[c];
	}
	for (char c: abilities) {
		if (my_map[c] > 2) {
			throw InvalidMove{"You can have at most 2 abilities of the same type!\n"};
		}
	}
}



int main(int argc, char *argv[]) {
	//Read command line arguments
	
	string links1 = "V1V2V3V4D1D2D3D4";
	string links2 = "V1V2V3V4D1D2D3D4";
	string ability1 = "LFDSP";
	string ability2 = "LFDSP";
	bool graphics = false;
	
	//TODO: CHECK FOR CORRECT INPUT
	try {
	for (int i = 1; i < argc;){
		if (string(argv[i]) == "-ability1"){
			try {
				validate_abilities(argv[i + 1]);
			}
			catch (InvalidMove& error) {
				cerr << error.getErrorMessage();
				exit(EXIT_SUCCESS);
			}
			ability1 = argv[i+1];
			i += 2;
		}
		else if (string(argv[i]) == "-ability2"){
			try {
				validate_abilities(argv[i + 1]);
			}
			catch (InvalidMove& error) {
				cerr << error.getErrorMessage();
				exit(EXIT_SUCCESS);
			}
			ability2 = argv[i+1];
			i += 2;
		}
		else if (string(argv[i]) == "-link1"){
			links1 = argv[i+1];
			i += 2;
		}
		else if (string(argv[i]) == "-link2"){
			links2 = argv[i+1];
			i += 2;
		}
		else if (string(argv[i]) == "-graphics"){
			graphics = true;
			++i;
		}
		else {
			throw InvalidMove{"Unrecognized Option found: " + string(argv[i])};
		}
	}
	}
	catch (InvalidMove& error) {
		cerr << error.getErrorMessage() << endl;
		exit(EXIT_SUCCESS);
	}
	
	// Initialize game
	Game g;
	g.game_init(links1, links2, ability1, ability2, graphics);
	if (!graphics){ cout <<  g;}

	// Main game loop
	string cmd;
	ifstream fileinput;
	bool call_abilities = false;

	while (true){
		istream &input = fileinput ? fileinput : cin;

		if (cin.eof()){ break;}
		if(!(input >> cmd)){ continue;} //Prevent failed read of end of file
		if (cmd == "move"){
			// move link
			char linkname;
			string direction;
			input >> linkname >> direction;

			try{
				g.move_link(linkname, direction);

				// Change turn
				g.change_turn();
				call_abilities = false;
				if(!graphics){ cout << endl << g << endl;}
			}
			catch (InvalidMove &e){ 
				cout << e.getErrorMessage() << endl;
				g.appendStringToGraphics(e.getErrorMessage());
			}
		}
		else if (cmd == "abilities"){
			// show abilities
			if(graphics){
				string s = "Abilities:\n" + g.show_abilities();
				g.appendStringToGraphics(s);
			}
			else{
				cout << g.show_abilities() << endl;
			}
		}
		else if (cmd == "ability"){
			// use ability
			int a;
			cin >> a;
			if (!(1 <= a && a <= 5)) {
				cout << a << " Invalid ability" << endl;
				g.appendStringToGraphics("Invalid ability");
				continue;
			}
			if (call_abilities){
				cout << "Already Used one ability this turn" << endl;
				g.appendStringToGraphics("Already Used one \nability this turn");
				continue;
			}

			char c;
			cin >> c;
			int row;
			int col;

			try {
				if ('0' <= c && c <= '7') {
					row = c - '0';
					cin >> col;
					g.activateAbility(a, row, col);
				} else {
					g.activateAbility(a, c);
				}
				call_abilities = true;

			} catch (InvalidMove &e) {
				cout << e.getErrorMessage() << endl;
				
				if (e.getErrorMessage().length() > 30){
					string e1 = e.getErrorMessage().substr(0, 30);
					string e2 = e.getErrorMessage().substr(30);
					g.appendStringToGraphics(e1+"\n"+e2);
				}
				else{
					g.appendStringToGraphics(e.getErrorMessage());
				}
				continue;
			}
			
		}
		else if (cmd == "board"){
			if (graphics){
				stringstream ss;
				ss << g;
				g.appendStringToGraphics(ss.str());
			}
			else{
				cout << g;
			}
		}
		else if (cmd == "sequence"){
			string file;
			input >> file;
			fileinput.open(file);
		}
		else if (cmd == "quit"){
			break;
		}
		
		//Check if game ends
		int winner = g.who_won();
		if (winner){
			string s;
			stringstream ss{s};
			ss << "Game Over. Player " << winner << " won." << endl;
			cout << ss.str();
			if (graphics){
				g.writeToGraphics(ss.str());
				input >> cmd;
			}
			break;
		}
	}
	
	return 0;
}
