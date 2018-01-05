#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<sstream>
#include "sqlite3.h"
#include "Global.h"
using namespace std;

extern bool printError;

//in shell.c - lines 3000 - 3003 : 
//static int callback(void *pArg, int nArg, char **azArg, char **azCol) {
//	/* since we don't have type info, call the shell_callback with a NULL value */
//	return shell_callback(pArg, nArg, azArg, azCol, NULL);
//}

int callback(void *data, int argc, char **argv, char **azColName) 
{
	int index;
	int colWidth;
	int dataWidth = 15;
	int longest = 0;
	printError = true;
	string temp;
	string checkForm;

	//Column Widths I = 0,1,~2,3,4,~5,6,7,8 ,9 = 92 total
	int column[10] = { 15,8,17,8,9,10,9,9,9,5};

	cout << "|| ";

	for (index = 0; index < argc; index++)
	{
		
		string temp;
		
		if (argv[index])
		{
			temp = argv[index];

			if (index == 6)
			{
				if (temp.substr(0, 3) == "100")
				{
					temp = "0000";
					temp[0] = argv[index][0];
					temp[1] = argv[index][1];
					temp[2] = argv[index][2];
					temp[3] = '%';
				}
				else if (temp.substr(0, 1) == "0")
				{
					temp = "00";
					temp[0] = argv[index][0];
					temp[1] = '%';
				}
				else
				{
					temp = "000";
					temp[0] = argv[index][0];
					temp[1] = argv[index][1];
					temp[2] = '%';
				}

			}
			else if (index == 7) //because I havnt implemented lifetime yet
			{
				temp = argv[index - 1];
				if (temp.substr(0, 3) == "100")
				{
					temp = "0000";
					temp[0] = argv[index - 1][0];
					temp[1] = argv[index - 1][1];
					temp[2] = argv[index - 1][2];
					temp[3] = '%';
				}
				else if (temp.substr(0, 1) == "0")
				{
					temp = "00";
					temp[0] = argv[index - 1][0];
					temp[1] = '%';
				}
				else
				{
					temp = "000";
					temp[0] = argv[index - 1][0];
					temp[1] = argv[index - 1][1];
					temp[2] = '%';
				}
			}

			if (temp.length() < column[index] + 1)
			{

				if (index == 8)
				{
					checkForm = temp;
					checkForm += "/";

					checkForm += argv[index + 1];
					temp = checkForm;
				}

				colWidth = column[index] - temp.length();
				string spaces(colWidth, ' ');
				temp += spaces;


			}
			else
			{
				temp = temp.substr(0, column[index] - 2);
				temp += "..";
			}



		}
		else
		{
				temp = "NULL";		
				colWidth = column[index] - temp.length();
				string spaces(colWidth, ' ');
				temp += spaces;
		}

		if (index != 9)
		{
			cout << temp;
		}


	}

	cout << "||" << endl;
	printError = false;
	
	return 0;
}


//temp += "||";
//cout << temp;

//int index;
//int colWidth;
//int dataWidth = 15;
//int longest = 0;
//printError = true;
//string temp;
//
//cout << "||";
//
//for (index = 0; index < argc; index++)
//{
//
//	string temp;
//
//	if (argv[index])
//	{
//		temp = argv[index];
//
//		if (index == 0 || index == 2)
//		{
//			if (temp.length() < 18)
//			{
//				colWidth = 17 - temp.length();
//				string spaces(colWidth, ' ');
//				temp += spaces;
//			}
//			else
//			{
//				temp = temp.substr(0, 15);
//				temp += "..";
//			}
//		}
//		else
//		{
//			if (temp.length() < 6)
//			{
//				colWidth = 7 - temp.length();
//				string spaces(colWidth, ' ');
//				temp += spaces;
//
//			}
//			else
//			{
//				temp = temp.substr(0, 5);
//				temp += "..";
//			}
//
//		}
//
//
//	}
//	else
//	{
//		if (index == 1 || index > 2)
//		{
//			temp = "NULL";
//
//			if (index == 4)
//			{
//				colWidth = 9 - temp.length();
//			}
//			else
//			{
//				colWidth = 5 - temp.length();
//			}
//
//			string spaces(colWidth, ' ');
//			temp += spaces;
//
//		}
//		else
//		{
//			temp = "NULL";
//			colWidth = 17 - temp.length();
//			string spaces(colWidth, ' ');
//			temp += spaces;
//
//		}
//	}
//
//	cout << temp;
//
//	if (index == 3 || index == 4)
//	{
//		string tempSpaces(index - 2, ' ');
//		cout << tempSpaces;
//	}
//
//}
//
//temp += "||";
//cout << temp;
//printError = false;
//
//
//cout << endl;
//return 0;
//}