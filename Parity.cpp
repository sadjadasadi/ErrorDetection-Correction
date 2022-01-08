#include "Header.h"

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
	cout << "  >Correct Even Parity (CEP) Finished\n";
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
	cout << "  >Fault Even Parity (FEP) Finished\n";
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
	cout << "  >Correct Odd Parity (COP) Finished\n";
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
	cout << "  >Fault Odd Parity (FOP) Finished\n";

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

float comb_parity(bool org_mem[ROWS][COLS], bool CCPB[ROWS][COLS + PARITY_No * 2], bool FCPB[ROWS][COLS + PARITY_No * 2], bool burst)
{
	//calc parity befor error injection

	bool parity[ROWS][PARITY_No * 2] = {};

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (!(j % (COLS / (PARITY_No * 2))))
			{
				parity[i][j / (COLS / (PARITY_No * 2))] = org_mem[i][j] ^ false;
			}
			else
			{
				parity[i][j / (COLS / (PARITY_No * 2))] ^= org_mem[i][j];
			}
		}
		for (int k = 0; k < PARITY_No * 2; k++)
		{
			if (k % 2)
			{
				parity[i][k] = parity[i][k];
			}
			else
			{
				parity[i][k] = !parity[i][k];
			}
			//check!
			//	cout << parity[i][k];
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		int counter = 0;
		for (int j = 0; j < COLS + PARITY_No * 2; j++)
		{
			if (!((j + 1) % ((COLS + PARITY_No * 2) / (PARITY_No * 2))))
			{
				CCPB[i][j] = parity[i][counter];
				FCPB[i][j] = parity[i][counter];
				counter++;

				//check!
				//cout << "|" << CCPB[i][j] << "|";
			}
			else
			{
				CCPB[i][j] = org_mem[i][j - counter];
				FCPB[i][j] = org_mem[i][j - counter];

				//check!
				//cout << CCPB[i][j];
			}
		}
	}

	cout << "  >Corect Comb Parity (CCP) Finished\n";
	//========================================================================================================================
	
	//error injection into correct data
	int fault_P[ROWS][FAULT_No] = {};
	fault_inject(fault_P, ROWS, COLS + PARITY_No * 2, burst);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < FAULT_No; j++)
		{
			FCPB[i][fault_P[i][j]] = !(FCPB[i][fault_P[i][j]]);
		}
	}

	//check!
	/*for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0; j < COLS + PARITY_No * 2; j++)
		{
			cout << FCPB[i][j];
		}
		cout << endl;
	}*/
	cout << "  >Fault Comb Parity (FCP) Finished\n";
	//===============================================================================================================================
	
	// calc parity after error injection and then, calc probability of error detection
	bool AFparity[ROWS][PARITY_No * 2] = {};
	int counter = 0;
	for (int i = 0; i < ROWS; i++)
	{
		//cout << endl;
		bool flag = false;
		for (int j = 0; j < COLS + (PARITY_No * 2); j++)
		{
			if (!(j % ((COLS + (PARITY_No * 2)) / (PARITY_No * 2))))
			{
				AFparity[i][j / (((COLS + (PARITY_No * 2)) / (PARITY_No * 2)))] = FCPB[i][j] ^ false;
			}
			else
			{
				AFparity[i][j / (((COLS + (PARITY_No * 2)) / (PARITY_No * 2)))] ^= FCPB[i][j];
			}
		}

		for (int k = 0; k < PARITY_No * 2; k++)
		{
			AFparity[i][k] = AFparity[i][k];
			if (k % 2)
			{

				if (AFparity[i][k])
				{
					flag = true;
					break;
				}
			}
			else
			{

				if (!AFparity[i][k])
				{
					flag = true;
					break;
				}
			}

			//check !
			//cout << AFparity[i][k];
		}

		if (flag) counter++;
	}

	return ((counter * 100) / (float)(ROWS));
}


