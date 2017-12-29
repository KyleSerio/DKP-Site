#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<sstream>
#include "sqlite3.h"
using namespace std;

extern bool printError;

//in shell.c - lines 3000 - 3003 : 
//static int callback(void *pArg, int nArg, char **azArg, char **azCol) {
//	/* since we don't have type info, call the shell_callback with a NULL value */
//	return shell_callback(pArg, nArg, azArg, azCol, NULL);
//}

int callbackitem(void *data, int argc, char **argv, char **azColName)
{
	int index;
	int colWidth;
	int dataWidth = 15;
	int longest = 0;
	printError = true;
	string temp;
	//Column Widths = 0,  1,  2,  3, 4 = 84 total
	int column[10] = {8, 14, 15, 40, 7};

	cout << "|| ";

	for (index = 0; index < argc; index++)
	{

		string temp;

		if (argv[index])
		{
			temp = argv[index];

			if (temp.length() < column[index])
			{
	
				if (index == 1)
				{
					string dateForm;

					for (int index2 = 0; index2 < temp.length(); index2++)
					{
						if (index2 == 2 || index2 == 4)
						{
							dateForm += "/";
						}
						dateForm += temp[index2];
					}

					temp = dateForm;
				}
				else if (index == 0)
				{
					temp = "[" + temp + "]";
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

		cout << temp;

	}

	cout << "||" << endl;
	printError = false;

	return 0;
}


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