#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<sstream>
#include "database.h"
#include "sqlite3.h"
using namespace std;

int callback(void *data, int argc, char **argv, char **azColName);
int callbackitem(void *data, int argc, char **argv, char **azColName);
int callbackraid(void *data, int argc, char **argv, char **azColName);




