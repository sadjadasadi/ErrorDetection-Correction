#include "Header.h"

bool  fault_inject(int fault_P[][FAULT_No], int rows, int cols, bool burst)
{
	srand(time(NULL));
	if (!burst)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < FAULT_No; j++)
			{
				fault_P[i][j] = rand() % (cols);
			}
		}

		for (int i = 0; i < rows; i++)
		{
			bool flag = true;
			while (flag)
			{
				flag = false;
				for (int j = 0; j < FAULT_No - 1; j++)
				{
					for (int k = j + 1; k < FAULT_No; k++)
					{
						if (fault_P[i][j] == fault_P[i][k] /*|| (fault_P[i][j] + 1) == fault_P[i][k] || (fault_P[i][j] - 1) == fault_P[i][k]*/)
						{
							fault_P[i][j] = rand() % (cols);
							flag = true;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			fault_P[i][0] = rand() % (cols);
		}

		for (int i = 0; i < rows; i++)
		{
			bool flag = false;
			for (int j = 1; j < FAULT_No; j++)
			{
				if (fault_P[i][j - 1] + 1 >= cols || flag)
				{
					if (!flag)
					{
						fault_P[i][j] = fault_P[i][j - 1] - j;
						flag = true;
					}
					else
					{
						fault_P[i][j] = fault_P[i][j - 1] - 1;
					}
				}
				else
				{
					fault_P[i][j] = fault_P[i][j - 1] + 1;
				}
			}
		}
	}
	return true;
}