#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<list>
#include "raid.h" // + playerDump.h
#include "player.h"
#include "item.h"
#include "sqlite3.h"
//#include "Commdlg.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
using namespace std;

int callbackitem(void *data, int argc, char **argv, char **azColName);
int callbackraid(void *data, int argc, char **argv, char **azColName);
int callbackdump(void *data, int argc, char **argv, char **azColName);
int callbackno(void *data, int argc, char **argv, char **azColName);



class database : public item, public player, public raid
{
public:
	//Functions
	void update();
	void mainMenu();

	void accessPlayer();
	void accessItem();
	void accessRaid();

	void addPlayer();
	bool addPlayer(string newName, string newClass, int newLevel);
	void addItem();
	void addRaid();

	void removePlayer();
	void removeItem();
	void removeRaid();

	void viewPlayer();
	void viewItem();
	void viewRaid();

	void updatePlayer();
	void updateItem();
	void updateRaid();


	void printPlayers();
	void printItems();
	void printRaids();

	void printItem(string name);

	void printPlayer(string name);
	void printPlayerItems(string name);
	void printPlayerRaids(string name);

	void printDumps();

	void parseDump(char* fileName);


	//Incrementers/Decrementers
	//**************************
	void incPlayerCount();
	void decPlayerCount();
	void incItemCount();
	//**************************

	database();
	~database();

private:

	int playerCount;
	int itemCount;	
	int raidCount;

	char *zErrMsg = 0;
	sqlite3 *db;
	int check;
	char* sql;
	string stats = "C:\\Users\\Kyle\\source\\repos\\DKP Program\\SumCodeMang\\stats.txt";
};

