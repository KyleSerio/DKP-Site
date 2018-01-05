#include "database.h"

extern bool printError;




void database::update() //Used as a one-time when manually updating the database
{
	string command;






	cout << "Update Thingy " << endl;


	//command = "DROP TABLE RAIDDUMP;";
	//sql = &command[0u];
	//check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

	//command = "CREATE TABLE RAIDDUMP(DATE INT,TIME INT,EVENT TEXT,PLAYER TEXT,DKP INT,FILE TEXT);";
	//sql = &command[0u];
	//check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

	//command = "DROP TABLE FILECHECK;";
	//sql = &command[0u];
	//check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

	//command = "CREATE TABLE FILECHECK(FILE TEXT UNIQUE);";
	//sql = &command[0u];
	//check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

	//sql = "DELETE FROM RAID;";
	//check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);
	//sql = "VACUUM;";
	//check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);


}


void database::mainMenu()
{
	string input = "~";
	
	while (!input.empty()) //Outer menu - displays player list, and asks for a selection
	{
		std::cout << "Current Entries: " << endl;
		std::cout << "Players   : " << playerCount << endl;
		std::cout << "Items     : " << itemCount << endl;
		std::cout << "Raids     : " << raidCount << endl;

		std::cout << "Main Menu: [Enter] to Quit Program) Work with [P]layers, [I]tems, or [R]aids : ";
		std::getline(std::cin,input);
		std::cout << endl;

		if (input.empty())
		{
			//exit if input.empty()
		}
		else
		{
			input = toupper(input[0]);

			if (input[0] == 'P')
			{
				accessPlayer();
			}
			else if (input[0] == 'I')
			{
				accessItem();
			}
			else if (input[0] == 'R')
			{
				accessRaid();
			}
			else
			{
				std::cout << "Error: No Such Option " << endl << endl;
			}
		}



	}//end while - outer selection
}


void database::accessItem()
{
	string input = "~";


	while (!input.empty()) //Outer menu - displays player list, and asks for a selection
	{
		printItems();


		std::cout << "Item Menu: [Enter] to Quit Program) Would you like to [V]iew, [U]pdate, [A]dd, or [R]emove? : ";
		std::getline(std::cin,input);
		std::cout << endl;

		if (input.empty())
		{

		}
		else
		{
			input[0] = toupper(input[0]);

			if (input[0] == 'U')
			{
				updateItem();
			}
			else if (input[0] == 'A')
			{
				addItem();
			}
			else if (input[0] == 'R')
			{
				removeItem();
			}
			else if (input[0] == 'V')
			{
				viewItem();
			}
			else
			{
				std::cout << "Error: No Such Option " << endl << endl;
			}
		}



	}//end while - outer selection
}

void database::accessPlayer()
{
	string input = "~";

	while (!input.empty()) //Outer menu - displays player list, and asks for a selection
	{
		printPlayers();

		std::cout << "Player Menu: [Enter] to Main Menu) Would you like to [V]iew, [U]pdate, [A]dd, or [R]emove? : ";
		std::getline(std::cin, input);
		
		std::cout << endl;

		if (input.empty())
		{

		}
		else
		{
			input[0] = toupper(input[0]);

			if (input[0] == 'U')
			{
				updatePlayer();
			}
			else if (input[0] == 'A')
			{
				addPlayer();
			}
			else if (input[0] == 'R')
			{
				removePlayer();
			}
			else if (input[0] == 'V')
			{
				viewPlayer();
			}
			else
			{
				std::cout << "Error: No Such Option " << endl << endl;
			}
		}




	}//end while - outer selection

}

void database::accessRaid()
{
	string input = "~";


	while (!input.empty()) //Outer menu - displays player list, and asks for a selection
	{
		printRaids();


		std::cout << "Raid Menu: [Enter] for Main Menu) Would you like to [V]iew Dumps, [A]dd Files, or [R]emove? : ";
		std::getline(std::cin, input);
		std::cout << endl;

		if (input.empty())
		{

		}
		else
		{
			input = toupper(input[0]);


		    if (input[0] == 'A')
			{
				addRaid();
			}
			else if (input[0] == 'R')
			{
				removeRaid();
			}
			else if (input[0] == 'V')
			{
				printDumps();
			}
			else
			{
				std::cout << "Error: No Such Option " << endl << endl;
			}

		}


	}//end while - outer selection
}



void database::addItem()
{
	string command;
	string name;
	string buyer;
	bool leave = false;
	int date = 0;
	int dkp = -1;

	//sql = "INSERT INTO ITEM(ID,DATE,BUYER,ITEM,SPENT) VALUES (1, 12202017, 'Venalin', 'Morguecaller', 50);";
	//check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	printError = true;

	std::cout << "Adding Item: [Enter] for Main Menu) What is the name of the item?: ";
	std::getline(std::cin, name);
	std::cout << endl;

	if (!name.empty())
	{
		name[0] = toupper(name[0]);

		while (printError && !leave)
		{

			std::cout << "[Enter] to exit: Who bought this item?: ";
			std::getline(std::cin,buyer);
			std::cout << endl;

			if (!buyer.empty())
			{
				leave = true;
			}
			else
			{
				buyer[0] = toupper(buyer[0]);
				printError = true;
				std::cout << "Adding to ";
				command = "SELECT NAME FROM PLAYER WHERE NAME = '" + buyer + "';";
				sql = &command[0u];
				check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

				if (printError)
				{
					std::cout << "Error: Invalid player" << endl;
				}
			}

		}

		while ((dkp < 0 || dkp > 2500) && !leave)
		{
			std::cout << "[-1] to exit: How much did " + buyer + " pay?: ";
			std::cin >> dkp;
			std::cout << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			while (std::cin.fail())
			{
				std::cout << "Error: Enter an integer " << endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> date;
			}


			if (dkp == -1)
			{
				leave = true;
			}
			else
			{
				if (dkp < 0 || dkp > 2500)
				{
					std::cout << "Error: Invalid DKP amount(0 - 2500)" << endl;
				}
			}

		}

		date = 0;
		while (date != -1 && !leave)
		{
			string testDate;
			std::cout << "[-1] to exit) Enter New Raid Date(MMDDYYYY): ";
			std::cin >> date;
			std::cout << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			while (std::cin.fail())
			{
				std::cout << "Error: Enter an integer " << endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> date;
			}

			if (date != -1)
			{

				testDate = to_string(date);
				if (testDate.length() != 8) //8 didgits + null char (?)
				{
					std::cout << "Error: Incorrect Date Format" << endl;
				}
				else
				{
					incItemCount();
					command = "INSERT INTO ITEM(ID,DATE,BUYER,ITEM,SPENT) VALUES (" + to_string(itemCount) + ", " + to_string(date) + ", '" + buyer + "', '" + name + "', " + to_string(dkp) + ");";
					sql = &command[0u];
					check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);


					std::cout << "Added " << buyer << "'s purchase to the database! " << endl;
					printPlayerItems(buyer);
					date = -1;

				}
			}
		}



				
			


	}



	std::cout << endl;

	
	
}

