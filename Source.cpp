//Quintin Ott : Text base RPG
//The goal of this code was to make a text based game with custom character creation, and a brief easy to understand storyline/objective which could be expanded on later if so desired to be a more robust system!
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
string ans; //generic global string used by both the program and user in order to store temporary values

struct Item{ // There are items that the user can find, make, and use!
	string name; // name of the item
	int quantity; // how many of the item there should be
	string stat; // which stat is being modified by the item
	string discription; // discription of what the item does
	int bonus; // numerical bonus granted by the item
	Item() { // default constructor
		name = " ";
		quantity = 0;
		stat = " ";
		discription = " ";
		bonus = 0;
	}
	Item(string name1, int quantity1, string stat1, string discription1, int bonus1);
};
struct Stats { // These are the basic core values for 
	string name; // Name of the entity that the stat block is linked to
	int hp; // number of hit points of the character
	int bab; // the baseline attack bonus for determining whether the character hits it's target
	int str; // strength for deteremining physical damage
	int dex; // dexterity for deteremining the accuracy of a character
	int con; // consitituion for determining a characters hp
	Stats() { // default constructor
		name = " ";
		hp = 0;
		bab = 0;
		str = 0;
		dex = 0;
		con = 0;
	}
	Stats(string name, int hp, int bab, int str, int dex, int con);
};
class Attack {
private:
	int nbrDice; //number of "dice" rolled
	int typDice; //type of "dice" rolled Ei. four sided/six sided/ eight sided ... ex... 
public:
	string name; //name of attack 
	Attack() { //default constructor
		name = "Unarmed Strike";
		nbrDice = 1;
		typDice = 3;
	}
	Attack(string weapon, int nDice, int tDice);
	bool toHit(Stats target, Stats scores);
	int calcDMG(int str); //determines the if the character hits its target, and if so what kind of damage it deals
};
class Character {
public:
	vector<Item> inv; // The container for the characters items, Ei the characters inventory
	Attack attack; // your characters attack 
	int kills = 0; // how many encounters you have defeated!
	Stats values; // the stat block for the character
	Character() {};
	Character(Stats scores); //constructor without inventory
	Character(vector<Item> items, Stats scores); //constructor with inventory;
	Character(Stats scores, Attack weapon); //constructor with attack
	string toString(); //prints out important character information/feilds
	void addItem(Item loot); //adds an already generated item to the characters inventory
	Item newItem(); //adds a newly created item to the user inventory based off of user input
	string useItem(int ndx); //uses an item from the characters inventory
};
Character encounters[3]; //instantiating the types of character that the player will encounter along their adventures
Character bat = Character(Stats("Bat",3,1,1,3,3),Attack("bite",1,4));
Character zombie = Character(Stats("Zombie", 5, 3, 2, 1, 5), Attack("Slam", 1, 6));
Character lich = Character(Stats("Lich", 10, 5, 5, 3, 10), Attack("Necrotic Sword", 2, 8));
Item drops[4];
int main() {
	encounters[0] = bat;
	encounters[1] = zombie;
	encounters[2] = lich;
	Stats temp; //temp container for stats to be constructed into a character
	ifstream input; //potenail file input
	ofstream output; // potenial file output
	cout << "\nWould you like to enter your stats manually or would you like to upload a file?";
	cout << "\nIf you would like to input a file please leave it formatted as only four integers corresponding with BAB, STR, DEX, and CON in that order";
	cout << "\nPlease enter manual or file: ";
	cin >> ans;
	if (ans == "file") { //checks to see if the user wishes to provide a file or input character information manually
		input.open("infile.txt");
		input >>  temp.bab >> temp.str >> temp.dex >> temp.con;
	}
	else{ //manual user input, prompts for each needed field to be instantiated by the constructor
		cout << "\nsense you are inputting your stats manually please enter them one at a time when prompted";
		cout << "\n\tBAB: ";
		cin >> temp.bab;
		cout << "\n\tStr: ";
		cin >> temp.str;
		cout << "\n\tDex: ";
		cin >> temp.dex;
		cout << "\n\tCon: ";
		cin >> temp.con;
		temp.hp = temp.con;
	}
	cout << "\nOh? It would seem as if you have awoken. Quite the crazy night you had... ermm... I am sorry, but what was your name again?";
	cout << "\nTrust me, I never forget a name, but last I recall you never gave me yours. You were just raving on about being the world richest adventurer and how you have come to town seeking your fortune hunting the mosnters found here in Riverwood";
	cout << "\nSo as I said, what is your name? : ";
	cin.ignore();
	getline(cin, ans);
	temp.name = ans;
	cout << "\n Ahh yes " + temp.name + ", I remember now! You vaugely did mention something along those lines";
	Character player(temp); //generates a character for the user based on their input
	cout << "\n\tDo you have any items. Yes or No? : "; //prompts the user if they have any items, at which point they will have to put in the items values
	cin >> ans;
	if (ans == "Yes") { //prompts to see if the user has any items
		cout << "\n\tHow many items do you have? : ";
		int count;
		cin >> count;
		for (int i = 0; i < count; i++) {//allows user to input any set number of custom items that they want, have fun. This is the most custom and fun part of this game
			player.addItem(player.newItem());
		}
	}
	cout << "\n\n\tAnd this is where your journey begins.";
	cout << "\nStarting, in the once quite village of Riverside, which has been recently been plagued by all number of foul creatures.";
	cout << "\nYou a fledging adventurer and have decided to assist the town accepting there quest for quite the handsome reward of 500 gold pieces";
	cout << "\nYour task? To vanquish 5 enemies consecuatively!";
	bool alive = true; //player defaults to being alive
	while (player.kills < 5 && alive) { // so long as the player is both alive and under the number of required kills the game continues
		bool adventuring = true;
		Character encounter = encounters[rand()%3]; // selects a random encounter each time for you to face from a set of pre-generated characters
		cout << "\nOh no! It appears as if you have ran into a " + encounter.values.name;
		while (adventuring) {
			cout << "\nWhat do you do? Fight, Use Item, Flee : "; //allows user input to simulate combat!
			cin.ignore();
			getline(cin, ans);
			if (ans == "Fight") { //fight option
				if (player.attack.toHit(encounter.values, player.values)) { // if the character hits generate dmg to be dealt to the enemy!
					int dmg = player.attack.calcDMG(player.values.str);
					encounter.values.hp = encounter.values.hp - dmg;
					if (encounter.values.hp > 0) { //is the enemy dead?
						cout << "\n\t" + player.values.name + " struck the " + encounter.values.name + " with " + player.attack.name + " for " + to_string(dmg) + " damage!"; //print out damage dealt to creature
					}
					else { //the enemy is dead
						cout << "\n\t" + encounter.values.name + " has been slain by " + player.values.name; // display that it is dead
						player.kills++; // increase the kill count
						cout << "\n\t Congratulations you now have " + to_string(player.kills) +" kill(s), but who know what you might encounter next!";
						break; //break this combat loop, and get a new encounter to progress
					}
				}
				else {
					cout << "\nOh no it looks like you missed, better luck nex time";
				}
			}
			if (ans == "Flee") { //the user can flee, but that breaks the rules of quest line, so they must start over. The users character's hp is reset back to full, but their quest tracker also resets
				cout << "\nIf you successfully flee your hp be will be reset but your kill counter will be too! Are you sure you would still like to Flee : Yes or No";
				cin >> ans;
				if (ans == "Yes") {
					if (rand() % 100 + 1 > 25) { // there is a failure chance for running away
						player.kills = 0;
						player.values.hp = player.values.con;
						break;
					}
					else {
						cout << "\nNot only are you a coward, but you are a failure;\n\t but look at the bright side, you can keep your kill streak if you still vanquish the enemy before you";
					}
				}
			}
			if (ans == "Use Item") {
				cout << "\nOh is this a tactican I see? \nAlrighty then, lets take a look at your stats and inventory and see which item you would like to use!\n";
				cout << player.toString(); //allows the user to see there character's stats and values so that they can make an informed decision
				cout << "\nPlease select the number corresponding with the items location! : ";
				int ndx;
				cin >> ndx; //takes the user input of the item the user wishes to use
				while(ndx > sizeof(player.inv) - 1){ //so long as the inputed index is with the range of the vector, the item is "used" via the useItem function
					cout << "\n\tPlease input a valid index : ";
					cin >> ndx;
				}
				cout << player.useItem(ndx);//if the user has a custom item inputed that would cause them selves to die 
				if (player.values.hp <= 0) {
					cout << "Congratulations task failed successfully, you managed to reduced your own hp to 0 in a game where you control the flow of items. Truly curiosity killed the cat, but you have been slain by your own huberis";
					alive = false;
					break;
				}
			}
			if (encounter.attack.toHit(player.values, encounter.values)) {//This is the encounters "turn" if you want to think of it like that. The encounter always moves after the player, and always attacks
				int dmg = encounter.attack.calcDMG(encounter.values.str);
				cout << "\nA " + encounter.values.name + " hit you with " + encounter.attack.name + " for " + to_string(dmg) + " damage!";
				if (player.values.hp - dmg <= 0) {//if the encounter lands a hit on the character and that hit is enough to drop the characters hp to 0 then the user's character is dead, and the user loses the game
					cout << "\n\t You have been slain by " + encounter.values.name + "'s " + encounter.attack.name;
					alive = false;
					break;
				} //encounters damage dealt to the user is displayed
				player.values.hp = player.values.hp - dmg;
			}
			else { //the encounter can miss its attack, just like the user's character
				cout << "\nThe " + encounter.values.name + " attempted to hit you, but missed!";
			}
		}
	}
	if (alive) { // if you terminate the loop via completing the quest then you win the game 
		cout << "\nHazah! This will forever go done in history as the day you saved the town of Riverwood, and more importantly collected your ransom of 500 gold!";
		Item reward = Item("Gold", 500, "hp", "This is magic healing coin, or you can just use it as currency", 1);
		player.addItem(reward);
	}
	else {//if you terminated the loop because you died, well then you lost. Game over.
		cout << "\n\n GAME OVER! Restart to replay!";
	}
	cout << "\nWould you like to export your characters current information? Yes or No :";
	cin >> ans;
	if (ans == "Yes") { //checks to see if the user would like to export there characters info 
		output.open("outfile.txt");
		output << player.toString();
	}
	input.close();
	output.close();
}
Item::Item(string name1, int quantity1, string stat1, string discription1, int bonus1){
	name = name1;
	quantity = quantity;
	stat = stat1;
	discription = discription1;
	bonus = bonus1;
};
Stats::Stats(string name1, int hp1, int bab1, int str1, int dex1, int con1) {
	name = name1;
	hp = hp1;
	bab = bab1;
	str = str1;
	dex = dex1;
	con = con1;
};
Attack::Attack(string weapon, int nDice, int tDice) {
	name = weapon;
	nbrDice = nDice;
	typDice = tDice;
};
Character::Character(Stats scores){ // initalizing stats is the minimum requirement for this code to properly function, so every construct will have stats as a prerequiste parameter.
	values = scores;
};
Character::Character(vector<Item> items, Stats scores){ // initalizing character with inventory provided
	inv = items;
	values = scores;
};
Character::Character(Stats scores, Attack weapon) {// Character with a specific stat block, and attack, but not inventory EI. encounters
	values = scores;
	attack = weapon;
};
Item Character::newItem() { //a method version of the item constructor for the user to be able to call
	Item loot;
	string temp;
	cout << "\n\tPlease enter your items information when requested. Please enter either a single word or number depending on what is required";
	cout << "\n\tName: ";
	cin.ignore();
	getline(cin, loot.name);
	cout << "\n\tQuantity: ";
	cin >> loot.quantity;
	cout << "\n\tDiscription: ";
	cin.ignore();
	getline(cin, loot.discription);
	cout << "\n\tEffected Stat: ";
	cin >> loot.stat;
	cout << "\n\tWhat bonus is granted by the item when consumed? : ";
	cin >> loot.bonus;
	return loot;
}
void Character::addItem(Item loot) { //adds item to characters inventory
	vector<Item> temp = inv;
	int duplicate = -1;
	for (int i = 0; i < temp.size(); i++) { //goes through current inventory to see if the item is present
		if (temp.at(i).name == loot.name) {
			duplicate = i;
		}
	}
	if (duplicate == -1) {
		inv.push_back(loot); //if the item is not present, adds item to the back of the inventory
	}
	else {
		inv.at(duplicate).quantity = inv.at(duplicate).quantity + loot.quantity; // if the item is already present, increases the quantity field of the item already in the inventory
	}
};
string Character::useItem(int ndx) {
	string ans = " ";
	Item temp = inv[ndx-1]; //gets a point to the item
	ans = temp.stat; //checks to see what stat the item would modify and changes that value by the bonus granted by the item
	if (ans == "hp") { 
		values.hp = values.hp + temp.bonus;
	}
	if (ans == "str") {
		values.str = values.str + temp.bonus;
	}
	if (ans == "dex") {
		values.dex = values.dex + temp.bonus;
	}
	if (ans == "con") {
		values.con = values.con + temp.bonus;
	}
	cout << "\nYou used a " + temp.name + " and gained " + to_string(temp.bonus) + " " + temp.stat;
	if ((temp.quantity - 1) == 0) { //if you use the last instance of an item, that item is removed from the characters inventory and the user is notified
		ans = "\nOh no it looks like you have used your last " + temp.name;
		inv.erase(inv.begin() + (ndx - 1));
	}
	else {
		temp.quantity = temp.quantity - 1;//updates quantity
		ans = "\nYou used 1 " + temp.name + " there are " + to_string(temp.quantity) + " left";//notifies user
	}
	return ans;
};
string Character::toString() { // prints out all character field values for the user to see
	string ans;
	vector<Item> temp = inv;
	ans = "\nName: " + values.name + "\nHp: " + to_string(values.hp) + " \nBAB: " + to_string(values.bab) + "\nStr: " + to_string(values.str) + "\nDex: " + to_string(values.dex) + "\nCon: " + to_string(values.con) + "\nInventory: "; //prints out stat values
	if (inv.empty() == 0) { //as long as there are items in the inventor
		for (int i = 0; i < temp.size(); i++) { //go through each and print out the name and quantity
			Item current = temp.at(i); 
			ans = ans + "\n\t" + to_string(i + 1) + " :\tName : " + current.name + "\n\t Quantity: " + to_string(current.quantity) + "\n\t Discription: " + current.discription;
		}
	}
	else {
		ans = ans + "EMPTY";
	}
	return ans;
}
int Attack::calcDMG(int str) { //generate random damage
	int ans = 0;
	for (int i = nbrDice; i > 0; i--) { // each attack has a number of dice
		ans = rand() % typDice + 1; // and a type of dice
	}
	return ans + str;//strength is the base damage value, but everything else lends a slightly random aspect
};
bool Attack::toHit(Stats target, Stats player) {
	if (player.bab + player.dex > target.dex) { //dexterity is what determines you ability to hit and dodge, if you basic attack bonus + your dexterity is greater then your oppenents dextery then you hit
		return true;
	}
	else {
		return false;
	}
};