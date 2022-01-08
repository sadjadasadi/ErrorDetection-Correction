﻿#include "Header.h"

float even_parity(bool org_mem[ROWS][COLS], bool CEPB[ROWS][COLS + PARITY_No], bool FEPB[ROWS][COLS + PARITY_No], bool burst)
{	
	//calc parity befor inject error 

	bool parity[PARITY_No] = {};
	//cout << "\n----Even Parity";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				parity[j / (COLS / PARITY_No)] = org_mem[i][j] ^ false;
			}
			else
			{
				parity[j / (COLS / PARITY_No)] ^= org_mem[i][j];
			}

			CEPB[i][j] = org_mem[i][j];
			FEPB[i][j] = org_mem[i][j];
		}
		for (int k = 0; k < PARITY_No; k++)
		{
			CEPB[i][COLS + k] = parity[k];
			FEPB[i][COLS + k] = parity[k];

			//check! 
			//cout << "\n" << parity[k] << endl;
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No; j++)
		{
			cout << FEPB[i][j];
		}
		cout << endl;
	}*/
	cout << "\n  >Correct Even Parity (CEP) Finished\n";
	//======================================================================================================================
	
	// error injection 
	
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No, burst);
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FEPB[i][fault_P[i][j]] = !(FEPB[i][fault_P[i][j]]);
		}
	}

	// check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No; j++)
		{
			cout << FEPB[i][j];
		}
		cout << endl;
	}*/
	cout << "\n  >Fault Even Parity (FEP) Finished\n\n";
	//======================================================================================================================

	// check parity after error injection 
	bool BFparity[PARITY_No] = {};
	bool AFparity[ROWS][PARITY_No] = {};


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				BFparity[j / (COLS / PARITY_No)] = FEPB[i][j] ^ false;
			}
			else
			{
				BFparity[j / (COLS / PARITY_No)] ^= FEPB[i][j];
			}
		}

		for (int k = 0; k < PARITY_No; k++)
		{
			AFparity[i][k] = BFparity[k];
		}
	}
	
	//check!

	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = COLS;j < COLS + PARITY_No;j++)
		{
			cout << AFparity[i][j - COLS] << " | " << FEPB[i][j] << "  -  ";
		}
		cout << endl;
	}*/
	//======================================================================================================================
	
	// calc probability of error detection 
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = COLS; j < COLS + PARITY_No; j++)
		{
			if (AFparity[i][j - COLS] ^ FEPB[i][j])
			{
				flag = true;
				break;
			}
		}

		if (flag)	counter++;
	}
	return (counter * 100 / (float)(ROWS));
}

float odd_parity(bool org_mem[ROWS][COLS], bool COPB[ROWS][COLS + PARITY_No], bool FOPB[ROWS][COLS + PARITY_No], bool burst)
{
	// calc odd parity befor error inject

	bool parity[PARITY_No] = {};

	//cout << "\n----Odd Parity";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				parity[j / (COLS / PARITY_No)] = org_mem[i][j] ^ false;
			}
			else
			{
				parity[j / (COLS / PARITY_No)] ^= org_mem[i][j];
			}

			COPB[i][j] = org_mem[i][j];
			FOPB[i][j] = org_mem[i][j];

		}
		for (int k = 0; k < PARITY_No; k++)
		{
			COPB[i][COLS + k] = !parity[k];
			FOPB[i][COLS + k] = !parity[k];
			
			//check!
			//cout << COPB[i][COLS + k];
		}
	}

	//check!

	/*for (int i = 0;i < ROWS;i++)
	{
		cout << endl;
		for (int j = 0;j < COLS + PARITY_No;j++)
		{
			cout << COPB[i][j];
		}

	}*/
	cout << "\n\n  >Correct Odd Parity (COP) Finished\n\n";
	//========================================================================================================================
	
	//inject error to correct data
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No, burst);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FOPB[i][fault_P[i][j]] = !(FOPB[i][fault_P[i][j]]);
		}
	}

	// check !
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No; j++)
		{
			cout << FOPB[i][j];
		}
		cout << endl;
	}*/
	cout << "\n\n  >Fault Odd Parity (FOP) Finished\n\n";

	//=========================================================================================================================
	
	//calc odd parity after error injection

	bool BFparity[PARITY_No] = {};
	bool AFparity[ROWS][PARITY_No] = {};
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / PARITY_No)))
			{
				BFparity[j / (COLS / PARITY_No)] = FOPB[i][j] ^ false;
			}
			else
			{
				BFparity[j / (COLS / PARITY_No)] ^= FOPB[i][j];
			}
		}
		for (int k = 0; k < PARITY_No; k++)
		{
			AFparity[i][k] = !BFparity[k];
			
			//check!
			//cout << AFparity[i][k];
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = COLS;j < COLS + PARITY_No;j++)
		{
			cout << AFparity[i][j - COLS] << " | " << FOPB[i][j] << "  -  ";
		}
		cout << endl;
	}*/
	//====================================================================================================================================
	
	//calc probability of error detection by odd parity on this configure
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		bool flag = false;
		for (int j = COLS; j < COLS + PARITY_No; j++)
		{
			if (!(!(AFparity[i][j - COLS] ^ FOPB[i][j])))
			{
				flag = true;
				break;
			}
		}
		if (flag)	counter++;
	}
	return (counter * 100 / (float)(ROWS));
}