bool database::addPlayer(string newName, string newClass, int newLevel)
{
	string command;
	string type;
	bool success;




	std::cout << "Adding " << newName << " the level " << newLevel << " " << newClass << "..." << endl;


	std::cout << "[Enter] to cancel: What type of player is " + newName + "? (Main/Box etc.): ";
	std::getline(std::cin, type);

	if (type.empty())
	{

	}
	else
	{
		type[0] = toupper(type[0]);

		for (int index = 0; index < type.length(); index++)
		{
			if (type[index] == ' ' && type[index + 1] != NULL)
			{
				type[index + 1] = toupper(type[index + 1]);
			}
		}

		command = "INSERT INTO PLAYER(name,level,class,type,dkp,dkptotal,attendance,lifetime,checks,checkstotal) " \
			"VALUES ('" + newName + "', " + to_string(newLevel) + ",'" + newClass + "', '" + type + "', 0, 0, 0, 0, 0, 0);";
		sql = &command[0u];
		check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		incPlayerCount();
		printError = true;

		command = "SELECT * FROM PLAYER WHERE NAME = '" + newName + "';";
		sql = &command[0u];
		check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (printError)
		{
			std::cout << "Print Error!" << endl;
			success = false;
		}
		else
		{
			std::cout << "Quick Added " << newName << " to the database! " << endl << endl;
			success = true;
		}



	}
	std::cout << endl;

	return success;

}

void database::addPlayer() //Takes input from user to add a player to PLAYER table
{
	string command;
	string name = "~";
	string type;
	bool cancel;
	string newClass;


	while (!name.empty()) //Outer Loop Exit Condition
	{
		int level = 0;
		cancel = false;
		std::cout << "[Enter] for Main Menu) Who would you like to add?: ";
		std::getline(std::cin, name);
		std::cout << endl;

		
		if (!name.empty()) 
		{
			name[0] = toupper(name[0]);
			printError = true;
			command = "SELECT * FROM PLAYER WHERE NAME = '" + name + "';";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

			if (printError)
			{
				while (level != -1 && !cancel)
				{
					std::cout << "[-1] to exit) What level is " + name + "?: ";
					std::cin >> level;
					std::cout << endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					while (std::cin.fail())
					{
						std::cout << "Error: Enter an integer " << endl;
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cin >> level;
					}

					if (level != -1)
					{
						if (level < 1 || level > 110)
						{
							std::cout << "Error: Invalid level" << endl;
							level = 1;
						}
						else
						{
							std::cout << "[Enter] to Cancel: What class is " + name + "?: ";
							std::getline(std::cin, newClass);
							std::cout << endl;

							if (!newClass.empty() && !cancel)
							{
								newClass[0] = toupper(newClass[0]);

								std::cout << "[Enter] to Cancel: What type of player is " + name + "? (Main/Box etc.): ";
								std::getline(std::cin, type);
								std::cout << endl;

								if (!type.empty() && !cancel)
								{
									type[0] = toupper(type[0]);

									command = "INSERT INTO PLAYER(name,level,class,type,dkp,dkptotal,attendance,lifetime,checks,checkstotal) " \
										"VALUES ('" + name + "', " + to_string(level) + ",'" + newClass + "', '" + type + "', 0, 0, 0, 0, 0, 0);";
									sql = &command[0u];
									check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
									level = -1;
									incPlayerCount();
									std::cout << "Added " << name << " to the database! " << endl;

									printPlayers();
								}
								else
								{
									cancel = true;
								}


							}
							else
							{
								cancel = true;
							}


						}
					}
					else
					{
						cancel = true;
					}

				}
			}
			else
			{
				std::cout << "Error: Player already exists!" << endl;
			}


		}

		std::cout << endl;

	}


}

void database::addRaid()
{
	string input;

	char filename[500];
	string file[100];
	int index = 0;
	string test;
	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 500;
	ofn.lpstrTitle = "Select a File, yo!";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;




	std::cout << "[Enter] to Cancel: Would you like to add [D]umps or [L]oots? : ";
	std::getline(std::cin,input);
	std::cout << endl;



	if (input.empty())
	{

	}
	else
	{
		if (GetOpenFileNameA(&ofn))
		{
			
			char* str = ofn.lpstrFile;
			string directory = str;

			str += (directory.length() + 1);
			directory += '\\';

			while (*str) 
			{
				string filenamestr = str;
				str += (filenamestr.length() + 1);
				// use the filename, e.g. add it to a vector

				file[index] = filenamestr;


				std::cout << index << "] You chose the file \"" << file[index] << "\"\n";

				index++;

			}

			input = toupper(input[0]);

			if (input[0] == 'D')
			{
				if (index == 0) //index is zero if all data is contained in the directory!
				{
					file[index] = directory;
					index = 1;
					std::cout << index << "] You chose:     " << directory << endl;
				}

				parseDump(directory, file, index);
			}
			else if (input[0] == 'L')
			{
				//ParseLoots(directory, file, index);
			}
		}
		else
		{
			// All this stuff below is to tell you exactly how you messed up above. 
			// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
			switch (CommDlgExtendedError())
			{
			case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
			case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
			case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
			case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
			case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
			case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
			case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
			case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
			case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
			case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
			case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
			case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
			case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
			case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
			case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
			default: std::cout << "You cancelled.\n";
			}

		}
	}
		
} 




void database::removeItem()
{
	string command;
	int id = 0;

	while (id != -1)
	{

		std::cout << "Remove Menu: [-1] for Main Menu) What item ID would you like to remove?: ";
		std::cin >> id;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while (std::cin.fail())
		{
			std::cout << "Error: Enter an integer " << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> id;
		}

		if (id != -1)
		{
			std::cout << endl << "Removing [" << id << "]";

			printError = true;
			command = "SELECT ITEM FROM ITEM WHERE ID = " + to_string(id) + ";";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
			std::cout << "... " << endl;



			if (printError)
			{
				std::cout << "Error: No Entry For [" << id << "]" << endl << endl;
			}
			else
			{
				command = "DELETE FROM ITEM WHERE ID = " + to_string(id) + ";";
				sql = &command[0u];
				check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
				std::cout << endl;
				std::cout << "Removed [" << id << "] from the database! " << endl;

				printItems();
			}

		}
	}
}

