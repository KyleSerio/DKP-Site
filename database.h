#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<list>
#include "raidDump.h"
using namespace std;

struct player
{
	string name = "0";
	int level = 0;
	string charClass = "0";
	int dkp = 0;
	int dkpTotal = 0;
	int dkpSpent = 0;
	float attendance = 0;
	int checks = 0;
};

struct item
{
	string name;
	int cost;
	string buyer;
	int date;
};

struct raids
{
	int date; //MMDDYYYY Format
	list<raidDump> raidNight;
};

class database : public raidDump
{
public:
	//Functions
	void addPlayer(int newNum, string newName, int newLevel, string newClass, string newFlag);
	void printRaid(string fileName);
	raidDump raidList[100];
	list<raids> raidNights;
	void update();


	//Getters
	int raidTotal();
	int itemTotal();
	int playerTotal();

	//Setters
	void incRaid();


	database();
	~database();

private:

	//Relationals
	list<player> raiders;
	//player raiders[100];
	item items[1000];

	//Inner-Counters
	int playerCount;
	int itemCount;
	int raidCount;


};

