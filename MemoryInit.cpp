#include "Header.h"

bool create_memory(string addr)
{
	ofstream OFile;
	OFile.open(addr);
	if (OFile)
	{
		srand(time(NULL));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				OFile << rand() % 2;
			}
		}
		OFile.close();
		return true;
	}
	cout << "cant open file\a";
	return false;
}
bool read_memory(bool mem[rows][cols], string addr)
{
	FILE *RFile;
	const char* c = addr.c_str();
	errno = fopen_s(&RFile, c, "r+");
	if (~errno)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				char c = fgetc(RFile);
				if (c == '0')
					mem[i][j] = 0;
				else if (c == '1')
					mem[i][j] = 1;

			}
		}
		fclose(RFile);
		cout << "\nread memory finished\n";
		return true;
	}
	cout << "\nfile note exist!\a";
	return false;
}