void database::removePlayer()
{
	string command;
	string name = "~";

	while (!name.empty())
	{

		std::cout << "Remove Menu: [Enter] for Player Menu) Who would you like to remove?: ";
		std::getline(std::cin,name);
		std::cout << endl;

		if (!name.empty())
		{
			name[0] = toupper(name[0]);

			std::cout << "Removing ";
			printError = true;

			command = "SELECT NAME FROM PLAYER WHERE NAME = '" + name + "';";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			std::cout << "... " << endl;


			if (printError)
			{
				std::cout << "Error: No Entry For " << name << endl << endl;
			}
			else
			{
				command = "DELETE FROM PLAYER WHERE NAME = '" + name + "';";
				sql = &command[0u];
				check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
				std::cout << endl;
				std::cout << "Removed " << name << " from the database! " << endl;
				decPlayerCount();

				printPlayers();
			}
		}


		
	}

}

void database::removeRaid()
{

}



void database::viewItem()
{
	string command;
	string name;
	string input = "~";

	while (!input.empty())
	{

		std::cout << "View Menu: [Enter] for Item Menu) What item would you like to view?: ";
		std::getline(std::cin,name);
		std::cout << endl;

		if (!name.empty())
		{
			name[0] = toupper(name[0]);

			printError = true;
			std::cout << "Loading ";
			command = "SELECT ITEM FROM ITEM WHERE ITEM = '" + name + "' LIMIT 1;";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);

			if (printError)
			{
				std::cout << "Error: No Entry For " << name << endl << endl;
			}
			else
			{

				printItem(name);

				while (!input.empty())
				{
					std::cout << "Item's Page: [Enter] for Item Menu) Viewing all " << name << ": View [B]uyer, [R]aid, [D]elete item, or [Q]uit";
					std::getline(std::cin,input);
					std::cout << endl;


					if (!input.empty())
					{
						input[0] = toupper(input[0]);

						if (input[0] == 'B')
						{
							viewPlayer();
						}
						else if (input[0] == 'R')
						{
							//viewRaid
						}
						else if (input[0] == 'D')
						{
							removeItem();
						}
						else
						{
							std::cout << "Error: no Such Option " << endl;
						}

						printItems();
					}

				}
			}


		}


	}
}

void database::viewPlayer()
{
	string command;
	string name = "~";
	string dummy;
	string input = "~";

	while (!name.empty())
	{



		std::cout << "View Menu: [Enter] for Player Menu) Who would you like to view?: ";
		std::getline(std::cin,name);
		std::cout << endl;
		

		if (!name.empty())
		{
			name[0] = toupper(name[0]);
			printError = true;
			std::cout << "Loading ";
			command = "SELECT NAME FROM PLAYER WHERE NAME = '" + name + "';";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


			if (printError)
			{
				std::cout << "Error: No Entry For " << name << endl << endl;
			}
			else
			{
				while (!input.empty())
				{
					printPlayer(name);

					std::cout << "Player Page: [Enter] for View Menu) View all " << name << "'s [I]tems or [R]aids?: ";
					std::getline(std::cin,input);
					std::cout << endl;

					if (!input.empty())
					{
						input[0] = toupper(input[0]);

						if (input[0] == 'I')
						{
							printPlayerItems(name);

							std::cout << "Items Page: [Enter] for Player Page)...";
							std::getline(std::cin, dummy);
							std::cout << endl;
						}
						else if (input[0] == 'R')
						{
							printPlayerRaids(name);

							std::cout << "Raids Page: [Enter] for Player Page)...";
							std::getline(std::cin, dummy);
							std::cout << endl;
						}
						else
						{
							std::cout << "Error: no Such Option " << endl;
						}
					}


				}
			}

			printPlayers();
		}

	}
}

void database::viewRaid()
{

}



void database::updateItem()
{
	string command;

	int id = 0;


	while (id != -1)
	{

		std::cout << "Update Menu: [-1] for Main) What item id would you like to update?: ";
		std::cin >> id;
		std::cout << endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while (std::cin.fail())
		{
			std::cout << "Error: Enter an integer " << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> id;
		}


		if (id != -1)
		{
			printError = true;

			command = "SELECT * FROM ITEM WHERE ID = " + to_string(id) + ";";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
			std::cout << endl;


			if (printError)
			{
				std::cout << "Error: No Entry For " << id << endl << endl;
			}
			else
			{
				string input = "~";
				while (!input.empty()) //Item specific Edit Menu
				{

					std::cout << "[Enter] to leave: Update [I]tem name, [B]uyer, [D]KP spent or [R]aid date: ";
					std::getline(std::cin,input);
					std::cout << endl << endl;

					if (!input.empty())
					{
						input = toupper(input[0]);
						if (input == "I") //Changing Item Name
						{
							string name = "~";

							std::cout << "[Enter] to cancel: Enter New Item Name: ";
							std::getline(std::cin, name);

							if (!input.empty())
							{
								name[0] = toupper(name[0]);

								command = "UPDATE ITEM SET ITEM = '" + name + "' WHERE ID = " + to_string(id) + ";";
								sql = &command[0u];
								check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
							}

						}
						else if (input == "B") //Changing Item Buyer
						{

							string buyer = "~";
							while (!buyer.empty())
							{
								std::cout << "[Enter] to exit: Enter New Buyer: ";
								std::getline(std::cin,buyer);

								if (!buyer.empty())
								{
									buyer[0] = toupper(buyer[0]);

									printError = true;
									command = "SELECT NAME FROM PLAYER WHERE NAME = '" + buyer + "';";
									sql = &command[0u];
									check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
									std::cout << endl;

									if (printError)
									{
										std::cout << "Error: Invalid buyer" << endl;
									}
									else
									{
										command = "UPDATE ITEM SET BUYER = '" + buyer + "' WHERE ID = " + to_string(id) + ";";
										sql = &command[0u];
										check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
										buyer = buyer.empty();
									}
								}

								


							}


						}
						else if (input == "D") //Changing DKP Spent
						{
							int dkp = 0;
							while (dkp != -1)
							{
								std::cout << "[-1] to exit) Enter New DKP Spent: ";
								std::cin >> dkp;
								std::cout << endl;
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								while (std::cin.fail())
								{
									std::cout << "Error: Enter an integer " << endl;
									std::cin.clear();
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									std::cin >> dkp;
								}

								if (dkp != -1)
								{
									if (dkp > 2500 || dkp < 0)
									{
										std::cout << "Error: Incorrect dkp amount (0 - 2500 only)! " << endl;
									}
									else
									{
										command = "UPDATE ITEM SET SPENT = " + to_string(dkp) + " WHERE ID = " + to_string(id) + ";";
										sql = &command[0u];
										check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
										dkp = -1;
									}
								}

							}

						}
						else if (input == "R")
						{
							int date = 0;
							while (date != -1)
							{
								string testDate;
								std::cout << "[-1] to exit) Enter New Raid Date(MMDDYYYY): ";
								std::cin >> date;
								std::cout << endl;
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								while (std::cin.fail())
								{
									std::cout << "Error: Enter an integer " << endl;
									std::cin.clear();
									std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
									std::cin >> date;
								}

								if (date != -1)
								{
									testDate = to_string(date);
									if (testDate.length() != 8) //8 didgits + null char (?)
									{
										std::cout << "Error: Incorrect Date Format" << endl;
									}
									else
									{
										command = "UPDATE ITEM SET DATE = " + to_string(date) + " WHERE ID = " + to_string(id) + ";";
										sql = &command[0u];
										check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
										date = -1;
									}
								}
							}

						}
						else
						{
							std::cout << "Error: No Such Option";
						}

						std::cout << endl;
						if (!input.empty())
						{
							command = "SELECT * FROM ITEM WHERE ID = '" + to_string(id) + "';";
							sql = &command[0u];
							check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);
							std::cout << endl;
						}
						else if (input.empty())
						{
							printItems();
						}
					}

				}//end while - player specific

			}
		}

	}


}//end method

