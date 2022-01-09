#include "Header.h"

float single_checksum(bool org_mem[ROWS][COLS], bool CSingleChksum[ROWS + 1][COLS], bool FSingleChksum[ROWS + 1][COLS], bool burst)
{
	//calc single checksum befor error injectin for correct data
	int carry = 0;
	int one = 0;
	bool Checksum[COLS] = {};
	for (int i = COLS - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (org_mem[j][i])one++;
		}
		Checksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;

		//check!
		//cout << "\n" << Checksum[i] << endl;
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			CSingleChksum[i][j] = org_mem[i][j];
			FSingleChksum[i][j] = org_mem[i][j];
		}
	}

	for (int j = 0; j < COLS; j++)
	{
		CSingleChksum[ROWS][j] = Checksum[j];
		FSingleChksum[ROWS][j] = Checksum[j];
	}

	//check!
	/*for (int i = 0; i < ROWS + 1; i++)
	{
		cout << endl;
		for (int j = 0;j < COLS;j++)
		{
			cout << CSingleChksum[i][j];
		}

	}*/
	cout << "\n >Correct Single Checksum (CSC) Finished\n";
	//=======================================================================================================================
	//error injection into correct data
	int fault_P[ROWS + 1][FAULT_No] = {};
	fault_inject(fault_P, ROWS + 1, COLS, burst);
	for (int i = 0; i < ROWS + 1; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FSingleChksum[i][fault_P[i][j]] = !(FSingleChksum[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS + 1;i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << FSingleChksum[i][j];
		}
		cout << endl;
	}*/
	cout << "\n >Fault Single Checksum (FSC) Finished\n";
	//==========================================================================================================================
	
	//calc checksum for faulty data
	bool AChecksum[COLS] = {};
	carry = 0;
	one = 0;

	for (int i = COLS - 1; i > -1; i--)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (FSingleChksum[j][i])one++;
		}
		AChecksum[i] = (carry + one) % 2;
		carry = (one + carry) / 2;
		one = 0;
	}

	//check!
	/*cout << endl;
	for (int j = 0; j < COLS; j++)
	{
		cout << AChecksum[j] << " - " << FSingleChksum[ROWS][j] << " | ";
	}
	cout << endl;*/
	//============================================================================================
	//calc probabily of error detection 

	bool flag = true;
	for (int j = 0; j < COLS; j++)
	{
		if (AChecksum[j] != FSingleChksum[ROWS][j])
		{
			flag = false;
			break;
		}
	}

	if (flag) return 0;
	else return 100;
}
