#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<sstream>
#include "sqlite3.h"
using namespace std;

extern int globalIndex;
extern bool printError;
extern int globalInt;
extern string globalString;

string formColumn(string word, int columnSize);

//in shell.c - lines 3000 - 3003 : 
//static int callback(void *pArg, int nArg, char **azArg, char **azCol) {
//	/* since we don't have type info, call the shell_callback with a NULL value */
//	return shell_callback(pArg, nArg, azArg, azCol, NULL);
//}

int callbackdumpsummary(void *data, int argc, char **argv, char **azColName)
{
	int index;
	int colWidth;
	int dataWidth = 15;
	int num = 0;
	bool newEvent = false;
	printError = true;
	string temp;
	//Column Widths = 0,  1,  2,   3   4  5  = 84 total
	int column[10] = { 15, 15, 39, 15, 7, 2};
	

	//sql = "CREATE TABLE RAIDDUMP(DATE INT,TIME INT,EVENT TEXT,PLAYER TEXT);";
	//check = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


	if (globalString != argv[2] || globalIndex == 0)
	{
		if (globalIndex == 0)
		{
			globalString = argv[2];
			globalIndex = 1;
			globalInt = 1;
		}
		else
		{
			temp = formColumn(to_string(globalInt),column[4]);
			std::cout << temp << " ||" << endl;
			globalString = argv[2];
			globalInt = 1;
		}
		
		cout << "|| ";

		for (index = 0; index < argc; index++)
		{

			string temp;

			if (argv[index])
			{
				temp = argv[index];

				if (temp.length() < column[index])
				{

					if (index == 0)
					{
						string dateForm;

						if (temp.length() < 8)
						{
							temp = "0" + temp;
						}

						dateForm = temp.substr(4, 2) + "/" + temp.substr(6, 2) + "/" + temp.substr(0, 4);

						temp = dateForm;
					}
					else if (index == 1)
					{
						string timeForm;
						int time = ((temp[0] - 48) * 10) + (temp[1] - 48);

						if (time > 12)
						{
							time -= 12;
						}


						timeForm = to_string(time) + ":" + temp[2] + temp[3];
						temp = timeForm;
					}


					colWidth = column[index] - temp.length();
					string spaces(colWidth, ' ');
					temp += spaces;
				}
				else
				{
					if (index != 1)
					{
						temp = temp.substr(0, column[index] - 2);
						temp += "..";
					}
					else
					{
						temp = "DATE ERR";
					}
				}


			}
			else
			{
				temp = "NULL";
				colWidth = column[index] - temp.length();
				string spaces(colWidth, ' ');
				temp += spaces;
			}

			if (index != 5 && index != 3)
			{
				cout << temp;
			}


		}

	}
	else
	{
		globalInt++;
	}

	
	printError = false;

	return 0;
}