void database::updatePlayer()
{
	string command;
	string name = "~";
	string newName;
	string newClass;

	while (!name.empty())
	{

		std::cout << "Update Menu: [Enter] for Main) Who would you like to update?: ";
		std::getline(std::cin,name);
		std::cout << endl;


		if (!name.empty())
		{
			name[0] = toupper(name[0]);
			printError = true;

			command = "SELECT * FROM PLAYER WHERE NAME = '" + name + "';";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
			std::cout << endl;

			if (printError)
			{
				std::cout << "Error: No Entry For " << name << endl << endl;
			}
			else
			{
				string input = "~";
				while (!input.empty()) //Player specific Edit Menu
				{

					std::cout << "[Enter] to leave: Update [N]ame, [L]evel, [C]lass, [D]KP or [A]ttendance: ";
					std::getline(std::cin,input);
					std::cout << endl << endl;

					if (!input.empty())
					{
						input = toupper(input[0]);

						if (input[0] == 'N')
						{
							std::cout << "[Enter] to cancel: Enter New Name: ";
							std::getline(std::cin,newName);

							if (!newName.empty())
							{
								newName[0] = toupper(newName[0]);

								command = "UPDATE PLAYER SET NAME = '" + newName + "' WHERE NAME = '" + name + "';";
								sql = &command[0u];
								check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

								name = newName;
							}


						}
						else if (input[0] == 'L')
						{


							int level = 0;
							while (level != -1)
							{
								std::cout << "[-1] to exit: Enter New Level: ";
								std::cin >> level;
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

								if (level != -1)
								{
									if (level < 1 || level > 110)
									{
										std::cout << "Error: Invalid level" << endl;
									}
									else
									{
										command = "UPDATE PLAYER SET Level = " + to_string(level) + " WHERE NAME = '" + name + "';";
										sql = &command[0u];
										check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
										level = -1;
									}
								}
							}

						}
						else if (input[0] == 'C')
						{
							std::cout << "[Enter] to cancel: Enter New Class: ";
							std::getline(std::cin,newClass);

							if (!newClass.empty())
							{
								newClass[0] = toupper(newClass[0]);

								command = "UPDATE PLAYER SET Class = '" + newClass + "' WHERE NAME = '" + name + "';";
								sql = &command[0u];
								check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
							}

						}
						else if (input[0] == 'D')
						{
							int dkp = 0;
							while (dkp != -1)
							{
								std::cout << "[-1] to exit) Enter New DKP Amount: ";
								std::cin >> dkp;
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

								if (dkp != -1)
								{
									if (dkp > 2500)
									{
										std::cout << "Error: Too Much DKP! " << endl;
									}
									else
									{
										command = "UPDATE PLAYER SET DKP = " + to_string(dkp) + " WHERE NAME = '" + name + "';";
										sql = &command[0u];
										check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
										dkp = -1;
									}
								}

							}


						}
						else if (input[0] == 'A')
						{
							float attendance = 0;
							while (attendance != -1)
							{
								std::cout << "[-1] to exit) Enter New 30 Day Attendance: ";
								std::cin >> attendance;
								std::cin.clear();
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

								if (attendance != -1)
								{
									if (attendance < 0 || attendance > 100)
									{
										std::cout << "Error: Invalid Percentage" << endl;
									}
									else
									{
										command = "UPDATE PLAYER SET Attendance = " + to_string(attendance) + " WHERE NAME = '" + name + "';";
										sql = &command[0u];
										check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
										attendance = -1;
									}
								}

							}

						}
						else
						{
							std::cout << "Error: No Such Option" << endl;
						}

						if (!input.empty())
						{
							command = "SELECT * FROM PLAYER WHERE NAME = '" + name + "';";
							sql = &command[0u];
							check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
							std::cout << endl;
						}
						else if (input.empty())
						{
							printPlayers();
						}

					}




				}//end while - player specific
			}

			
		}

	}
	
	
}//end method


