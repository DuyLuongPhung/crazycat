#include "Utils.h"

char *__trace_file = "C:\\temp\\trace.log";
int __trace = 1;

void trace(const LPWSTR format, ...)
{
	if (!__trace) return;

	FILE *f = stderr;

	if (__trace_file != NULL)
	{
		if (fopen_s(&f, __trace_file, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", __trace_file);
			return;
		}
	}

	va_list ap;
	va_start(ap, format);
	vfwprintf(f, format, ap);
	va_end(ap);

	fprintf(f, "\n");

	if (__trace_file != NULL) fclose(f);
}

void ReadMap(LPWSTR fileName, int **mapMatrix){
	std::ifstream myfile(fileName);

	if (myfile.is_open())
	{
		std::string line;
		int mode = 0;
		int itemCount = 0;
		int row = 0;
		int col = 0;

		while (std::getline(myfile, line))
		{
			size_t pos = 0;
			std::string token;
			int j = 0;
			col = 0;
			while ((pos = line.find(" ")) != std::string::npos && j < 150)
			{
				token = line.substr(0, pos);
				mapMatrix[row][col++] = stoi(token);
				line.erase(0, pos + 1);
				j++;
			}
			row++;
		}
	}
		myfile.close();
}


void ReadMapText(LPWSTR fileName, MapTiles *tilesItem, int **tilesMatrix, int columns)
{
	std::ifstream myfile(fileName);

	if (myfile.is_open())
	{
		std::string line;
		int mode = 0;
		int itemCount = 0;
		int row = -1;
		int col = 0;

		while (std::getline(myfile, line))
		{
			if (line.length() < 1)
			{
				mode++;
				continue;
			}
			if (mode == 1)		// đọc thông tin cơ bản của tile: id, x, y, widht, height
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				size_t pos = 0;
				std::string token;
				int j = 0;
				MapTiles item;
				while ((pos = line.find(" ")) != std::string::npos && j < 5)
				{
					token = line.substr(0, pos);
					if (j == 0) // tile id
						item._id = stoi(token);
					if (j == 1) // position x
						item._x = stoi(token);
					if (j == 2) // position y
						item._y = stoi(token);
					line.erase(0, pos + 1);
					j++;
				}
				tilesItem[itemCount++] = item;
			}
			if (mode == 2)		// đọc thông tin ma trận tiles
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				row++;
				col = 0;
				size_t pos = 0;
				std::string token;
				int j = 0;
				while ((pos = line.find(" ")) != std::string::npos && j < columns)
				{
					token = line.substr(0, pos);
					tilesMatrix[row][col++] = stoi(token);
					line.erase(0, pos + 1);
					j++;
				}
			}
		}
		myfile.close();
	}
}

//void ReadObject(char* fileName, MapTiles *tilesItem, int **tilesMatrix, int tiles, int rows, int columns)
//{
//	std::ifstream myfile(fileName);
//
//	if (myfile.is_open())
//	{
//		std::string line;
//		int mode = 0;
//		int itemCount = 0;
//		int row = -1;
//		int col = 0;
//
//		while (std::getline(myfile, line))
//		{
//			if (line.length() < 1)
//			{
//				mode++;
//				continue;
//			}
//			if (mode == 1)	// đọc thông tin cơ bản của các
//			{
//				if (line[0] == ' ')
//					line.erase(0, 1);
//				size_t pos = 0;
//				std::string token;
//				int j = 0;
//				MapTiles item;
//				while ((pos = line.find(" ")) != std::string::npos && j < 5)
//				{
//
//					token = line.substr(0, pos);
//					if (j == 0) // tile id
//						item.id = stoi(token);
//					if (j == 1) // position x
//						item.x = stoi(token);
//					if (j == 2) // position y
//						item.y = stoi(token);
//					if (j == 3) // width
//						item.width = stoi(token);
//					if (j == 4) // height
//						item.height = stoi(token);
//					line.erase(0, pos + 1);
//					j++;
//				}
//				tilesItem[itemCount++] = item;
//			}
//			if (mode == 2) // map matrix information
//			{
//				if (line[0] == ' ')
//					line.erase(0, 1);
//				row++;
//				col = 0;
//				size_t pos = 0;
//				std::string token;
//				int j = 0;
//				while ((pos = line.find(" ")) != std::string::npos && j < columns)
//				{
//					token = line.substr(0, pos);
//					tilesMatrix[row][col++] = stoi(token);
//					line.erase(0, pos + 1);
//					j++;
//				}
//			}
//		}
//		myfile.close();
//	}
//}

