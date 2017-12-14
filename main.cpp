#include"header.h"
#include "database.h"
#include "raidDump.h"


int main() {
	string readFrom[10] = { "raidDump.txt", "raidDump2.txt", "raidDump3.txt" , "raidDump4.txt" ,
						   "raidDump5.txt" , "raidDump6.txt" , "raidDump7.txt" , "raidDump8.txt" ,
						   "raidDump9.txt" , "raidDump10.txt" };
	database raidDump;
	string outFile = "RaidData.txt";

	for(int index = 0; index < 10; index++)
	{
		parse(readFrom[index], raidDump, index);
	}


	cout << "Pre-Print Raid Total: " << raidDump.raidTotal() << endl << endl;
	raidDump.printRaid(outFile);

	

	
	//system("pause");
	return 0;
}