//DONE WITH THIS!!! I think... detects filenames, eon't re-parse a file this way to avoid duplicating data. Adds relevant info from dumps to RAID
// will make new raid, or add to existing if there is one. Basically should be able to select any files and it knows if that files been used or not, and 
// then either adds to an existing raid, or makes a new one. Soooo should be handled. Next step would be to work on either 1) raid access functionality
// like deleting/updating etc, or 2) creating a parseLoots function to do the same as ParseDumps but for loot items. Should be much smaller and simpler, hopefully.
// also - update github with a nice working version - maybe do a few more error tests then upload this version, then start work on the above!
void database::parseDump(string directory,string fileName[],int fileNum)
{
	int fileCharCount = 26; //26 + 4 for .txt = 30 total for each file
	string command;

	//Struct to hold unknown players
	struct player
	{
		string newName;
		string newClass;
		int newLevel;
	};
	player unknown[100];


	//struct to gather data about each raid to later add to DB as a raid
	//parse item method should contain: items bought, dkp spent for raid
	struct raid
	{
		int dumpDKP = 0; //how much each dump is worth in dkp
		int dateInput = 0; // to use for adding, is the numerical date
		string date; // set in the dateform loop
		int singleDKP = 0; //set when asking for night's dkp val
		int raidDKP = 0; // set at the end, total raiders * individual dkp val
		int totalRaiders = 0; // incremented for each raider entered
		float avgRaiders = 0; //set at the end: total raiders / # of dumps = avg raiders
	};
	raid raidDetails[10];

	//Variable Declarations
			string charName;
		string charClass;
		string dummy;
		string flag;
		int charLevel;
		int groupNum;

		int raiderCount = 0;
		int raidIndex = 0;
		int fileCount = 0;
		int raidCount = 0;
		int fileIndex = 0;
		int dumpCount[10] = {0,0,0,0,0,0,0,0,0,0};
		int dumpTotal = 0;
		int dkpValue[10] = { 0,0,0,0,0,0,0,0,0,0 };
		int dateInput[10] = { 0,0,0,0,0,0,0,0,0,0 };
		int dkpInput;
		string files[100];
	
		bool leave;
		string temp;
		string find;
		string input;
		string event;
		string eventStore;

		string dateForm[10];
		ifstream readFrom;



	//parse the names and dates, count the number of raids
	if (fileNum == 1)
	{
		temp = directory.substr(0, directory.length() - 1);

		printError = true;
		command = "SELECT * FROM FILECHECK WHERE FILE = '" + temp + "';";
		sql = &command[0u];
		check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

		if (printError)
		{
			command = "INSERT INTO FILECHECK(FILE) VALUES ('" + temp + "');";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

			files[0] = temp;
			raidCount = 1;
			dumpCount[1] = 1;

			int place = files[0].length() - 20;

			dateForm[0] = files[0].substr(place + 5, 2) + '/';
			dateForm[0] += files[0].substr(place + 7, 2) + '/';
			dateForm[0] += files[0].substr(place + 1, 4);

			raidDetails[0].date = dateForm[0];


			dateInput[0] = ((temp[place - 5] - 48) * 10000000) + ((temp[place - 4] - 48) * 1000000) + ((temp[place - 3] - 48) * 100000)
				+ ((temp[place - 2] - 48) * 10000) + ((temp[place - 9] - 48) * 1000) + ((temp[place - 8] - 48) * 100)
				+ ((temp[place - 7] - 48) * 10) + (temp[place - 6] - 48);

			raidDetails[0].dateInput = dateInput[0];

		}
		else
		{
			std::cout << "Error: File Exists" << endl;
			fileNum = 0;
		}
		
	}
	else
	{

		for (int index = 0; index < fileNum; index++)
		{

			temp = directory + fileName[index];

			printError = true;
			command = "SELECT * FROM FILECHECK WHERE FILE = '" + temp + "';";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

			if (printError)
			{
				command = "INSERT INTO FILECHECK(FILE) VALUES ('" + temp + "');";
				sql = &command[0u];
				check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

				files[fileIndex] = temp;
				int place = files[fileIndex].length() - 20;

				dateForm[fileIndex] = files[fileIndex].substr(place + 5, 2) + '/';
				dateForm[fileIndex] += files[fileIndex].substr(place + 7, 2) + '/';
				dateForm[fileIndex] += files[fileIndex].substr(place + 1, 4);

				//reorganizing the date to a standard format for input
				 





				if (dateForm[fileIndex] != dateForm[fileIndex - 1])
				{
					dateInput[fileIndex] = ((temp[place + 5] - 48) * 10000000) + ((temp[place + 6] - 48) * 1000000) + ((temp[place + 7] - 48) * 100000)
						+ ((temp[place + 8] - 48) * 10000) + ((temp[place + 1] - 48) * 1000) + ((temp[place + 2] - 48) * 100)
						+ ((temp[place + 3] - 48) * 10) + (temp[place + 4] - 48);

					raidDetails[raidIndex].dateInput = dateInput[fileIndex];

					raidDetails[raidIndex].date = dateForm[fileIndex];

					if (raidCount == 0)
					{
						raidCount = 1;
					}
					else
					{
						raidCount++;
					}

					dumpCount[raidCount]++;
					raidIndex++;

				}
				else
				{
					dumpCount[raidCount]++;
				}

				fileIndex++;
			}
			else
			{
				std::cout << temp << " Already Exists! Skipping...";
			}

		}
	}


	//List the raid and dump totals
	fileNum = fileIndex;
	std::cout << "Found " << raidCount << " raids!" << endl;
	for (int index = 1; index <= raidCount; index++)
	{
		std::cout << dumpCount[index] << " dumps for raid #" << index << endl;
		dumpTotal += dumpCount[index];
	}

	
	//assign DKP to dumps
	int PH = 0;
	for (int index = 1; index <= raidCount; index++)
	{
		cout << "[0] to make no change) There were " << dumpCount[index] << " dumps for raid #" << index << ", how much dkp was each dump worth? : ";
		std::cin >> dkpInput;
		std::cout << endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		while (std::cin.fail())
		{
			std::cout << "Error: Enter an integer " << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> dkpInput;
		}

		while (dkpValue[index] < 0 || dkpValue[index] > 2500)
		{
			std::cout << "Error: Must be between 0 and 2500 (Enter [0] to do nothing): " << endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> dkpInput;
		}

		if (dkpInput != 0)
		{
			cout << "Adding " << dkpInput << " to each present player, for a night's total of " << dkpInput * dumpCount[index] << " DKP!" << endl;
			raidDetails[index - 1].singleDKP = dkpInput * dumpCount[index];
			raidDetails[index - 1].dumpDKP = dkpInput;
		}

		int dkpIndex = 0;
		while (dkpIndex < dumpCount[index])
		{
			dkpValue[PH] = dkpInput;
			dkpIndex++;
			PH++;
		}

	}




	raidIndex = 0;
	//We have files to parse, now parse each one into the DB
	for (int index = 0; index < fileNum; index++)
	{
		readFrom.open(files[index]);
		//reset variables for each new file
				string timeForm;
		int unknownCount = 0;
		int dumpPlayers = 0;
		leave = false;


        //find and format the time of dump
        
		int place = files[index].length() - 10;
		string temp = files[index];

		int timeTest = ((temp[place] - 48) * 10) + (temp[place + 1] - 48);
		int time = ((temp[place] - 48) * 1000) + ((temp[place + 1] - 48) * 100);
		int time2 = ((temp[place + 2] - 48) * 10) + (temp[place + 3] - 48);


		//convert to standard
		if (timeTest > 12 )
		{
			timeTest -= 12;
		}

		//format time
		if (time2 < 10)
		{
			timeForm = to_string(timeTest) + ":0" + to_string(time2);
		}
		else
		{
			timeForm = to_string(timeTest) + ":" + to_string(time2);
		}
		time += time2;



		//Check for a change in raid date
		if ((dateForm[index] != dateForm[index - 1]) && index > 0)
		{
			std::cout << "New Raid Day! Dump is now for: " << dateForm[index] << endl;
			raidIndex++;
		}

		//Get Input for the Event on the Dump
		while (!leave)
		{
			//get the event name per dump
			std::cout << "Raid #" << raidIndex + 1 << " : Dump #" << index + 1 << " - " << endl;
			std::cout << "What event is the dump on " << dateForm[index] << " at " << timeForm << " for? [Enter] to repeat last event: ";
			std::getline(cin, event);
			std::cout << endl;

			if (event.empty() && eventStore.empty())
			{
				std::cout << "Error: No prior event listed!" << endl;
			}
			else if (event.empty())
			{
				event = eventStore;
				leave = true;
			}
			else
			{
				
				event[0] = toupper(event[0]);
				//Capitalize each new word vvv
				for (int index = 0; index < event.length(); index++)
				{
					if (event[index] == ' ')
					{
						event[index + 1] = toupper(event[index + 1]);
					}
				}
				eventStore = event;
				leave = true;
			}

		}

		//Output date/time info for error checking
				std::cout << "--------------------------------------" << endl;
		std::cout << "| Alpha  : Date = " << dateForm[index] <<  " Time = " << timeForm << " |" << endl;
		std::cout << "| Numeric: Date = " << dateInput[index] << " Time = " << time << " |" << endl;
		std::cout << "--------------------------------------" << endl;
		std::cout << "| Player Name               Exists?  |" << endl;
		std::cout << "--------------------------------------" << endl;

		//grab all player data from the file, add unknowns to array
		while (!readFrom.eof())
		{

			readFrom >> groupNum;
			readFrom >> charName;
			readFrom >> charLevel;
			readFrom >> charClass;	
			std::getline(readFrom, flag);

			if (!readFrom.eof())
			{
				//add dumps to player
				printError = true;
				command = "SELECT NAME FROM PLAYER WHERE NAME = '" + charName + "';";
				sql = &command[0u];
				check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);
				string spaces(20 - charName.length(), ' ');
				std::cout << "| " << charName << spaces;

				if (printError) //returns true if the player is not in the system already
				{
					std::cout << "No" << endl;
					unknown[unknownCount].newName = charName;
					unknown[unknownCount].newClass = charClass;
					unknown[unknownCount].newLevel = charLevel;
					unknownCount++;
				}
				else
				{
					std::cout << "Yes" << endl;
					command =  "INSERT INTO RAIDDUMP(DATE,TIME,EVENT,PLAYER,DKP,FILE) VALUES";
					command += " (" + to_string(dateInput[raidIndex]) + ", " + to_string(time) + ", '" + event + "', '" + charName + "', " + to_string(dkpValue[index]) + ", '" + files[index] + "');";
					sql = &command[0u];
					check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

					command = "UPDATE PLAYER SET CHECKS = CHECKS + 1, DKP = DKP + " + to_string(dkpValue[index]) + ", DKPTOTAL = DKPTOTAL + " + to_string(dkpValue[index]) + " WHERE NAME = '" + charName + "';";
					sql = &command[0u];
					check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

				}
				dumpPlayers++;
				raidDetails[raidIndex].totalRaiders++;
			}
			


		}

		std::cout << "------------------------------------" << endl;
		std::cout << "Raiders found in this dump: " << dumpPlayers << endl;


		//Go through the unknown players, and add any to the DB
		if (unknownCount > 0) 
		{
			//Can skip adding entirely
			std::cout << "Found " << unknownCount << " unknown Characters, would you like to add any? (Y/N): ";
			getline(std::cin,input);
			std::cout << endl;

			if (toupper(input[0]) == 'Y')
			{

				int index2 = 0;

				while (!input.empty() && index2 < unknownCount)
				{
					std::cout << "[Enter] to Leave: Add " << unknown[index2].newName << " into the database? (Y/N): ";
					std::getline(std::cin, input);
					std::cout << endl;


					if (toupper(input[0]) == 'Y')
					{


						if (addPlayer(unknown[index2].newName, unknown[index2].newClass, unknown[index2].newLevel)) //addPlayer returns bool: 1 on success
						{

							command =  "INSERT INTO RAIDDUMP(DATE,TIME,EVENT,PLAYER,DKP,FILE) VALUES";
							command += " (" + to_string(dateInput[raidIndex]) + ", " + to_string(time) + ", '" + event + "', '" + unknown[index2].newName + "', " + to_string(dkpValue[index]) + ", '" + files[index] + ");";
							sql = &command[0u];
							check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

							command = "UPDATE PLAYER SET CHECKS = CHECKS + 1, DKP = DKP + " + to_string(dkpValue[index]) + ", DKPTOTAL = DKPTOTAL + " + to_string(dkpValue[index]) + " WHERE NAME = '" + unknown[index2].newName + "';";
							sql = &command[0u];
							check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

							cout << unknown[index2].newName << " added to the dump!" << endl;

						}
						else
						{
							cout << "Add Failed" << endl;
						}
					}

					if (toupper(input[0]) == 'N')
					{
						cout << "Looking at next unknown player... " << endl;
					}
						
					index2++;

				}
				
			}
			else
			{
				std::cout << "Skipping adds..." << endl;
			}
			

		}


		cout << "Done with this dump!" << endl;
		readFrom.close();
	}

	//Raid Summary and Adds/Updates the Raid Info
	for (int index = 0; index < raidCount; index++)
	{

		raidDetails[index].avgRaiders = raidDetails[index].totalRaiders / float(dumpCount[index + 1]);
		raidDetails[index].raidDKP = raidDetails[index].totalRaiders * raidDetails[index].dumpDKP;

		std::cout << "--------raidDetails Report---------" << endl;
		std::cout << "Raid Date   : " << raidDetails[index].date << endl;
		std::cout << "Date Num    : " << raidDetails[index].dateInput << endl << endl;

		std::cout << "Raid DKP    : " << raidDetails[index].raidDKP << endl;
		std::cout << "Single DKP  : " << raidDetails[index].singleDKP << endl;
		std::cout << "Dump DKP    : " << raidDetails[index].dumpDKP << endl << endl;

		std::cout << "Raider Total: " << raidDetails[index].totalRaiders << endl;
		std::cout << "Raider AVG  : " << raidDetails[index].avgRaiders << endl;
		std::cout << "-----------------------------------" << endl;

		printError = true;
		command = "SELECT * FROM RAID WHERE date = " + to_string(raidDetails[index].dateInput) + ";";
		sql = &command[0u];
		check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

		if(printError)
		{
			//"INSERT INTO RAID(DATE,ITEMS,DKPEARNED,RAIDERS,RAIDERSAVG, DKPSPENT, DKPRAID) VALUES (12202017, 47, 158, 52, 48.5, 7425, 8216);";
			command = "INSERT INTO RAID(DATE,ITEMS,DKPEARNED,RAIDERS,RAIDERSAVG,DKPSPENT,DKPRAID) VALUES (" \
									//DATE                      //ITEMS                 //DKPEARNED
				    + to_string(raidDetails[index].dateInput) + ", 0 ," + to_string(raidDetails[index].singleDKP) + ", " 
									//RAIDERS                                           //RAIDERSAVG                //DKPSPENT
				    + to_string(raidDetails[index].totalRaiders) + ", " + to_string(raidDetails[index].avgRaiders) + ", 0 ," 
									//DKPRAID
				    + to_string(raidDetails[index].raidDKP) + ");";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

			std::cout << "Added a new Raid!" << endl;
		}
		else
		{
			command = "UPDATE RAID SET"					//DKP EARNED 2
				" DKPEARNED = DKPEARNED + " + to_string(raidDetails[index].singleDKP) +
													    //TOTAL RAIDERS 2
				",RAIDERS = RAIDERS + " + to_string(raidDetails[index].totalRaiders) +
														//RAIDERSAVG 2 /2
				",RAIDERSAVG = (RAIDERSAVG + " + to_string(raidDetails[index].avgRaiders) + ") / 2" + 
														//DKPRAID 2
				",DKPRAID = DKPRAID + " + to_string(raidDetails[index].raidDKP) + 
														//SHARED DATE
				" WHERE DATE = " + to_string(raidDetails[index].dateInput) + ";";
			sql = &command[0u];
			check = sqlite3_exec(db, sql, callbackno, 0, &zErrMsg);

			std::cout << "Modified an existing raid!" << endl;
		}
	}

	//Update the total checks and all existing player attendance
		command = "UPDATE PLAYER SET CHECKSTOTAL = CHECKSTOTAL + " + to_string(dumpTotal) + ";";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

	command = "UPDATE PLAYER SET ATTENDANCE = (CAST(CHECKS AS FLOAT)/CHECKSTOTAL) * 100;";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

}



