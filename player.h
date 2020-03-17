#ifndef _PLAYER_H
#define _PLAYER_H
#include <map>
#include <utility>
#include <vector>
#include <string>

class LinkComponent;

class Player{
	std::map<char, LinkComponent*> links;
	std::vector<std::pair<bool, char>> abilities;
	int data_downloaded = 0;
	int viruses_downloaded = 0;
	char c;

	public:
	Player(char c);
	void player_init(std::string links, std::string ability_string);
	~Player();
	
	std::string show_abilities();
	int ability_count();
	void set_link(LinkComponent* newLink, char oldLink);
	void setAbilityUsed(int index);

	bool is_my_link(char name);
	int get_datacount();
	int get_viruscount();
	LinkComponent* get_link(char name);
	void updata();
	void upvirus();
	bool abilityUsed(int a); // a is the index of the ability
	char getAbilityName(int index);
	int getPlayerId();

	void download(LinkComponent* link);
	void useAbility(int a, LinkComponent*);
};

#endif
