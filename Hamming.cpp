#include "Header.h"

float hamming(bool org_mem[ROWS][COLS], bool CHamming[ROWS][COLS + (COLS / 4) * 3], bool FHamming[ROWS][COLS + (COLS / 4) * 3], bool DCEHamming[ROWS][COLS + (COLS / 4) * 3], bool burst)
{
	//calc hamming code for correct data
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS / 4; j++)
		{
			CHamming[i][7 * j] = FHamming[i][7 * j] = (org_mem[i][4 * j] ^ org_mem[i][4 * j + 1]) ^ org_mem[i][4 * j + 3];
			CHamming[i][7 * j + 1] = FHamming[i][7 * j + 1] = (org_mem[i][4 * j] ^ org_mem[i][4 * j + 2]) ^ org_mem[i][4 * j + 3];
			CHamming[i][7 * j + 2] = FHamming[i][7 * j + 2] = org_mem[i][4 * j];
			CHamming[i][7 * j + 3] = FHamming[i][7 * j + 3] = (org_mem[i][4 * j + 1] ^ org_mem[i][4 * j + 2]) ^ org_mem[i][4 * j + 3];
			CHamming[i][7 * j + 4] = FHamming[i][7 * j + 4] = org_mem[i][4 * j + 1];
			CHamming[i][7 * j + 5] = FHamming[i][7 * j + 5] = org_mem[i][4 * j + 2];
			CHamming[i][7 * j + 6] = FHamming[i][7 * j + 6] = org_mem[i][4 * j + 3];
		}
	}

	//check!
	/*for (int i = 0; i < ROWS; i++)
	{
		cout << endl;
		for (int j = 0; j < COLS + (COLS / 4) * 3; j++)
		{

			cout << CHamming[i][j];
		}
	}*/
	cout << "\n\n  >Correct Hamming Code Finished\n\n";

	//========================================================================================================================
	//error injection into correct data

	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + (COLS / 4) * 3, burst);

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FHamming[i][fault_P[i][j]] = !(FHamming[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + (COLS / 4) * 3; j++)
		{
			cout << FHamming[i][j];
		}
		cout << endl;
	}*/

	cout << "\n\n  >Fault Hammingcode Finished\n\n";

	//================================================================================================================================
	//calc probability of error detection
	bool BFHamming[ROWS][(COLS / 4) * 3] = {};
	bool AFHamming[ROWS][(COLS / 4) * 3] = {};

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS / 4; j++)
		{
			BFHamming[i][3 * j] = FHamming[i][7 * j];
			BFHamming[i][3 * j + 1] = FHamming[i][7 * j + 1];
			BFHamming[i][3 * j + 2] = FHamming[i][7 * j + 3];
		}
	}

	//check!
	/*cout << "\nBF hamming\n";
	for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < (COLS / 4) * 3; j++)
		{
			cout << BFHamming[i][j];
		}
		cout << endl;
	}*/


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS / 4; j++)
		{
			AFHamming[i][3 * j] = (FHamming[i][7 * j + 2] ^ FHamming[i][7 * j + 4]) ^ FHamming[i][7 * j + 6];
			AFHamming[i][3 * j + 1] = (FHamming[i][7 * j + 2] ^ FHamming[i][7 * j + 5]) ^ FHamming[i][7 * j + 6];
			AFHamming[i][3 * j + 2] = (FHamming[i][7 * j + 4] ^ FHamming[i][7 * j + 5]) ^ FHamming[i][7 * j + 6];

		}
	}

	//check!
	/*cout << "\nAF hamming\n";
	for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < (COLS / 4) * 3; j++)
		{
			cout << AFHamming[i][j];
		}
		cout << endl;
	}
	*/

	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = 0; j < (COLS / 4) * 3; j++)
		{
			if (AFHamming[i][j] ^ BFHamming[i][j])
			{
				flag = true;
				break;
			}
		}
		if (flag)
			counter++;
	}

	float DErr = counter;
	//=========================================================================================================
	
	// error correction in hamming code 

	if (FAULT_No == 1)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS + (COLS / 4) * 3; j++)
			{
				DCEHamming[i][j] = FHamming[i][j];
			}
		}


		for (int i = 0; i < ROWS; i++)
		{
			bool c2 = false;
			bool c1 = false;
			bool c0 = false;
			for (int j = 0; j < COLS / 4; j++)
			{
				c0 = DCEHamming[i][7 * j] ^ DCEHamming[i][7 * j + 2] ^ DCEHamming[i][7 * j + 4] ^ DCEHamming[i][7 * j + 6];
				c1 = DCEHamming[i][7 * j + 1] ^ DCEHamming[i][7 * j + 2] ^ DCEHamming[i][7 * j + 5] ^ DCEHamming[i][7 * j + 6];
				c2 = DCEHamming[i][7 * j + 3] ^ DCEHamming[i][7 * j + 4] ^ DCEHamming[i][7 * j + 5] ^ DCEHamming[i][7 * j + 6];

				if ((c0 + c1 * 2 + c2 * 4) != 0)
				{
					DCEHamming[i][(7 * j) + (c0 + c1 * 2 + c2 * 4) - 1] = !DCEHamming[i][(7 * j) + (c0 + c1 * 2 + c2 * 4) - 1];
				}
			}
		}

	}
	else {

		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS + (COLS / 4) * 3; j++)
			{
				DCEHamming[i][j] = false;
			}
		}
	}

	/*for (int i = 0;i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0; j < COLS + (COLS / 4) * 3; j++)
		{
			cout << DCEHamming[i][j];
		}
	}
	cout << "\n\n  >Detect and Correct Error Hamming";
*/
	return (DErr * 100 / (float)ROWS);

}

