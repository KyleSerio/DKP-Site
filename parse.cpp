#pragma once
#include "raidDump.h"
#include "header.h"
#include "database.h"


void parse(string fileName, database& mainDB, int order)
{
	string flag;
	string charName;
	int charLevel;
	int groupNum;
	string charClass;


	//database raidDump;
	ifstream readFrom;

	readFrom.open(fileName);

	while (!readFrom.eof())
	{
		readFrom >> groupNum;
		readFrom >> charName;
		readFrom >> charLevel;
		readFrom >> charClass;
		readFrom >> flag;

		while (flag != "Yes" && flag != "No")
		{
			readFrom >> flag;
		}

		mainDB.addPlayer(groupNum, charName, charLevel, charClass, flag);
	}

	cout << mainDB.raidTotal() << " -> ";
	mainDB.incRaid();
	cout << mainDB.raidTotal() << endl;

	readFrom.close();
}