void database::printPlayers()
{

	std::cout << "||***********************************************************************************************||" << endl;
	std::cout << "|| Name          Level      Class          Type    DKP      Earned    30 Day   Life     Checks   ||" << endl;
	std::cout << "||-----------------------------------------------------------------------------------------------||" << endl; //added 20

	sql = "SELECT * FROM PLAYER ORDER BY ATTENDANCE DESC;";
	check = sqlite3_exec(db,sql,callback,0, &zErrMsg);


	std::cout << "||***********************************************************************************************||" << endl;

}

void database::printPlayer(string name)
{
	string command;
	string asterisks(42 - name.length(), '*');

	std::cout << "||************************************ Viewing " << name << "'s page!" << asterisks << "||" << endl;
	std::cout << "||                                                                                               ||" << endl;
	std::cout << "|| Name          Level      Class          Type    DKP      Earned    30 Day   Life     Checks   ||" << endl;
	std::cout << "||-----------------------------------------------------------------------------------------------||" << endl; //added 20

	command = "SELECT * FROM PLAYER WHERE NAME = '" + name + "';";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


	string asterisksAgain(43 - name.length(), '*');
	std::cout << "||                                                                                               ||" << endl;
	std::cout << "||************************************** " << name << "'s Purchases " << asterisksAgain << "||" << endl;
	std::cout << "||                                                                                               ||" << endl;
	std::cout << "||  ID     Date          Buyer          Item Name                               Spent            ||" << endl;
	std::cout << "||-----------------------------------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM ITEM WHERE BUYER = '" + name + "';"; 
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);

	std::cout << "||                                                                                               ||" << endl;
	std::cout << "||***********************************************************************************************||" << endl;

}

