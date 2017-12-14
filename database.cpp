#include "database.h"
#include "raidDump.h"

void database::update()
{
	for(int raidCount = 0; raidCount < 9; raidCount++)
	{
		for (int groupNum = 0; groupNum < 11; groupNum++)
		{
			for (int playerNum = 0; playerNum < 5; playerNum++)
			{
				
			}
		}
	}
}


void database::addPlayer(int newNum, string newName, int newLevel, string newClass, string newFlag)
{

	if (raidList[raidCount].started == 0)
	{
		raidList[raidCount].started = 1;
	}
	else if (newNum != raidList[raidCount].lastNum)
	{
		raidList[raidCount].groupIndex = 0;
		raidList[raidCount].raidIndex++;
	}

	raidList[raidCount].raidGroups[raidList[raidCount].raidIndex].num = newNum;
	raidList[raidCount].raidGroups[raidList[raidCount].raidIndex].name[raidList[raidCount].groupIndex] = newName;
	raidList[raidCount].raidGroups[raidList[raidCount].raidIndex].level[raidList[raidCount].groupIndex] = newLevel;
	raidList[raidCount].raidGroups[raidList[raidCount].raidIndex].charClass[raidList[raidCount].groupIndex] = newClass;
	raidList[raidCount].raidGroups[raidList[raidCount].raidIndex].flag[raidList[raidCount].groupIndex] = newFlag;
	raidList[raidCount].lastNum = newNum;

	raidList[raidCount].groupIndex++;

}

void database::printRaid(string fileName)
{
	ofstream print;
	player attendee;
	attendee.checks = 1;
	list<player>::iterator it;
	bool found = false;
	int dbRaid = 0;
	int group = 0;
	int raid = 0;
	int num = 0;

	/** Class Defs **/
	int bards = 0;
	int beastlords = 0;
	int berserkers = 0;
	int clerics = 0;
	int druids = 0;
	int enchanters = 0;
	int magicians = 0;
	int monks = 0;
	int necromancers = 0;
	int paladins = 0;
	int rangers = 0;
	int rogues = 0;
	int shadowknights = 0;
	int shaman = 0;
	int warriors = 0;
	int wizards = 0;


	print.open(fileName, ios_base::app);

	print << "Group --- Name ----- Level --- Class --- Flagged?" << endl;

	while (dbRaid < raidCount)
	{

	
		raid = 0;

		while (raid < raidList[dbRaid].lastNum)
		{
			group = 0;

			while (group < 6)
			{
				if (raidList[dbRaid].raidGroups[raid].level[group] > 0) //bandaid - initializations dont stick?
				{
					print << raidList[dbRaid].raidGroups[raid].num << "   " << raidList[dbRaid].raidGroups[raid].name[group] << "   "
						  << raidList[dbRaid].raidGroups[raid].level[group] << "   " << raidList[dbRaid].raidGroups[raid].charClass[group]
						  << "  " << raidList[dbRaid].raidGroups[raid].flag[group] << endl;

					for (it = raiders.begin(); it != raiders.end(); it++) //does this player exist yet? - if so, add a check
					{
						if (it->name == raidList[dbRaid].raidGroups[raid].name[group])
						{
							found = true;
							it->checks++;
						}
					}

					if (!found) //if not found in the list of players, add them
					{
						attendee.name = raidList[dbRaid].raidGroups[raid].name[group];
						attendee.charClass = raidList[dbRaid].raidGroups[raid].charClass[group];
						attendee.level = raidList[dbRaid].raidGroups[raid].level[group];
						raiders.push_back(attendee); //make a method for this?
						playerCount++;
						num++;

						/*Counting Classes*/
						if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Bard")
						{
							bards++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Beastlord")
						{
							beastlords++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Berserker")
						{
							berserkers++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Cleric")
						{
							clerics++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Druid")
						{
							druids++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Enchanter")
						{
							enchanters++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Magician")
						{
							magicians++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Monk")
						{
							monks++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Necromancer")
						{
							necromancers++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Paladin")
						{
							paladins++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Ranger")
						{
							rangers++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Rogue")
						{
							rogues++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Shadowknight")
						{
							shadowknights++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Shaman")
						{
							shaman++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Warrior")
						{
							warriors++;
						}
						else if (raidList[dbRaid].raidGroups[raid].charClass[group] == "Wizard")
						{
							wizards++;
						}
					}

					found = false;
				
				}
				group++;
			}

			raid++;

			if (raid < raidList[dbRaid].lastNum)
			{
				print << endl;
			}

		}

		print << "----------------------------------------------------------" << endl;
		print << "----------------------------------------------------------" << endl;
		dbRaid++;
	}


	/* Print Raiders*/
	
	print << "----- Attendees -----" << endl;

	for (it = raiders.begin(); it != raiders.end(); it++)
	{
		print << it->name << "   " << it->level << "   " << it->charClass << "      " << it->checks << endl;
	}

	print << "---------------------" << endl;

	/*Print Breakdown*/	
	print << endl;
			print << "--------------- Class Breakdown ------------------" << endl;
			print << "Tanks:   " << warriors << " Warriors,   " << shadowknights << " Shadowknights, " << paladins << " Paladins" << endl;
			print << "Healers: " << clerics << " Clerics,    " << shaman << " Shaman,        " << druids << " Druids" << endl;
			print << "Melee:   " << berserkers << " Berserkers, " << rogues << " Rogues,        " << monks << " Monks" << endl;
			print << "Hybrid:  " << rangers << " Rangers,    " << beastlords << " Beastlords,    " << bards << " Bards" << endl;
			print << "Casters: " << wizards << " Wizards,    " << necromancers << " Necromancers,  " << magicians << " Magicians" << endl;
			print << "Enchanters: " << enchanters << endl;
			print << "Total Raiders: " << num << endl;
			print << "--------------------------------------------------" << endl << endl;




	print.close();
}

int database::raidTotal()
{
	return raidCount;
}

int database::itemTotal()
{
	return itemCount;
}

int database::playerTotal()
{
	return playerCount;
}


void database::incRaid()
{
	raidCount++;
}

database::database()
{
	raidCount = 0;
	itemCount = 0;
	playerCount = 0;
}


database::~database()
{
}
