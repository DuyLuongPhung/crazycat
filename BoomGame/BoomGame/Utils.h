#ifndef Utils_H

#define Utils_H


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

void trace(const LPWSTR format, ...);

struct MapTiles{
	int _id;
	int _x;
	int _y;
};

void ReadMap(LPWSTR fileName, int **tilesMatrix);


void ReadMapText(LPWSTR fileName, MapTiles *tilesItem, int **tilesMatrix, int columns);

//void ReadObject(char* fileName, MapTiles *tilesItem, int **tilesMatrix, int tiles, int rows, int columns);


#endif