void database::printPlayerItems(string name)
{
	string command;

	string asterisksAgain(38 - name.length(), '*');
	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||********************************* " << name << "'s Purchases " << asterisksAgain << "||" << endl;
	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||  ID     Date          Buyer          Item Name                               Spent  ||" << endl;
	std::cout << "||-------------------------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM ITEM WHERE BUYER = '" + name + "';";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);

	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||*************************************************************************************||" << endl;

}

void database::printPlayerRaids(string name)
{
	string command;
	string asterisksAgain(36 - name.length(), '*');

	std::cout << "||************************* " << name << "'s Raids " << asterisksAgain << "||" << endl;
	std::cout << "||                                                                      ||" << endl;
	std::cout << "|| Raid Day/Date | # Items Bought | DKP Spent | DKP Earned | Raid Total ||" << endl;
	std::cout << "||----------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM RAID WHERE BUYER = '" + name + "';";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackraid, 0, &zErrMsg);
	std::cout << "||                                                                      ||" << endl;
	std::cout << "||**********************************************************************||" << endl;
}




void database::printItems()
{
	string command;

	std::cout << "||************************************ Item Database **********************************||" << endl;
	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||  ID     Date          Buyer          Item Name                               Spent  ||" << endl;
	std::cout << "||-------------------------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM ITEM;";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);

	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||*************************************************************************************||" << endl;

}

void database::printItem(string name)
{
	string command;

	string asterisksAgain(40 - name.length(), '*');
	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||********************************* " << name << "'s History " << asterisksAgain << "||" << endl;
	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||  ID     Date          Buyer          Item Name                               Spent  ||" << endl;
	std::cout << "||-------------------------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM ITEM WHERE ITEM = '" + name + "';";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackitem, 0, &zErrMsg);

	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||*************************************************************************************||" << endl;

}

void database::printRaids()
{
	string command;

	//int column[10] = { 15, 9, 13, 10, 12, 11};


	//sql = "CREATE TABLE RAID(DATE INT UNIQUE,ITEMS INT,DKPEARNED INT,RAIDERS INT,RAIDERSAVG FLOAT, DKPSPENT INT, DKPRAID INT);";
	//check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


	std::cout << "||************************************** Raid List ************************************||" << endl;
	std::cout << "||                                                                                     ||" << endl;
	std::cout << "|| Raid Date    | Items | DKP Earned | Raiders | Avg. Raiders | DKP Spent | Raid DKP   ||" << endl;
	std::cout << "||-------------------------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM RAID;";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackraid, 0, &zErrMsg);

	std::cout << "||                                                                                     ||" << endl;
	std::cout << "||*************************************************************************************||" << endl;
}

void database::printDumps()
{
	string command;

	//		int column[10] = { 15, 15, 39, 15};
	//sql = "CREATE TABLE RAIDDUMP(DATE INT,TIME INT,EVENT TEXT,PLAYER TEXT);";
	//check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


	std::cout << "||*************************************** Raid Dumps ***************************************||" << endl;
	std::cout << "||                                                                                          ||" << endl;
	std::cout << "|| Raid Date    | Dump Time    | Event                                | Raider        | DKP ||" << endl;
	std::cout << "||------------------------------------------------------------------------------------------||" << endl;

	command = "SELECT * FROM RAIDDUMP ORDER BY DATE DESC;";
	sql = &command[0u];
	check = sqlite3_exec(db, sql, callbackdump, 0, &zErrMsg);

	std::cout << "||                                                                                          ||" << endl;
	std::cout << "||******************************************************************************************||" << endl;
}



void database::incPlayerCount()
{
	std::cout << "Players: " << playerCount << " -> ";
	playerCount++;
	std::cout << playerCount << endl;
}

void database::decPlayerCount()
{
	playerCount--;
}

void database::incItemCount()
{
	itemCount++;
}



database::database()
{
	ifstream ifile(stats);
	string dummy;
	int players;
	int raids;
	int items;

	//stats format--
	//items x
	//players y
	//raids z

	if (sqlite3_open("DKP Site", &db))
	{
		std::cout << "Failed to open Database" << endl;
	}
	else
	{
		std::cout << "Database opened!" << endl;
	}


	if (ifile.is_open())
	{
		ifile >> dummy;
		ifile >> items;
		ifile >> dummy;
		ifile >> players;
		ifile >> dummy;
		ifile >> raids;

		playerCount = players;
		itemCount = items;
		raidCount = raids;
	}
	else
	{
		std::cout << "Error: Stats File Not Found (Input)" << endl;
	}

}

database::~database()
{
	ofstream ofile(stats);
	string dummy;


	if (ofile.is_open())
	{
		ofile << "items " << itemCount << endl;
		ofile << "players " << playerCount << endl;
		ofile << "raids " << raidCount << endl;

	}
	else
	{
		std::cout << "Error: Stats File Not Found (Output)" << endl;
	}

	sqlite3_close(db);

}		


//************************************************** Old Code Below ***********************************************************

//void database::printRaidOld(string fileName){
//	ofstream print;
//	player attendee;
//	attendee.addChecks(1);
//	list<player>::iterator it;
//	list<raid>::iterator rit;
//	list<raidDump>::iterator dit;
//	bool found = false;
//	int dbRaid = 0;
//	int group = 0;
//	int raid = 0;
//	int num = 0;
//
//	/** Class Defs **/
//	int bards = 0;
//	int beastlords = 0;
//	int berserkers = 0;
//	int clerics = 0;
//	int druids = 0;
//	int enchanters = 0;
//	int magicians = 0;
//	int monks = 0;
//	int necromancers = 0;
//	int paladins = 0;
//	int rangers = 0;
//	int rogues = 0;
//	int shadowknights = 0;
//	int shaman = 0;
//	int warriors = 0;
//	int wizards = 0;
//
//
//	print.open(fileName, ios_base::app);
//
//	print << "Group --- Name ----- Level --- Class --- Flagged?" << endl;
//
//	rit = raidNights.begin(); //If we need to print multiple raid nights
//
//	while (dbRaid < rit->getDumps())
//	{
//		dit = rit->dumpList.begin(); //Dump iterator looks at first dump in raidss
//
//		raid = 0;
//
//		while (raid < dit->lastGroup)
//		{
//			group = 0;
//
//			while (group < 6)
//			{
//				if (dit->raidGroups[raid].level[group] > 0) //bandaid - initializations dont stick?
//				{
//					print << dit->raidGroups[raid].num << "   " << dit->raidGroups[raid].name[group] << "   "
//						<< dit->raidGroups[raid].level[group] << "   " << dit->raidGroups[raid].charClass[group]
//						<< "  " << dit->raidGroups[raid].flag[group] << endl;
//
//					for (it = raiders.begin(); it != raiders.end(); it++) //does this player exist yet? - if so, add a check
//					{
//						if (it->getName() == dit->raidGroups[raid].name[group])
//						{
//							found = true;
//							it->addChecks(1);
//						}
//					}
//
//					if (!found) //if not found in the list of players, add them
//					{
//						attendee.setName(dit->raidGroups[raid].name[group]);
//						attendee.setClass(dit->raidGroups[raid].charClass[group]);
//						attendee.setLevel(dit->raidGroups[raid].level[group]);
//						raiders.push_back(attendee); //make a method for this?
//						playerCount++;
//						num++;
//
//						/*Counting Classes*/
//						if (dit->raidGroups[raid].charClass[group] == "Bard")
//						{
//							bards++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Beastlord")
//						{
//							beastlords++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Berserker")
//						{
//							berserkers++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Cleric")
//						{
//							clerics++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Druid")
//						{
//							druids++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Enchanter")
//						{
//							enchanters++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Magician")
//						{
//							magicians++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Monk")
//						{
//							monks++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Necromancer")
//						{
//							necromancers++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Paladin")
//						{
//							paladins++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Ranger")
//						{
//							rangers++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Rogue")
//						{
//							rogues++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Shadowknight")
//						{
//							shadowknights++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Shaman")
//						{
//							shaman++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Warrior")
//						{
//							warriors++;
//						}
//						else if (dit->raidGroups[raid].charClass[group] == "Wizard")
//						{
//							wizards++;
//						}
//					}
//
//					found = false;
//
//				}
//				group++;
//			}
//
//			raid++;
//
//			if (raid < dit->lastGroup)
//			{
//				print << endl;
//			}
//
//		}
//
//		print << "----------------------------------------------------------" << endl;
//		print << "----------------------------------------------------------" << endl;
//		dit++; //Look at the next dump
//		dbRaid++;
//	}
//
//
//	/* Print Raiders*/
//
//	print << "----- Attendees -----" << endl;
//
//	for (it = raiders.begin(); it != raiders.end(); it++)
//	{
//		print << it->getName() << "   " << it->getLevel() << "   " << it->getClass() << "      " << it->getChecks() << endl;
//	}
//
//	print << "---------------------" << endl;
//
//	/*Print Breakdown*/
//	print << endl;
//	print << "--------------- Class Breakdown ------------------" << endl;
//	print << "Tanks:   " << warriors << " Warriors,   " << shadowknights << " Shadowknights, " << paladins << " Paladins" << endl;
//	print << "Healers: " << clerics << " Clerics,    " << shaman << " Shaman,        " << druids << " Druids" << endl;
//	print << "Melee:   " << berserkers << " Berserkers, " << rogues << " Rogues,        " << monks << " Monks" << endl;
//	print << "Hybrid:  " << rangers << " Rangers,    " << beastlords << " Beastlords,    " << bards << " Bards" << endl;
//	print << "Casters: " << wizards << " Wizards,    " << necromancers << " Necromancers,  " << magicians << " Magicians" << endl;
//	print << "Enchanters: " << enchanters << endl;
//	print << "Total Raiders: " << num << endl;
//	print << "--------------------------------------------------" << endl << endl;
//
//
//
//
//	print.close();
//}

//int database::raidTotal()
//{
//	return raidCount;
//}
//
//int database::itemTotal()
//{
//	return itemCount;
//}
//
//int database::playerTotal()
//{
//	return playerCount;
//}
//
//int database::raidDumps()
//{
//	return rit->getDumps();
//}
//
//
//void database::incRaid()
//{
//	raidCount++;
//}
//
//void database::incDumpCount()
//{
//	rit->addDump();
//}
//
//void database::newDump()
//{
//
//}


//if (groupNum != rit->dit->lastGroup) //check if group number changed - if true: reset group #
//{
//	rit->dit->groupIndex = 0;
//	rit->dit->raidIndex++;
//}

//rit->dit->raidGroups[rit->dit->raidIndex].num = groupNum;
//rit->dit->raidGroups[rit->dit->raidIndex].name[rit->dit->groupIndex] = newName;
//rit->dit->raidGroups[rit->dit->raidIndex].level[rit->dit->groupIndex] = newLevel;
//rit->dit->raidGroups[rit->dit->raidIndex].charClass[rit->dit->groupIndex] = newClass;
//rit->dit->raidGroups[rit->dit->raidIndex].flag[rit->dit->groupIndex] = newFlag;
//rit->dit->lastGroup = groupNum;

//rit->dit->groupIndex++;


//end with iterator pointiong to a new and empty class